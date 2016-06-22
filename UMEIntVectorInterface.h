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
        public ArithmeticBaseVectorInterface<DERIVED_VECTOR_TYPE, SCALAR_TYPE,  SIMD_STRIDE> {
    protected:
        ~ArithmeticIntVectorInterface() {}

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

        // SUB
        template<typename E2>
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> sub(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> sub(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        //UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > sub(SCALAR_TYPE srcB) {
        //    return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        //}

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
