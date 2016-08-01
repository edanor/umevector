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
