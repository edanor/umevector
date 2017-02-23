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

// The stride can and should be controlled by the user, depending
// on the algorithm and hardware used. This default is provided
// so that it is possible to simplify some code examples, rather than
// as a hard setting.
#define UME_DEFAULT_SIMD_STRIDE 8

// Vectors of DYNAMIC_LENGTH may have lengths that
// are unknowns at compile time. While the internal behaviour 
// is different than for static vector lengths, the interoperation
// of static and dynamic vectors should still take place correctly,
// as long as vector lengths are the same. For performance reasons
// it is best to use static vectors since then it is possible for the
// compiler to perform additional code optimizations.
const int UME_DYNAMIC_LENGTH = -1;

#include <umesimd/UMESimd.h>

#include "UMEVectorInterface.h"

#include "terminals/UMEStaticMask.h"
#include "terminals/UMEDynamicMask.h"

#include "terminals/UMEStaticArithmeticUintVector.h"
#include "terminals/UMEDynamicArithmeticUintVector.h"

#include "terminals/UMEStaticArithmeticIntVector.h"
#include "terminals/UMEDynamicArithmeticIntVector.h"

#include "terminals/UMEStaticArithmeticFloatVector.h"
#include "terminals/UMEDynamicArithmeticFloatVector.h"


namespace UME {
    namespace VECTOR {
        template<typename SCALAR_T, uint32_t SIMD_STRIDE = UME_DEFAULT_SIMD_STRIDE, uint32_t VEC_LEN = UME_DYNAMIC_LENGTH>
        struct BaseVectorType {
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<uint8_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::UintVector<uint8_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<uint16_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::UintVector<uint16_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<uint32_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::UintVector<uint32_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<uint64_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::UintVector<uint64_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<int8_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::IntVector<int8_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<int16_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::IntVector<int16_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<int32_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::IntVector<int32_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<int64_t, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::IntVector<int64_t, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<float, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::FloatVector<float, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<uint32_t VEC_LEN, uint32_t SIMD_STRIDE>
        struct BaseVectorType<double, VEC_LEN, SIMD_STRIDE> {
            typedef typename UME::VECTOR::FloatVector<double, VEC_LEN, SIMD_STRIDE> BASE_T;
        };

        template<typename SCALAR_T, uint32_t VEC_LEN = UME_DYNAMIC_LENGTH, uint32_t SIMD_STRIDE = UME_DEFAULT_SIMD_STRIDE>
        using Vector = typename BaseVectorType<SCALAR_T, VEC_LEN, SIMD_STRIDE>::BASE_T;

    }
}




#endif
