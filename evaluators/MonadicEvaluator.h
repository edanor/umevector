#pragma once

#include "../UMEVector.h"

namespace UME
{
namespace VECTOR {

// Monadic evaluator can be used to trigger evaluation
// of a single expression.
class MonadicEvaluator {
public:
    // This constructor permits evaluation of expressions with a
    // vector destination.
    template<
        typename SCALAR_TYPE,
        int SIMD_STRIDE,
        typename DST_T,
        typename EXP_T>
    UME_FORCE_INLINE MonadicEvaluator(
        DST_T & dst,
        UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp1);

        for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_exp.evaluate_SIMD(i);
            t0.store(&elements[i]);
        }

        for (int i = reinterpret_exp.LOOP_PEEL_OFFSET(); i < reinterpret_exp.LENGTH(); i++) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_exp.evaluate_scalar(i);
            t1.store(&elements[i]);
        }

        // Dispose of the expression and release all temporary storage.
        reinterpret_exp.dispose();
    }

    // Evaluate expression with scalar destination (e.g. reduction operation)
    template<
        typename SCALAR_TYPE,
        int SIMD_STRIDE,
        typename EXP_T>
    UME_FORCE_INLINE MonadicEvaluator(
            SCALAR_TYPE & dst,
            UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);

        dst = exp1.evaluate_scalar(0);
    }

    // Evaluate expression with implicit destination (e.g. destructive operation).
    template<
        typename SCALAR_TYPE,
        int SIMD_STRIDE,
        typename EXP_T>
        UME_FORCE_INLINE MonadicEvaluator(
            UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        // Need to reinterpret vec to E to propagate to proper expression
        // evaluator.
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);
        for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_exp.evaluate_SIMD(i);
        }

        for (int i = reinterpret_exp.LOOP_PEEL_OFFSET(); i < reinterpret_exp.LENGTH(); i++) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_exp.evaluate_scalar(i);
        }
    }

};




}
}
