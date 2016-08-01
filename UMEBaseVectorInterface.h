#ifndef UME_BASE_VECTOR_INTERFACE_H_
#define UME_BASE_VECTOR_INTERFACE_H_

#include <cassert>

#include "UMEVectorExpressions.h"

namespace UME {
namespace VECTOR {

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticBaseVectorInterface :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> {
    protected:
        ~ArithmeticBaseVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;

        // ADD
        template<typename E2>
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> add(SCALAR_TYPE srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
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
        UME_FORCE_INLINE ArithmeticSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> sub(SCALAR_TYPE srcB) {
            return ArithmeticSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
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

        // MMUL
        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> mul(LogicalExpression<E1> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMMULExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> && mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMMULExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        // Partially specialize to support RH scalar operand
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> & mask, SCALAR_TYPE srcB) {
            return ArithmeticMMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> && mask, SCALAR_TYPE srcB) {
            return ArithmeticMMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // MDIV
        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> div(LogicalExpression<E1> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMDIVExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> && mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMDIVExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        // Partially specialize to support RH scalar operand
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> & mask, SCALAR_TYPE srcB) {
            return ArithmeticMDIVExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMDIVExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> && mask, SCALAR_TYPE srcB) {
            return ArithmeticMDIVExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // MSUB
        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> sub(LogicalExpression<E1> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMSUBExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        template<typename E1, typename E2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> && mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMSUBExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        // Partially specialize to support RH scalar operand
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> & mask, SCALAR_TYPE srcB) {
            return ArithmeticMSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }
        template<typename E1>
        UME_FORCE_INLINE ArithmeticMSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(LogicalExpression<E1> && mask, SCALAR_TYPE srcB) {
            return ArithmeticMSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), mask, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
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
        UME_FORCE_INLINE ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fmuladd(
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

        // FADDMUL
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        // Partially specialize to support RH scalar operand
        template<typename E2>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> faddmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> faddmul(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC)
        {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> faddmul(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC)
        {
            return ArithmeticFADDMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        // FMULSUB
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        // Partially specialize to support RH scalar operand
        template<typename E2>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fmulsub(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fmulsub(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC)
        {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fmulsub(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC)
        {
            return ArithmeticFMULSUBExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        // FSUBMUL
        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC) {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        template<typename E2, typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC) {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>(
                (*this),
                srcB,
                srcC);
        }

        // Partially specialize to support RH scalar operand
        template<typename E2>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E2>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> fsubmul(
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB,
            SCALAR_TYPE srcC)
        {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>(
                (*this),
                srcB,
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcC));
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fsubmul(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> & srcC)
        {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
                (*this),
                ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB),
                srcC);
        }

        template<typename E3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3> fsubmul(
            SCALAR_TYPE srcB,
            ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E3> && srcC)
        {
            return ArithmeticFSUBMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>, E3>(
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

        UME_FORCE_INLINE ArithmeticHMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> hmul() {
            return ArithmeticHMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }

        UME_FORCE_INLINE ArithmeticHBANDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> hband() {
            return ArithmeticHBANDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }

        UME_FORCE_INLINE ArithmeticHBORExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> hbor() {
            return ArithmeticHBORExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }

        UME_FORCE_INLINE ArithmeticHBXORExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> hbxor() {
            return ArithmeticHBXORExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }

    };

}
}

#endif

