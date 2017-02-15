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
#ifndef UME_MLOG10_EXPRESSION_H_
#define UME_MLOG10_EXPRESSION_H_

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK>
    class ArithmeticMLOG10Expression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E_MASK & _e_mask;

    public:
        UME_FORCE_INLINE ArithmeticMLOG10Expression(E1 & e1, E_MASK & e_mask) :
            _e1(e1),
            _e_mask(e_mask) {}

        UME_FORCE_INLINE ArithmeticMLOG10Expression(E1 && e1, E_MASK & e_mask) :
            _e1(std::move(e1)),
            _e_mask(e_mask) {}

        UME_FORCE_INLINE ArithmeticMLOG10Expression(E1 & e1, E_MASK && e_mask) :
            _e1(e1),
            _e_mask(std::move(e_mask)) {}

        UME_FORCE_INLINE ArithmeticMLOG10Expression(E1 && e1, E_MASK && e_mask) :
            _e1(std::move(e1)),
            _e_mask(std::move(e_mask)) {}

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e_mask.evaluate_SIMD(index);
            auto t2 = t0.log10(t1);
            return t2;
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e_mask.evaluate_scalar(index);
            auto t2 = t0.log10(t1);
            return t2;
        }

        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE ITOU_EXPRESSION_TYPE;
        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMLOG10Expression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK>>::CAST_TYPE FTOI_EXPRESSION_TYPE;

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
