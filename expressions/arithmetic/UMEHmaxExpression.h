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

    public:
        E1 _e1;

        UME_FORCE_INLINE int LENGTH() const { return _e1.LENGTH(); }
        UME_FORCE_INLINE int LOOP_COUNT() const { return _e1.LENGTH() / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return _e1.LENGTH() % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }

        // Value of this expression has to be calculated only once, and can be returned for every
        // call to 'evaluate'.
        bool _evaluated;
        SCALAR_TYPE _value; // This value is correct only if 'evaluated == true'

        UME_FORCE_INLINE ArithmeticHMAXExpression(E1 e1) :
            _e1(e1), _evaluated(false) {}

        UME_FORCE_INLINE ArithmeticHMAXExpression(ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & origin) :
            _e1(origin._e1), _evaluated(origin._evaluated) {}

        UME_FORCE_INLINE ArithmeticHMAXExpression(ArithmeticHMAXExpression<SCALAR_TYPE, SIMD_STRIDE, E1> && origin) :
            _e1(std::move(origin._e1)), _evaluated(std::move(origin._evaluated)) {}

        // First reduce to scalar and then return
        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(int index)
        {
            if (!_evaluated) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, N> A(SCALAR_TYPE(0));
                int loop_count = _e1.LOOP_PEEL_OFFSET();
                for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                    auto t0 = _e1.template evaluate<N>(i);
                    A.maxa(t0);
                }
                _value = A.hmax();
                for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                    auto t1 = _e1.template evaluate<1>(i);
                    _value = t1.hmax(SCALAR_TYPE(_value));
                }
                _evaluated = true;
            }
            return UME::SIMD::SIMDVec<SCALAR_TYPE, N>(_value);
        }

        // Reduction operations require to be cast-able into scalar types.
        UME_FORCE_INLINE operator SCALAR_TYPE() {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> A(SCALAR_TYPE(0));
            int loop_count = _e1.LOOP_PEEL_OFFSET();
            for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                auto t0 = _e1.template evaluate<SIMD_STRIDE>(i);
                A.maxa(t0);
            }
            SCALAR_TYPE B = A.hmax();
            for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                auto t1 = _e1.template evaluate<1>(i);
                B = t1.hmax(B);
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
