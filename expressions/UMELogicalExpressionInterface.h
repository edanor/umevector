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
// ***This file has been automatically generated***
//
#ifndef UME_LOGICAL_EXPRESSION_INTERFACE_H_
#define UME_LOGICAL_EXPRESSION_INTERFACE_H_

namespace UME {
namespace VECTOR {
    template<typename SCALAR_TYPE, int SIMD_STRIDE> class Scalar;

    template<int SIMD_STRIDE, typename E1> class LogicalLNOTExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISFINExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISINFExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISANExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISNANExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISNORMExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISSUBExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISZEROExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISZEROSUBExpression;

    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLANDExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLORExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLXORExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLANDNOTExpression;

    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPGTExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPLTExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPGEExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPLEExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPEQExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPNEExpression;


    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticRCPExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticNEGExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticABSExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticSQRTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticROUNDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticFLOORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticCEILExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticEXPExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOGExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOG10Expression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOG2Expression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticSINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticCOSExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticTANExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticATANExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticBNOTExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMAXExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBANDNOTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticREMExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticLSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticRSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticROLExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticRORExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticBLENDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMAXExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBANDNOTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMLSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMRSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMROLExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMRORExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTINCExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTDECExpression;
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

