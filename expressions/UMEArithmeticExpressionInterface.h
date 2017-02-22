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
#ifndef UME_ARITHMETIC_EXPRESSION_INTERFACE_H_
#define UME_ARITHMETIC_EXPRESSION_INTERFACE_H_

namespace UME {
namespace VECTOR {

#include "common/UMEForwardDeclarations.h"

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename DERIVED_EXPRESSION>
    class ArithmeticExpression {
    public:
        int LOOP_COUNT() { return static_cast<DERIVED_EXPRESSION&>(*this).LOOP_COUNT(); }

        static constexpr int GET_SIMD_STRIDE() { return SIMD_STRIDE; }

        operator DERIVED_EXPRESSION&() { return static_cast<DERIVED_EXPRESSION&>(*this); }
        operator DERIVED_EXPRESSION const&() const { return static_cast<const DERIVED_EXPRESSION&>(*this); }

        void dispose() {}

        UME_FORCE_INLINE ArithmeticRCPExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > rcp()
        {
            return ArithmeticRCPExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticNEGExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > neg()
        {
            return ArithmeticNEGExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticABSExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > abs()
        {
            return ArithmeticABSExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticSQRTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > sqrt()
        {
            return ArithmeticSQRTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticROUNDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > round()
        {
            return ArithmeticROUNDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticFLOORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > floor()
        {
            return ArithmeticFLOORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticCEILExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > ceil()
        {
            return ArithmeticCEILExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticEXPExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > exp()
        {
            return ArithmeticEXPExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOGExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > log()
        {
            return ArithmeticLOGExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOG10Expression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > log10()
        {
            return ArithmeticLOG10Expression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOG2Expression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > log2()
        {
            return ArithmeticLOG2Expression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticSINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > sin()
        {
            return ArithmeticSINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticCOSExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > cos()
        {
            return ArithmeticCOSExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticTANExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > tan()
        {
            return ArithmeticTANExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticATANExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > atan()
        {
            return ArithmeticATANExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticBNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > bnot()
        {
            return ArithmeticBNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> add(T2 srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> add(SCALAR_TYPE srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> sadd(T2 srcB)
        {
            return ArithmeticSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> sadd(SCALAR_TYPE srcB)
        {
            return ArithmeticSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> mul(T2 srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> mul(SCALAR_TYPE srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> div(T2 srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> div(SCALAR_TYPE srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> sub(T2 srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> sub(SCALAR_TYPE srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> ssub(T2 srcB)
        {
            return ArithmeticSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> ssub(SCALAR_TYPE srcB)
        {
            return ArithmeticSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> max(T2 srcB)
        {
            return ArithmeticMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> max(SCALAR_TYPE srcB)
        {
            return ArithmeticMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> min(T2 srcB)
        {
            return ArithmeticMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> min(SCALAR_TYPE srcB)
        {
            return ArithmeticMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> band(T2 srcB)
        {
            return ArithmeticBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> band(SCALAR_TYPE srcB)
        {
            return ArithmeticBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> bor(T2 srcB)
        {
            return ArithmeticBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bor(SCALAR_TYPE srcB)
        {
            return ArithmeticBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> bxor(T2 srcB)
        {
            return ArithmeticBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bxor(SCALAR_TYPE srcB)
        {
            return ArithmeticBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> bandnot(T2 srcB)
        {
            return ArithmeticBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bandnot(SCALAR_TYPE srcB)
        {
            return ArithmeticBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticREMExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> rem(T2 srcB)
        {
            return ArithmeticREMExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticREMExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> rem(SCALAR_TYPE srcB)
        {
            return ArithmeticREMExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticLSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> lsh(T2 srcB)
        {
            return ArithmeticLSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticLSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> lsh(SCALAR_TYPE srcB)
        {
            return ArithmeticLSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticRSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> rsh(T2 srcB)
        {
            return ArithmeticRSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticRSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> rsh(SCALAR_TYPE srcB)
        {
            return ArithmeticRSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticROLExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> rol(T2 srcB)
        {
            return ArithmeticROLExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticROLExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> rol(SCALAR_TYPE srcB)
        {
            return ArithmeticROLExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticRORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> ror(T2 srcB)
        {
            return ArithmeticRORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        UME_FORCE_INLINE ArithmeticRORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> ror(SCALAR_TYPE srcB)
        {
            return ArithmeticRORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> blend(T_MASK mask, T2 srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> blend(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> add(T_MASK mask, T2 srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> add(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> sadd(T_MASK mask, T2 srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> sadd(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> mul(T_MASK mask, T2 srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> mul(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> div(T_MASK mask, T2 srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> div(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> sub(T_MASK mask, T2 srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> sub(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> ssub(T_MASK mask, T2 srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> ssub(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> max(T_MASK mask, T2 srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> max(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> min(T_MASK mask, T2 srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> min(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> band(T_MASK mask, T2 srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> band(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> bor(T_MASK mask, T2 srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bor(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> bxor(T_MASK mask, T2 srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bxor(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> bandnot(T_MASK mask, T2 srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> bandnot(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMLSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> lsh(T_MASK mask, T2 srcB)
        {
            return ArithmeticMLSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMLSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> lsh(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMLSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMRSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> rsh(T_MASK mask, T2 srcB)
        {
            return ArithmeticMRSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMRSHExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> rsh(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMRSHExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMROLExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> rol(T_MASK mask, T2 srcB)
        {
            return ArithmeticMROLExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMROLExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> rol(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMROLExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMRORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            T2> ror(T_MASK mask, T2 srcB)
        {
            return ArithmeticMRORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK>
        UME_FORCE_INLINE ArithmeticMRORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T_MASK,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> ror(T_MASK mask, SCALAR_TYPE srcB)
        {
            return ArithmeticMRORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T_MASK,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, mask, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            T3> fmuladd(T2 srcB, T3 srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fmuladd(T2 srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            T2> fmuladd(SCALAR_TYPE srcB, T2 srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                T2> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), srcC);
        }

        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fmuladd(SCALAR_TYPE srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            T3> fmulsub(T2 srcB, T3 srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fmulsub(T2 srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            T2> fmulsub(SCALAR_TYPE srcB, T2 srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                T2> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), srcC);
        }

        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fmulsub(SCALAR_TYPE srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            T3> faddmul(T2 srcB, T3 srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> faddmul(T2 srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            T2> faddmul(SCALAR_TYPE srcB, T2 srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                T2> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), srcC);
        }

        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> faddmul(SCALAR_TYPE srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            T3> fsubmul(T2 srcB, T3 srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fsubmul(T2 srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, srcB, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            T2> fsubmul(SCALAR_TYPE srcB, T2 srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                T2> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), srcC);
        }

        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            Scalar<SCALAR_TYPE, SIMD_STRIDE>,
            Scalar<SCALAR_TYPE, SIMD_STRIDE>> fsubmul(SCALAR_TYPE srcB, SCALAR_TYPE srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>,
                Scalar<SCALAR_TYPE, SIMD_STRIDE>> (*this, Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcB), Scalar<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        UME_FORCE_INLINE ArithmeticHADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hadd()
        {
            return ArithmeticHADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hmul()
        {
            return ArithmeticHMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hband()
        {
            return ArithmeticHBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hbor()
        {
            return ArithmeticHBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hbxor()
        {
            return ArithmeticHBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hmax()
        {
            return ArithmeticHMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > hmin()
        {
            return ArithmeticHMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmpgt(T2 srcB)
        {
            return LogicalCMPGTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPGTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmpgt(SCALAR_TYPE srcB)
        {
            return LogicalCMPGTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmplt(T2 srcB)
        {
            return LogicalCMPLTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPLTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmplt(SCALAR_TYPE srcB)
        {
            return LogicalCMPLTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmpge(T2 srcB)
        {
            return LogicalCMPGEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPGEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmpge(SCALAR_TYPE srcB)
        {
            return LogicalCMPGEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmple(T2 srcB)
        {
            return LogicalCMPLEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPLEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmple(SCALAR_TYPE srcB)
        {
            return LogicalCMPLEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPEQExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmpeq(T2 srcB)
        {
            return LogicalCMPEQExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPEQExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmpeq(SCALAR_TYPE srcB)
        {
            return LogicalCMPEQExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPNEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            T2> cmpne(T2 srcB)
        {
            return LogicalCMPNEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2>((*this), srcB);
        }

        UME_FORCE_INLINE LogicalCMPNEExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION,
            Scalar<bool, SIMD_STRIDE>> cmpne(SCALAR_TYPE srcB)
        {
            return LogicalCMPNEExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                Scalar<bool, SIMD_STRIDE>>((*this), Scalar<bool, SIMD_STRIDE>(srcB));
        }
    };

}
}

#endif
