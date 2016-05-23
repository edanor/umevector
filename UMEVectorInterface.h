#ifndef UME_VECTOR_INTERFACE_H_
#define UME_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class Vector;
    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class ColumnVector;

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

        UME_FORCE_INLINE LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> land(bool srcB) {
            return LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        UME_FORCE_INLINE LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator& (bool srcB) {
            return LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> land(E2 & srcB) {
            return LogicalANDExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator& (E2 & srcB) {
            return land(srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator&& (E2 & srcB) {
            return land(srcB);
        }


        UME_FORCE_INLINE LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool> lor(bool srcB) {
            return LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        UME_FORCE_INLINE LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator| (bool srcB) {
            return LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> lor(E2 & srcB) {
            return LogicalORExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator| (E2 & srcB) {
            return lor(srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator|| (E2 & srcB) {
            return lor(srcB);
        }
    };

}
}

namespace UME {
    namespace VECTOR {

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticVectorInterface :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> {
    protected:
        ~ArithmeticVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;

        template<typename E2>
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }
        
        template<typename E2>
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(SCALAR_TYPE srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // MADD
        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMADDExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> && mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMADDExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        // Partially specialize to support RH scalar operand
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> & mask, SCALAR_TYPE srcB) {
            return ArithmeticMADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> && mask, SCALAR_TYPE srcB) {
            return ArithmeticMADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> sub(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> sub(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > sub(SCALAR_TYPE srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // MUL
        template<typename E2>
        UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> mul(SCALAR_TYPE srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // DIV
        template<typename E2>
        UME_FORCE_INLINE ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> div(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticDIVExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> div(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticDIVExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        UME_FORCE_INLINE ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> div(SCALAR_TYPE srcB) {
            return ArithmeticDIVExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // FMULADD
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this), 
                srcB, 
                srcC);
        }

        // Partially specialize to support RH scalar operand
        template<typename E2>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fmuladd (
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }
        template<typename E2>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fmuladd(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }
        template<typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fmuladd(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) 
        {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }
        template<typename E3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fmuladd(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC)
        {
            return ArithmeticFMULADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        UME_FORCE_INLINE ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> postinc() {
            return ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }

        UME_FORCE_INLINE ArithmeticHADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> hadd() {
            return ArithmeticHADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }
    };

}
}

#endif
