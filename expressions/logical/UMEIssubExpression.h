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
#ifndef UME_ISSUB_EXPRESSION_H_
#define UME_ISSUB_EXPRESSION_H_

namespace UME {
namespace VECTOR {

#include "../common/UMEForwardDeclarations.h"

    template <int SIMD_STRIDE, typename E1>
    class LogicalISSUBExpression :
    public LogicalExpression<SIMD_STRIDE, LogicalISSUBExpression<SIMD_STRIDE, E1>>
    {
        typedef typename UME::SIMD::SIMDVecMask<SIMD_STRIDE> SIMD_MASK_TYPE;
        typedef typename UME::SIMD::SIMDVecMask<1> SIMD_1_MASK_TYPE;

        E1 _e1;

    public:
        UME_FORCE_INLINE LogicalISSUBExpression(E1 e1) :
            _e1(e1) {}

        UME_FORCE_INLINE LogicalISSUBExpression(LogicalISSUBExpression<SIMD_STRIDE, E1> & origin) :
            _e1(origin._e1) {}

        UME_FORCE_INLINE LogicalISSUBExpression(LogicalISSUBExpression<SIMD_STRIDE, E1> && origin) :
            _e1(std::move(origin._e1)) {}

        UME_FORCE_INLINE SIMD_MASK_TYPE evaluate_SIMD(int index) {
            auto t0 = _e1.evaluate_SIMD(index);
            return t0.issub();
        }

        UME_FORCE_INLINE SIMD_1_MASK_TYPE evaluate_scalar(int index) {
            auto t0 = _e1.evaluate_scalar(index);
            return t0.issub();
        }
    };

}
}

#endif

