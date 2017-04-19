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
#ifndef UME_DYNAMIC_ARITHMETIC_FLOAT_VECTOR_H_
#define UME_DYNAMIC_ARITHMETIC_FLOAT_VECTOR_H_

namespace UME {
namespace VECTOR {

    // Dynamic vector template. The main difference with static vectors is, that
    // the the length may not be known at compile time. For that reason stack allocation
    // is not possible and the data needs to be stored on heap. This class can still use
    // ArithmeticVectorInterface, but it require some additional user-invisible functionality
    // to support type conversions between static and dynamic vectors.
    template<typename SCALAR_TYPE, int SIMD_STRIDE, class Allocator>
    class FloatVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator> :
        public FloatExpressionInterface<
            FloatVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator>,
            SCALAR_TYPE,
            SIMD_STRIDE>
    {
    private:
        int mLength;
        int mGatherStride;

    public:
        UME_FORCE_INLINE int LENGTH() const { return mLength; }
        UME_FORCE_INLINE int ALIGNMENT() const { return UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE>::alignment(); }
        UME_FORCE_INLINE int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }
        //UME_FORCE_INLINE int SIMD_STRIDE() const { return STRIDE; }

        SCALAR_TYPE* elements;
        
        bool ownsMemory;
        
        UME_FORCE_INLINE int gatherStride() const { return mGatherStride; }
        
    private:
        // Prohibit invalid initialization
        UME_FORCE_INLINE FloatVector() {}

    public:
        // pointer should be properly aligned!
        UME_FORCE_INLINE FloatVector(int length, SCALAR_TYPE *values) :
            mLength(length), mGatherStride(1), elements(values), ownsMemory(false) {
        }
        
        UME_FORCE_INLINE FloatVector(int length, SCALAR_TYPE *values, int gatherStride) :
            mLength(length), mGatherStride(gatherStride), elements(values), ownsMemory(false) {        
        }

        UME_FORCE_INLINE FloatVector(int length) :
            mLength(length), mGatherStride(1), ownsMemory(true)
        {
            Allocator alloc;
            elements = alloc.allocate(sizeof(SCALAR_TYPE)*length);
        }
        UME_FORCE_INLINE FloatVector(FloatVector & origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            ownsMemory = false;
            mGatherStride = origin.mGatherStride;
        }

        UME_FORCE_INLINE FloatVector(FloatVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            origin.elements = NULL;
            ownsMemory = true;
            mGatherStride = origin.mGatherStride;
        }

        UME_FORCE_INLINE ~FloatVector() {
            if(ownsMemory) {
                Allocator alloc;
                alloc.deallocate(elements, sizeof(SCALAR_TYPE)*mLength);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(int index) const {
            UME::SIMD::SIMDVec<SCALAR_TYPE, N> t0;
            if(mGatherStride == 1)
            {
                t0.load(&elements[index]);
            }
            else {
                t0.gatheru(&elements[index*mGatherStride], mGatherStride);
            }
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        template<int N>
        UME_FORCE_INLINE void update(UME::SIMD::SIMDVec<SCALAR_TYPE, N> & x, int index) {
            if(mGatherStride == 1)
            {
                x.store(&elements[index]);
            }
            else {
                x.scatteru(&elements[index*mGatherStride], mGatherStride);
            }
        }

        // TODO: assignment should generate an ASSIGN expression to do lazy evaluation
        UME_FORCE_INLINE FloatVector& operator= (FloatVector & origin) {
            if(mGatherStride == 1) {
                for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            }
            else {
                for (int i = 0; i < LENGTH(); i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            }
            return *this;
        }

        UME_FORCE_INLINE FloatVector& operator= (FloatVector&& origin) {
            if(mGatherStride == 1) {
                for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            }
            else {
                for (int i = 0; i < LENGTH(); i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            }
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        UME_FORCE_INLINE FloatVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1)
            {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    auto t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    auto t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

        template<typename E>
        UME_FORCE_INLINE FloatVector<SCALAR_TYPE, UME_DYNAMIC_LENGTH, SIMD_STRIDE> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    auto t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                    auto t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

        UME_FORCE_INLINE FloatVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            if(mGatherStride == 1)
            {
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
    };

}
}
#endif
