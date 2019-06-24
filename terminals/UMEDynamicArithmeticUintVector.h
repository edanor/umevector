// The MIT License (MIT)
//
// Copyright (c) 2016 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//
#ifndef UME_DYNAMIC_ARITHMETIC_UINT_VECTOR_H_
#define UME_DYNAMIC_ARITHMETIC_UINT_VECTOR_H_

namespace UME {
namespace VECTOR {

    // Dynamic vector template. The main difference with static vectors is, that
    // the the length may not be known at compile time. For that reason stack allocation
    // is not possible and the data needs to be stored on heap. This class can still use
    // ArithmeticVectorInterface, but it require some additional user-invisible functionality
    // to support type conversions between static and dynamic vectors.
    template<typename SCALAR_TYPE, int SIMD_STRIDE, class Allocator>
    class UintVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator> :
        public UintExpressionInterface<
            UintVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator>,
            SCALAR_TYPE,
            SIMD_STRIDE>
    {
    private:
        int mLength;
        int mGatherStride;

        // Used when dealing with linearly spaced vectors
        bool mIsLinearlySpaced;    // vector is linearly spaced (e.g. [1, 3, 5, 7...])
        SCALAR_TYPE mLinearInitValue;
        SCALAR_TYPE mLinearIncrementValue;
    public:
        UME_FUNC_ATTRIB int LENGTH() const { return mLength; }
        UME_FUNC_ATTRIB int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FUNC_ATTRIB int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FUNC_ATTRIB int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }
        //UME_FUNC_ATTRIB int SIMD_STRIDE() const { return STRIDE; }

        SCALAR_TYPE* elements;

        bool ownsMemory;

        UME_FUNC_ATTRIB int gatherStride() const { return mGatherStride; }

    private:
        // Vector class should be intialized with proper user-managed memory buffer.
        UME_FUNC_ATTRIB UintVector() {}

    public:
        // pointer should be properly aligned!
        UME_FUNC_ATTRIB UintVector(int length, SCALAR_TYPE *values) :
            mLength(length),
            mGatherStride(1),
            elements(values),
            ownsMemory(false),
            mIsLinearlySpaced(false)
        {}
        
        UME_FUNC_ATTRIB UintVector(int length, SCALAR_TYPE *values, int gatherStride) :
            mLength(length),
            mGatherStride(gatherStride),
            elements(values),
            ownsMemory(false),
            mIsLinearlySpaced(false)
        {}

        UME_FUNC_ATTRIB UintVector(int length) :
            mLength(length),
            mGatherStride(1),
            ownsMemory(true),
            mIsLinearlySpaced(false)
        {
            Allocator alloc;
            alloc.allocate(sizeof(SCALAR_TYPE)*length);
        }

        UME_FUNC_ATTRIB UintVector(UintVector & origin) :
            elements(origin.elements),
            mLength(origin.mLength),
            ownsMemory(false),
            mGatherStride(origin.mGatherStride),
            mIsLinearlySpaced(origin.mIsLinearlySpaced),
            mLinearInitValue(origin.mLinearInitValue),
            mLinearIncrementValue(origin.mLinearIncrementValue)
        {}

        UME_FUNC_ATTRIB UintVector(UintVector && origin) :
            elements(origin.elements),
            mLength(origin.mLength),
            ownsMemory(true),
            mGatherStride(origin.mGatherStride),
            mIsLinearlySpaced(origin.mIsLinearlySpaced),
            mLinearInitValue(origin.mLinearInitValue),
            mLinearIncrementValue(origin.mLinearIncrementValue)
        {
            origin.elements = nullptr;
        }

        // Constructor to populate vector with incremented values.
        UME_FUNC_ATTRIB UintVector(int length, SCALAR_TYPE firstValue, SCALAR_TYPE increment) :
            elements(nullptr), // This constructor does not require any allocated memory
            mLength(length),
            mGatherStride(1),
            mIsLinearlySpaced(true),
            mLinearInitValue(firstValue),
            mLinearIncrementValue(increment)
        {}

        UME_FUNC_ATTRIB ~UintVector() {
            if(ownsMemory) {
                Allocator alloc;
                alloc.deallocate(elements, sizeof(SCALAR_TYPE)*mLength);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        template<int N>
        UME_FUNC_ATTRIB UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(int index) const {
            UME::SIMD::SIMDVec<SCALAR_TYPE, N> t0;
            if (mIsLinearlySpaced) {

                assert(mIsLinearlySpaced);
                alignas(UME::SIMD::SIMDVec<SCALAR_TYPE, N>::alignment()) SCALAR_TYPE raw[N];
                for (int i = 0; i < N; i++) {
                    raw[i] = SCALAR_TYPE(i)*mLinearIncrementValue;
                }
                t0.loada(raw);
                t0.adda(SCALAR_TYPE(index)*mLinearIncrementValue + mLinearInitValue);
            }
            else {
                if (mGatherStride == 1)
                {
                    t0.load(&elements[index]);
                }
                else {
                    t0.gatheru(&elements[index*mGatherStride], mGatherStride);
                }
            }
            return t0;
        }

        template<int N>
        UME_FUNC_ATTRIB UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(UME::SIMD::SIMDVec<uint32_t, N> & indices) const {
            assert(!mIsLinearlySpaced);
            UME::SIMD::SIMDVec<SCALAR_TYPE, N> t0;
            t0.gather(&elements[0], indices);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        template<int N>
        UME_FUNC_ATTRIB void update(UME::SIMD::SIMDVec<SCALAR_TYPE, N> & x, int index) {
            assert(!mIsLinearlySpaced);
            if(mGatherStride == 1) {
                x.store(&elements[index]);
            }
            else {
                x.scatteru(&elements[index*mGatherStride], mGatherStride);
            }
        }

        template<int N>
        UME_FUNC_ATTRIB void update(UME::SIMD::SIMDVec<SCALAR_TYPE, N> & x, UME::SIMD::SIMDVec<uint32_t, N> & scatterVec) {
            assert(!mIsLinearlySpaced);
            x.scatter(&elements[0], scatterVec);
        }

        // TODO: assignment should generate an ASSIGN expression to do lazy evaluation
        UME_FUNC_ATTRIB UintVector& operator= (UintVector & origin) {
            assert(!mIsLinearlySpaced);
            if (mGatherStride == 1) {
                for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            }
            else {
                for (int i = 0; i < LENGTH(); i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            }
            return *this;
        }

        UME_FUNC_ATTRIB UintVector& operator= (UintVector&& origin) {
            assert(!mIsLinearlySpaced);
            if (mGatherStride == 1) {
                for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            }
            else {
                for (int i = 0; i < LENGTH(); i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            }
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        UME_FUNC_ATTRIB UintVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }
        template<typename E>
        UME_FUNC_ATTRIB UintVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

        UME_FUNC_ATTRIB UintVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    t0.store(&elements[i]);
                }
                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    elements[i] = x;
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }
                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    elements[i*mGatherStride] = x;
                }
            }
            return *this;
        }

        UME_FUNC_ATTRIB SCALAR_TYPE get(int index) {
            return elements[index];
        }

        UME_FUNC_ATTRIB UintVector& set(int index, SCALAR_TYPE value) {
            elements[index] = value;
            return *this;
        }
    };

}
}
#endif
