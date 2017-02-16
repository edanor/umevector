// The MIT License (MIT)
//
// Copyright (c) 2016-2017 CERN
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
// ***This file has been automatically generated***
//
#ifndef UME_HMAX_EXPRESSION_H_
#define UME_HMAX_EXPRESSION_H_

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
    class ArithmeticHMAXExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;

        // Value of this expression has to be calculated only once, and can be returned for every
        // call to 'evaluate_SIMD' or 'evaluate_scalar'.
        bool _evaluated;
        SCALAR_TYPE _value; // This value is correct only if 'evaluated == true'

    public:
        UME_FORCE_INLINE ArithmeticHMAXExpression(E1 & e1) :
            _e1(e1), 
            _evaluated(false) {}

        UME_FORCE_INLINE ArithmeticHMAXExpression(E1 && e1) :
            _e1(std::move(e1)),
            _evaluated(false) {}

        // First reduce to scalar and then return
        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            if (!_evaluated) {
                SIMD_TYPE A(SCALAR_TYPE(0));
                int loop_count = _e1.LOOP_PEEL_OFFSET();
                for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                    SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                    A.maxa(t0);
                }
                _value = A.hmax();
                for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                    SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                    _value = t1[0];
                }
                _evaluated = true;
            }
            return SIMD_TYPE(_value);
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            if (!_evaluated)
            {
                SIMD_TYPE A(SCALAR_TYPE(0));
                int loop_count = _e1.LOOP_PEEL_OFFSET();
                for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                    SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                    A.maxa(t0);
                }
                _value = A.hmax();
                for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                    SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                    _value = t1[0];
                }
                _evaluated = true;
            }
            return SIMD_1_TYPE(_value);
        }

        // Reduction operations require to be cast-able into scalar types.
        UME_FORCE_INLINE operator SCALAR_TYPE() {
            SIMD_TYPE A(SCALAR_TYPE(0));
            int loop_count = _e1.LOOP_PEEL_OFFSET();
            for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                A.maxa(t0);
            }
            SCALAR_TYPE B = A.hmax();
            for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                B = t1[0];
            }
            return B;
        }

        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE FTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1>>::CAST_TYPE ITOU_EXPRESSION_TYPE;

        UME_FORCE_INLINE ITOF_EXPRESSION_TYPE itof() {
            return ITOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOI_EXPRESSION_TYPE ftoi() {
            return FTOI_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE UTOF_EXPRESSION_TYPE utof() {
            return UTOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOU_EXPRESSION_TYPE ftou() {
            return FTOU_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE UTOI_EXPRESSION_TYPE utoi() {
            return UTOI_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE ITOU_EXPRESSION_TYPE itou() {
            return ITOU_EXPRESSION_TYPE(*this);
        }
    };

}
}

#endif
