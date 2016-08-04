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
#ifndef UME_FTOI_EXPRESSION_H_
#define UME_FTOI_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE> class ScalarExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSUBExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSUBExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTINCExpression;

    template <typename SCALAR_TO_TYPE, int SIMD_STRIDE, typename E1>
    class ArithmeticFTOIExpression :
    public ArithmeticExpression<SCALAR_TO_TYPE, SIMD_STRIDE, ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>>
    {

        typedef typename UME::SIMD::SIMDVec<SCALAR_TO_TYPE, SIMD_STRIDE> SIMD_TO_TYPE;

        typedef typename UME::SIMD::SIMDVec<SCALAR_TO_TYPE, 1> SIMD_1_TO_TYPE;

        E1 & _e1;

    public:

        UME_FORCE_INLINE ArithmeticFTOIExpression(E1 & e1) :
            _e1(e1) {}

        UME_FORCE_INLINE ArithmeticFTOIExpression(E1 && e1) :
            _e1(std::move(e1)) {}

        UME_FORCE_INLINE SIMD_TO_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            return SIMD_TO_TYPE(t0);
        }

        UME_FORCE_INLINE SIMD_1_TO_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            return SIMD_1_TO_TYPE(t0);
        }


        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2 > add(T2 && srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2> mul(T2 & srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2 > mul(T2 && srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2> div(T2 & srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2 > div(T2 && srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2> sub(T2 & srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2 > sub(T2 && srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2> (*this, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>,
                T2,
                T3> (*this, srcB, srcC);
        }

        UME_FORCE_INLINE ArithmeticHADDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1> // this expression
            > hadd()
        {
            return ArithmeticHADDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMULExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1> // this expression
            > hmul()
        {
            return ArithmeticHMULExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBANDExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1> // this expression
            > hband()
        {
            return ArithmeticHBANDExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBORExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1> // this expression
            > hbor()
        {
            return ArithmeticHBORExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBXORExpression<
            SCALAR_TO_TYPE,
            SIMD_STRIDE,
            ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1> // this expression
            > hbxor()
        {
            return ArithmeticHBXORExpression<
                SCALAR_TO_TYPE,
                SIMD_STRIDE,
                ArithmeticFTOIExpression<SCALAR_TO_TYPE, SIMD_STRIDE, E1>
                > (*this);
        }
    };

}
}

#endif