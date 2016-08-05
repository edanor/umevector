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
#ifndef UME_MBAND_EXPRESSION_H_
#define UME_MBAND_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE> class ScalarExpression;

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

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMAXExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTINCExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTDECExpression;

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2>
    class ArithmeticMBANDExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E_MASK & _e_mask;
        E2 & _e2;

    public:
        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 & e1, E_MASK & e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 && e1, E_MASK & e_mask, E2 & e2) :
            _e1(std::move(e1)),
            _e_mask(e_mask),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 & e1, E_MASK && e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(std::move(e_mask)),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 & e1, E_MASK & e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 && e1, E_MASK && e_mask, E2 & e2) :
            _e1(std::move(e1)),
            _e_mask(std::move(e_mask)),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 && e1, E_MASK & e_mask, E2 && e2) :
            _e1(std::move(e1)),
            _e_mask(e_mask),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 & e1, E_MASK && e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(std::move(e_mask)),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMBANDExpression(E1 && e1, E_MASK && e_mask, E2 && e2) :
            _e1(std::move(e1)),
            _e_mask(std::move(e_mask)),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e_mask.evaluate_SIMD(index);
            auto t2 = _e2.evaluate_SIMD(index);
            auto t3 = t0.band(t1, t2);
            return t3;
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e_mask.evaluate_scalar(index);
            auto t2 = _e2.evaluate_scalar(index);
            auto t3 = t0.band(t1, t2);
            return t3;
        }

        UME_FORCE_INLINE ArithmeticRCPExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > rcp()
        {
            return ArithmeticRCPExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticNEGExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > neg()
        {
            return ArithmeticNEGExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticABSExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > abs()
        {
            return ArithmeticABSExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticSQRTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > sqrt()
        {
            return ArithmeticSQRTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticROUNDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > round()
        {
            return ArithmeticROUNDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticFLOORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > floor()
        {
            return ArithmeticFLOORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticCEILExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > ceil()
        {
            return ArithmeticCEILExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticEXPExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > exp()
        {
            return ArithmeticEXPExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOGExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > log()
        {
            return ArithmeticLOGExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOG10Expression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > log10()
        {
            return ArithmeticLOG10Expression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticLOG2Expression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > log2()
        {
            return ArithmeticLOG2Expression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticSINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > sin()
        {
            return ArithmeticSINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticCOSExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > cos()
        {
            return ArithmeticCOSExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticTANExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > tan()
        {
            return ArithmeticTANExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticATANExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > atan()
        {
            return ArithmeticATANExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticBNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > bnot()
        {
            return ArithmeticBNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > add(T2 && srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> sadd(T2 & srcB)
        {
            return ArithmeticSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > sadd(T2 && srcB)
        {
            return ArithmeticSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> mul(T2 & srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > mul(T2 && srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> div(T2 & srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > div(T2 && srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> sub(T2 & srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > sub(T2 && srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> ssub(T2 & srcB)
        {
            return ArithmeticSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > ssub(T2 && srcB)
        {
            return ArithmeticSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> max(T2 & srcB)
        {
            return ArithmeticMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > max(T2 && srcB)
        {
            return ArithmeticMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> min(T2 & srcB)
        {
            return ArithmeticMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > min(T2 && srcB)
        {
            return ArithmeticMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> band(T2 & srcB)
        {
            return ArithmeticBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > band(T2 && srcB)
        {
            return ArithmeticBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> bor(T2 & srcB)
        {
            return ArithmeticBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > bor(T2 && srcB)
        {
            return ArithmeticBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> bxor(T2 & srcB)
        {
            return ArithmeticBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > bxor(T2 && srcB)
        {
            return ArithmeticBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> bandnot(T2 & srcB)
        {
            return ArithmeticBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > bandnot(T2 && srcB)
        {
            return ArithmeticBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticREMExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> rem(T2 & srcB)
        {
            return ArithmeticREMExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticREMExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > rem(T2 && srcB)
        {
            return ArithmeticREMExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> blend(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> blend(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> blend(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> blend(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> add(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> add(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> add(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> add(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sadd(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sadd(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sadd(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sadd(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> mul(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> mul(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> mul(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> mul(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> div(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> div(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> div(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> div(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sub(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sub(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sub(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> sub(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> ssub(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> ssub(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> ssub(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> ssub(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> max(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> max(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> max(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> max(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> min(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> min(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> min(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> min(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> band(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> band(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> band(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> band(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bor(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bor(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bor(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bor(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bxor(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bxor(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bxor(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bxor(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bandnot(T_MASK & mask, T2 & srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bandnot(T_MASK && mask, T2 & srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bandnot(T_MASK & mask, T2 && srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMBANDNOTExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T_MASK,
            T2> bandnot(T_MASK && mask, T2 && srcB)
        {
            return ArithmeticMBANDNOTExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        UME_FORCE_INLINE ArithmeticHADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hadd()
        {
            return ArithmeticHADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hmul()
        {
            return ArithmeticHMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hband()
        {
            return ArithmeticHBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hbor()
        {
            return ArithmeticHBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hbxor()
        {
            return ArithmeticHBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMAXExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hmax()
        {
            return ArithmeticHMAXExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMINExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> // this expression
            > hmin()
        {
            return ArithmeticHMINExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>
                > (*this);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGTExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpgt(T2 & srcB)
        {
            return LogicalCMPGTExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGTExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpgt(T2 && srcB)
        {
            return LogicalCMPGTExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLTExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmplt(T2 & srcB)
        {
            return LogicalCMPLTExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLTExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmplt(T2 && srcB)
        {
            return LogicalCMPLTExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpge(T2 & srcB)
        {
            return LogicalCMPGEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPGEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpge(T2 && srcB)
        {
            return LogicalCMPGEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmple(T2 & srcB)
        {
            return LogicalCMPLEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPLEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmple(T2 && srcB)
        {
            return LogicalCMPLEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPEQExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpeq(T2 & srcB)
        {
            return LogicalCMPEQExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPEQExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpeq(T2 && srcB)
        {
            return LogicalCMPEQExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPNEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpne(T2 & srcB)
        {
            return LogicalCMPNEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE LogicalCMPNEExpression<
            SIMD_STRIDE,
            ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
            T2> cmpne(T2 && srcB)
        {
            return LogicalCMPNEExpression<
                SIMD_STRIDE,
                ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2>((*this), srcB);
        }

        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE FTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMBANDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>>::CAST_TYPE ITOU_EXPRESSION_TYPE;

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
