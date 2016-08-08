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

    template<int SIMD_STRIDE>
    class MaskVector<SIMD_STRIDE, UME_DYNAMIC_LENGTH> :
        public LogicalExpression<
            SIMD_STRIDE,
            MaskVector<SIMD_STRIDE, UME_DYNAMIC_LENGTH >>
    {
    private:
        int mLength;

    public:
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return mLength; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }
        //UME_FORCE_INLINE int SIMD_STRIDE() const { return SIMD_STRIDE; }

        bool* elements;

        MaskVector(int length) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
        }
        MaskVector(int length, bool value) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = value;
        }
        MaskVector(int length, bool *p) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = p[i];
        }

        MaskVector(MaskVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            origin.elements = NULL;
        }

        ~MaskVector() {
            UME::DynamicMemory::AlignedFree(elements);
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


        template<typename E>
        UME_FORCE_INLINE MaskVector<SIMD_STRIDE, UME_DYNAMIC_LENGTH>(LogicalExpression<SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            reinterpret_vec.dispose();
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        UME_FORCE_INLINE operator MaskVector<SIMD_STRIDE, UME_DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            MaskVector<SIMD_STRIDE, UME_DYNAMIC_LENGTH> temp(LENGTH());
            for (int i = 0; i < LENGTH();i++) temp.elements[i] = elements[i];
            return temp;
        }

        MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
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
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
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
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        MaskVector& operator= (bool x) {
            SIMD_TYPE t0(x);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                elements[i] = x;
            }
            return *this;
        }

        MaskVector& operator= (bool* x) {
            for (int i = 0; i < LENGTH(); i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

}
}
#endif
