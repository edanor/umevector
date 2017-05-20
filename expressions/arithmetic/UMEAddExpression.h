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
#ifndef UME_ADD_EXPRESSION_H_
#define UME_ADD_EXPRESSION_H_

#include "../UMEVectorConversionTraits.h"

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
    class ArithmeticADDExpression :
    public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> >
    {

    public:
        E1 _e1;
        E2 _e2;

        UME_FORCE_INLINE int LENGTH() const { return std::max(_e1.LENGTH(), _e2.LENGTH()); }
        UME_FORCE_INLINE int LOOP_COUNT() const { return _e1.LENGTH() / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return _e1.LENGTH() % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }

        UME_FORCE_INLINE ArithmeticADDExpression(E1 e1, E2 e2) :
            _e1(e1), _e2(e2) {}

        UME_FORCE_INLINE ArithmeticADDExpression(ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & origin) :
            _e1(origin._e1), _e2(origin._e2) {}

        UME_FORCE_INLINE ArithmeticADDExpression(ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> && origin) :
            _e1(std::move(origin._e1)), _e2(std::move(origin._e2)) {}

        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(int index)
        {
            auto t0 = _e1.template evaluate<N>(index);
            auto t1 = _e2.template evaluate<N>(index);
            return t0.add(t1);
        }

        template<int N>
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, N> evaluate(UME::SIMD::SIMDVec<uint32_t, N> & indices)
        {
            auto t0 = _e1.template evaluate<N>(indices);
            auto t1 = _e2.template evaluate<N>(indices);
            return t0.add(t1);
        }

        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE ITOU_EXPRESSION_TYPE;
        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE FTOI_EXPRESSION_TYPE;

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

    // Operators to handle "Exp1 + Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 + RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 + Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 + scalar" expressions.
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator+ (
        ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
        SCALAR_TYPE srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
            srcA,
            Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
    }

    // Operators to handle "RVALUE Exp1 + scalar" expressions.
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator+ (
        ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> && srcA,
        SCALAR_TYPE srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
            srcA,
            Scalar<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
    }

    // Operators to handle "scalar + Exp1" expressions.
    template<typename SCALAR_TYPE, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator+ (
        SCALAR_TYPE srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
            Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
            srcB);
    }

    // Operators to handle "scalar + RVALUE Exp1" expressions.
    template<typename SCALAR_TYPE, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator+ (
        SCALAR_TYPE srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
            Scalar<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
            srcB);
    }

}
}

#endif
