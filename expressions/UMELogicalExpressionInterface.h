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
#ifndef UME_LOGICAL_EXPRESSION_INTERFACE_H_
#define UME_LOGICAL_EXPRESSION_INTERFACE_H_

namespace UME {
namespace VECTOR {

#include "common/UMEForwardDeclarations.h"

    template<int SIMD_STRIDE, typename DERIVED_EXPRESSION>
    class LogicalExpression {
    public:
        static constexpr int GET_SIMD_STRIDE() { return SIMD_STRIDE; }

        operator DERIVED_EXPRESSION&() { return static_cast<DERIVED_EXPRESSION&>(*this); }
        operator DERIVED_EXPRESSION const&() const { return static_cast<const DERIVED_EXPRESSION&>(*this); }

        void dispose() {}


        UME_FORCE_INLINE LogicalLNOTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > lnot()
        {
            return LogicalLNOTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISFINExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > isfin()
        {
            return LogicalISFINExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISINFExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > isinf()
        {
            return LogicalISINFExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISANExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > isan()
        {
            return LogicalISANExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISNANExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > isnan()
        {
            return LogicalISNANExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISNORMExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > isnorm()
        {
            return LogicalISNORMExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISSUBExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > issub()
        {
            return LogicalISSUBExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISZEROExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > iszero()
        {
            return LogicalISZEROExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        UME_FORCE_INLINE LogicalISZEROSUBExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION // this expression
            > iszerosub()
        {
            return LogicalISZEROSUBExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION
                > (*this);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLANDExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> land(T2 & srcB)
        {
            return LogicalLANDExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLANDExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2 > land(T2 && srcB)
        {
            return LogicalLANDExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLORExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> lor(T2 & srcB)
        {
            return LogicalLORExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLORExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2 > lor(T2 && srcB)
        {
            return LogicalLORExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLXORExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> lxor(T2 & srcB)
        {
            return LogicalLXORExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLXORExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2 > lxor(T2 && srcB)
        {
            return LogicalLXORExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLANDNOTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2> landnot(T2 & srcB)
        {
            return LogicalLANDNOTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalLANDNOTExpression<
            SIMD_STRIDE,
            DERIVED_EXPRESSION, // this expression
            T2 > landnot(T2 && srcB)
        {
            return LogicalLANDNOTExpression<
                SIMD_STRIDE,
                DERIVED_EXPRESSION,
                T2> (*this, srcB);
        }
    };

}
}
#endif

