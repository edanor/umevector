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
#ifndef UME_DYNAMIC_MASK_H_
#define UME_DYNAMIC_MASK_H_

namespace UME {
namespace VECTOR {

    template<int SIMD_STRIDE, class Allocator>
    class MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator> :
        public LogicalExpression<
            SIMD_STRIDE,
            MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE>>
    {
    private:
        int mLength;
        int mGatherStride;

    public:
        UME_FORCE_INLINE int LENGTH() const { return mLength; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }

        bool* elements;

        // Used for dynamic memory allocation
        bool ownsMemory;

    private:
        UME_FORCE_INLINE MaskVector() {}

    public:
        UME_FORCE_INLINE MaskVector(int length, bool value) : mLength(length), mGatherStride(1), ownsMemory(true)
        {
            Allocator alloc;
            elements = alloc.allocate(sizeof(bool)*mLength);
            for (int i = 0; i < length; i++) elements[i] = value;
        }
        
        UME_FORCE_INLINE MaskVector(int length, bool *p) : mLength(length), mGatherStride(1), elements(p), ownsMemory(false) {}
        
        // This is the only constructor taking 'gatherStride' parameter. There is no need for it if
        // the memory is library-managed.
        UME_FORCE_INLINE MaskVector(int length, bool *p, int gatherStride) : mLength(length), mGatherStride(gatherStride), elements(p), ownsMemory(false) {}

        UME_FORCE_INLINE MaskVector(int length) : mLength(length), mGatherStride(1)
        {
            Allocator alloc;
            elements = alloc.allocate(sizeof(bool)*length);
        }

        UME_FORCE_INLINE MaskVector(MaskVector & origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            mGatherStride = origin.mGatherStride;
            ownsMemory = false;
        }

        UME_FORCE_INLINE MaskVector(MaskVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            mGatherStride = origin.mGatherStride;
            ownsMemory(true);
        }

        UME_FORCE_INLINE ~MaskVector() {
            if(ownsMemory) {
                Allocator alloc;
                alloc.deallocate(elements, sizeof(bool)*mLength);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<N> evaluate(int index) const {
            UME::SIMD::SIMDVecMask<N> t0;
            if(mGatherStride == 1)
            {
                t0.loada(&elements[index]);
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
        UME_FORCE_INLINE void update(UME::SIMD::SIMDVecMask<N> & x, int index) {
            if(mGatherStride == 1)
            {
                x.storea(&elements[index]);
            }
            else {
                x.scatteru(&elements[index*mGatherStride], mGatherStride);
            }
        }

        template<typename E>
        UME_FORCE_INLINE MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE, Allocator>(LogicalExpression<SIMD_STRIDE, E> && vec)   
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1)
            {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.storea(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }

            reinterpret_vec.dispose();
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        UME_FORCE_INLINE operator MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE>() {
            // Create dynamic Row vector, and copy data
            MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE> temp(LENGTH());
            for (int i = 0; i < LENGTH();i++) temp.elements[i] = elements[i*mGatherStride];
            return temp;
        }

        MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        MaskVector& operator= (LogicalExpression<SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            
            if(mGatherStride == 1)
            {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.storea(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }

            reinterpret_vec.dispose();
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        MaskVector& operator= (LogicalExpression<SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.storea(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

        MaskVector& operator= (bool x) {
            UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0(x);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    t0.storea(&elements[i]);
                }
                
                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    elements[i] = x;
                }
            }
            else {
                for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }
                
                for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                    elements[i*mGatherStride] = x;
                }
            }
            return *this;
        }

        MaskVector& operator= (bool* x) {
            if(mGatherStride == 1) {
                for (int i = 0; i < LENGTH(); i++) {
                    elements[i] = x[i];
                }
            }
            else {
                for (int i = 0; i < LENGTH(); i++) {
                    elements[i*mGatherStride] = x[i];
                }
            }
            return *this;
        }
    };

}
}
#endif
