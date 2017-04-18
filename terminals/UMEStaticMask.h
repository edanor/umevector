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
    public:
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return VEC_LEN; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return VEC_LEN / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return VEC_LEN % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }

        bool *elements;
        
        // Used for dynamic memory allocation
        bool ownsMemory;

    public:
        UME_FORCE_INLINE MaskVector(bool *p) : elements(p), ownsMemory(false) {}

        UME_FORCE_INLINE MaskVector() : ownsMemory(true) {
            Allocator alloc;
            elements = alloc.allocate(sizeof(bool)*VEC_LEN);
        }
        
        UME_FORCE_INLINE MaskVector(MaskVector & origin) {
            elements = origin.elements;
            // TODO: we need a reference counter to manage memory properly in this case!
            ownsMemory = false;
        }

        UME_FORCE_INLINE MaskVector(MaskVector && origin) {
            elements = origin.elements;
            ownsMemory = origin.ownsMemory;
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
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.loada(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Every expression evaluation starts with loading values from memory
        // storage into proper scalar equivalent.
        UME_FORCE_INLINE SIMD1_TYPE evaluate_scalar(int index) const {
            SIMD1_TYPE t0;
            t0.load(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        UME_FORCE_INLINE void update_SIMD(SIMD_TYPE & x, int index) {
            x.storea(&elements[index]);
        }

        UME_FORCE_INLINE void update_scalar(SIMD1_TYPE & x, int index) {
            x.store(&elements[index]);
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector && origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector<UME_DYNAMIC_LENGTH, SIMD_STRIDE> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        UME_FORCE_INLINE MaskVector& operator= (LogicalExpression<SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
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
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

    };

}
}
#endif
