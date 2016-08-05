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
#ifndef UME_SCALAR_EXPRESSION_H_
#define UME_SCALAR_EXPRESSION_H_

#include "arithmetic/UMEAddExpression.h"

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE>
    class ScalarExpression : public ArithmeticExpression < SCALAR_TYPE, SIMD_STRIDE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> >
    {
        const SCALAR_TYPE _e1;
        //SCALAR_TYPE * _e1;

    public:
        UME_FORCE_INLINE ScalarExpression(SCALAR_TYPE & value) : _e1(value) {}
        UME_FORCE_INLINE ScalarExpression(SCALAR_TYPE && value) : _e1(value) {}

        UME_FORCE_INLINE ScalarExpression(ScalarExpression && other) : _e1(other._e1) { } //: _e1(value._e1) {}
        UME_FORCE_INLINE ScalarExpression(const ScalarExpression & other) : _e1(other._e1) { }

        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> evaluate_SIMD(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE>(_e1);
        }

        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, 1>(_e1);
        }

        ScalarExpression& operator=(ScalarExpression&& other) {
            _e1 = other._e1;
            return *this;
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
            E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
                E2>(*this, srcB);
        }
        
        template<typename E_MASK, typename E2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
            E_MASK,
            E2> blend(LogicalExpression<E_MASK> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
                E_MASK,
                E2>(*this, mask, srcB);
        }

        template<typename E_MASK, typename E2>
        UME_FORCE_INLINE ArithmeticBLENDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
            E_MASK,
            E2> blend(LogicalExpression<E_MASK> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB)
        {
            return ArithmeticBLENDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
                E_MASK,
                E2>(*this, mask, srcB);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
            E2,
            E3> fmuladd(
                ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
                ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>,
                E2,
                E3>(*this, srcB, srcC);
        }
    };


    template<int SIMD_STRIDE>
    class ScalarExpression<bool, SIMD_STRIDE> : public LogicalExpression < ScalarExpression<bool, SIMD_STRIDE> >
    {
        const bool _e1;
        //SCALAR_TYPE * _e1;

    public:
        UME_FORCE_INLINE ScalarExpression(bool & value) : _e1(value) {}
        UME_FORCE_INLINE ScalarExpression(bool && value) : _e1(value) {}

        UME_FORCE_INLINE ScalarExpression(ScalarExpression && other) : _e1(other._e1) { } //: _e1(value._e1) {}
        UME_FORCE_INLINE ScalarExpression(const ScalarExpression & other) : _e1(other._e1) { }

        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<SIMD_STRIDE> evaluate_SIMD(int index)
        {
            return UME::SIMD::SIMDVecMask<SIMD_STRIDE>(_e1);
        }

        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<1> evaluate_scalar(int index)
        {
            return UME::SIMD::SIMDVecMask<1>(_e1);
        }

        ScalarExpression& operator=(ScalarExpression&& other) {
            _e1 = other._e1;
            return *this;
        }
    };

}
}
#endif
