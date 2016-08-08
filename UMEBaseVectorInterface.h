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
#ifndef UME_BASE_VECTOR_INTERFACE_H_
#define UME_BASE_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"

namespace UME {
namespace VECTOR {

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticBaseVectorInterface :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> {
    protected:
        ~ArithmeticBaseVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;


        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE FTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>::CAST_TYPE ITOU_EXPRESSION_TYPE;

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

