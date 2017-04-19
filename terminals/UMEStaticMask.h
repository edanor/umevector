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
#ifndef UME_STATIC_MASK_H_
#define UME_STATIC_MASK_H_

#include "../expressions/UMELogicalExpressionInterface.h"

namespace UME {
namespace VECTOR {

    template<int VEC_LEN = UME_DYNAMIC_LENGTH, int SIMD_STRIDE = UME_DEFAULT_SIMD_STRIDE, class Allocator=UME::AlignedAllocator<bool, SIMD_STRIDE>>
    class MaskVector : public LogicalExpression<
        SIMD_STRIDE,
        MaskVector<VEC_LEN, SIMD_STRIDE>>
    {
    private:
        int mGatherStride;

    public:
        UME_FORCE_INLINE int LENGTH() const { return VEC_LEN; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return VEC_LEN / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return VEC_LEN % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }

        bool *elements;

        // Used for dynamic memory allocation
        bool ownsMemory;

    public:
        UME_FORCE_INLINE MaskVector(bool *p) : mGatherStride(1), elements(p), ownsMemory(false) {}

        UME_FORCE_INLINE MaskVector(bool *p, int gatherStride) : mGatherStride(gatherStride), elements(p), ownsMemory(false) {}

        UME_FORCE_INLINE MaskVector() : mGatherStride(1), ownsMemory(true) {
            Allocator alloc;
            elements = alloc.allocate(sizeof(bool)*VEC_LEN);
        }

        UME_FORCE_INLINE MaskVector(MaskVector & origin) {
            elements = origin.elements;
            // TODO: we need a reference counter to manage memory properly in this case!
            ownsMemory = false;
            mGatherStride = origin.mGatherStride;
        }

        UME_FORCE_INLINE MaskVector(MaskVector && origin) {
            elements = origin.elements;
            ownsMemory = origin.ownsMemory;
            mGatherStride = origin.mGatherStride;
        }
        
        UME_FORCE_INLINE ~MaskVector() {
            if(ownsMemory) {
                Allocator alloc;
                alloc.deallocate(elements, sizeof(bool)*VEC_LEN);
            }
        }

        template<typename E>
        MaskVector(LogicalExpression<SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1)
            {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    auto t1 = reinterpret_vec.evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    auto t1 = reinterpret_vec.evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<N> evaluate(int index) const {
            UME::SIMD::SIMDVecMask<N> t0;
            if(mGatherStride == 1) {
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
        UME_FORCE_INLINE void update(UME::SIMD::SIMDVecMask<N> & x, int index) {
            if(mGatherStride == 1) {
                x.store(&elements[index]);
            }
            else {
                x.scatteru(&elements[index*mGatherStride], mGatherStride);
            }
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector && origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i*mGatherStride] = origin.elements[i*origin.mGatherStride];
            return *this;
        }

        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        UME_FORCE_INLINE MaskVector& operator= (LogicalExpression<SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1) {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    auto t1 = reinterpret_vec.evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    auto t0 = reinterpret_vec.evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], i*mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    auto t1 = reinterpret_vec.evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        UME_FORCE_INLINE MaskVector& operator= (LogicalExpression<SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            if(mGatherStride == 1)
            {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.store(&elements[i]);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i]);
                }
            }
            else {
                for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                    UME::SIMD::SIMDVecMask<SIMD_STRIDE> t0 = reinterpret_vec.template evaluate<SIMD_STRIDE>(i);
                    t0.scatteru(&elements[i*mGatherStride], mGatherStride);
                }

                for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                    UME::SIMD::SIMDVecMask<1> t1 = reinterpret_vec.template evaluate<1>(i);
                    t1.store(&elements[i*mGatherStride]);
                }
            }
            return *this;
        }

    };

}
}
#endif
