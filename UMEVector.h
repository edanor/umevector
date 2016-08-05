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
#ifndef UME_VECTOR_H_
#define UME_VECTOR_H_

#define UME_DEFAULT_SIMD_STRIDE 4

#include <UMESimd.h>

#include "UMEVectorInterface.h"

#include "expressions/UMEStaticMask.h"
#include "expressions/UMEDynamicMask.h"

#include "expressions/UMEStaticArithmeticUintVector.h"
#include "expressions/UMEDynamicArithmeticUintVector.h"

#include "expressions/UMEStaticArithmeticIntVector.h"
#include "expressions/UMEDynamicArithmeticIntVector.h"

#include "expressions/UMEStaticArithmeticFloatVector.h"
#include "expressions/UMEDynamicArithmeticFloatVector.h"

//#include "UMEVectorOperators.h"


namespace UME {
    namespace VECTOR {
        template<typename SCALAR_T, uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType {
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<uint8_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::UintVector<uint8_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<uint16_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::UintVector<uint16_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<uint32_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::UintVector<uint32_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<uint64_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::UintVector<uint64_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<int8_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::IntVector<int8_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<int16_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::IntVector<int16_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<int32_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::IntVector<int32_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<int64_t, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::IntVector<int64_t, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<float, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::FloatVector<float, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        struct BaseVectorType<double, SIMD_STRIDE, VEC_LEN> {
            typedef typename UME::VECTOR::FloatVector<double, SIMD_STRIDE, VEC_LEN> BASE_T;
        };

        template<typename SCALAR_T, uint32_t SIMD_STRIDE, uint32_t VEC_LEN>
        using Vector = typename BaseVectorType<SCALAR_T, SIMD_STRIDE, VEC_LEN>::BASE_T;
    }
}




#endif
