#ifndef UME_FLOAT_VECTOR_INTERFACE_H_
#define UME_FLOAT_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"
#include "UMEBaseVectorInterface.h"

namespace UME {
namespace VECTOR {

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticFloatVectorInterface :
        public ArithmeticBaseVectorInterface<DERIVED_VECTOR_TYPE, SCALAR_TYPE, SIMD_STRIDE> {
    protected:
        ~ArithmeticFloatVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;
    };

}
}

#endif
