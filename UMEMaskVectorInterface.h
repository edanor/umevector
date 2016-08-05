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
#ifndef UME_MASK_VECTOR_INTERFACE_H_
#define UME_MASK_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class UintVector;
    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class IntVector;
    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class FloatVector;

    template<int VEC_LEN, int SIMD_STRIDE> class MaskVector;

    // Vectors of DYNAMIC_LENGTH may have lengths that
    // are unknowns at compile time. While the internal behaviour 
    // is different than for static vector lengths, the interoperation
    // of static and dynamic vectors should still take place correctly,
    // as long as vector lengths are the same. For performance reasons
    // it is best to use static vectors since then it is possible for the
    // compiler to perform additional code optimizations.
    const int DYNAMIC_LENGTH = -1;

    template<
        typename DERIVED_MASK_TYPE,
        int STRIDE>
    class MaskInterface :
        public LogicalExpression<DERIVED_MASK_TYPE> {
    protected:
        ~MaskInterface() {}

    public: 
        typedef UME::SIMD::SIMDVecMask<STRIDE> SIMD_TYPE;

        UME_FORCE_INLINE LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> land(bool srcB) {
            return LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        UME_FORCE_INLINE LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator& (bool srcB) {
            return LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> land(E2 & srcB) {
            return LogicalLANDExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator& (E2 & srcB) {
            return land(srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator&& (E2 & srcB) {
            return land(srcB);
        }


        UME_FORCE_INLINE LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, bool> lor(bool srcB) {
            return LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        UME_FORCE_INLINE LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator| (bool srcB) {
            return LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, E2> lor(E2 & srcB) {
            return LogicalLORExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator| (E2 & srcB) {
            return lor(srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalLORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator|| (E2 & srcB) {
            return lor(srcB);
        }
    };

}
}

#endif
