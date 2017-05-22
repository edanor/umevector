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
#ifndef UME_MSUB_EXPRESSION_H_
#define UME_MSUB_EXPRESSION_H_

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2>
    class ArithmeticMSUBExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> >
    {

    public:
        E1 _e1;
        E_MASK _e_mask;
        E2 _e2;

        UME_FORCE_INLINE int LENGTH() const { return std::max(_e1.LENGTH(), _e2.LENGTH()); }
        UME_FORCE_INLINE int LOOP_COUNT() const { return _e1.LENGTH() / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return _e1.LENGTH() % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }

        UME_FORCE_INLINE ArithmeticMSUBExpression(E1 e1, E_MASK e_mask, E2 e2) :
            _e1(e1), _e_mask(e_mask), _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMSUBExpression(ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> & origin) :
            _e1(origin._e1), _e_mask(origin._e_mask), _e2(origin._e2) {}

        UME_FORCE_INLINE ArithmeticMSUBExpression(ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> && origin) :
            _e1(std::move(origin._e1)), _e_mask(std::move(origin._e_mask)), _e2(std::move(origin._e2)) {}

        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(int index)
        {
            auto t0 = _e1.template evaluate<N>(index);
            auto t1 = _e_mask.template evaluate<N>(index);
            auto t2 = _e2.template evaluate<N>(index);
            auto t3 = t0.sub(t1, t2);
            return t3;
        }

        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(UME::SIMD::SIMDVec<uint32_t, N> indices)
        {
            auto t0 = _e1.template evaluate<N>(indices);
            auto t1 = _e_mask.template evaluate<N>(indices);
            auto t2 = _e2.template evaluate<N>(indices);
            auto t3 = t0.sub(t1, t2);
            return t3;
        }

        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE ITOU_EXPRESSION_TYPE;
        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE FTOI_EXPRESSION_TYPE;

        UME_FORCE_INLINE UTOI_EXPRESSION_TYPE utoi() {
            return UTOI_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE UTOF_EXPRESSION_TYPE utof() {
            return UTOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE ITOU_EXPRESSION_TYPE itou() {
            return ITOU_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE ITOF_EXPRESSION_TYPE itof() {
            return ITOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOU_EXPRESSION_TYPE ftou() {
            return FTOU_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOI_EXPRESSION_TYPE ftoi() {
            return FTOI_EXPRESSION_TYPE(*this);
        }
    };

}
}

#endif
