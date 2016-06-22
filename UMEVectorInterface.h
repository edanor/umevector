#ifndef UME_VECTOR_INTERFACE_H_
#define UME_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"

namespace UME {
    namespace SIMD {
        template<int SIMD_STRIDE, int VEC_LEN> class MaskVector;
        template<typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE> class UintVector;
        template<typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE> class IntVector;
        template<typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE> class FloatVector;
    }
}

// Vectors of DYNAMIC_LENGTH may have lengths that
// are unknowns at compile time. While the internal behaviour 
// is different than for static vector lengths, the interoperation
// of static and dynamic vectors should still take place correctly,
// as long as vector lengths are the same. For performance reasons
// it is best to use static vectors since then it is possible for the
// compiler to perform additional code optimizations.
const int DYNAMIC_LENGTH = -1;

#include "UMEMaskVectorInterface.h"

#include "UMEBaseVectorInterface.h"
#include "UMEUintVectorInterface.h"
#include "UMEIntVectorInterface.h"
#include "UMEFloatVectorInterface.h"

#endif
