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
#ifndef UME_CMPNE_EXPRESSION_H_
#define UME_CMPNE_EXPRESSION_H_

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <int SIMD_STRIDE, typename E1, typename E2>
    class LogicalCMPNEExpression :
    public LogicalExpression<SIMD_STRIDE, LogicalCMPNEExpression<SIMD_STRIDE, E1, E2>>
    {
        typedef typename UME::SIMD::SIMDVecMask<SIMD_STRIDE> SIMD_MASK_TYPE;
        typedef typename UME::SIMD::SIMDVecMask<1> SIMD_1_MASK_TYPE;

    public:
        E1 _e1;
        E2 _e2;

        UME_FORCE_INLINE int LENGTH() const { return _e1.LENGTH(); }
        UME_FORCE_INLINE int LOOP_COUNT() const { return _e1.LENGTH() / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return _e1.LENGTH() % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }

        UME_FORCE_INLINE LogicalCMPNEExpression(E1 e1, E2 e2) :
            _e1(e1), _e2(e2) {}

        UME_FORCE_INLINE LogicalCMPNEExpression(LogicalCMPNEExpression<SIMD_STRIDE, E1, E2> & origin) :
            _e1(origin._e1), _e2(origin._e2) {}

        UME_FORCE_INLINE LogicalCMPNEExpression(LogicalCMPNEExpression<SIMD_STRIDE, E1, E2> && origin) :
            _e1(std::move(origin._e1)), _e2(std::move(origin._e2)) {}

        UME_FORCE_INLINE SIMD_MASK_TYPE evaluate_SIMD(int index) {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            return t0.cmpne(t1);
        }

        UME_FORCE_INLINE SIMD_1_MASK_TYPE evaluate_scalar(int index) {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            return t0.cmpne(t1);
        }
    };

    // Operators to handle "Exp1 != Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2> operator!= (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 != RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2> operator!= (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 != Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2> operator!= (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 != RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2> operator!= (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 != scalar" expressions.
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE LogicalCMPNEExpression<E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>> operator!= (
        ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
        SCALAR_TYPE srcB)
    {
        return LogicalCMPNEExpression<E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
            srcA,
            Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
    }

    // Operators to handle "scalar != Exp1" expressions.
    template<typename SCALAR_TYPE, typename E2>
    UME_FORCE_INLINE LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator!= (
        SCALAR_TYPE srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return LogicalCMPNEExpression<E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
            Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
            srcB);
    }

}
}

#endif

