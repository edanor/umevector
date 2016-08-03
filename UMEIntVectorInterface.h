#ifndef UME_INT_VECTOR_INTERFACE_H_
#define UME_INT_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"
#include "UMEBaseVectorInterface.h"

namespace UME {
namespace VECTOR {

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticIntVectorInterface :
        public ArithmeticBaseVectorInterface< DERIVED_VECTOR_TYPE, SCALAR_TYPE, SIMD_STRIDE> {
    protected:
        ~ArithmeticIntVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;

        typedef typename UME::SIMD::SIMDTraits<SIMD_TYPE>::SCALAR_FLOAT_T SCALAR_FLOAT_TYPE;

        UME_FORCE_INLINE ArithmeticITOFExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> itof() {
            return ArithmeticITOFExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }
    };

}
}

#endif

