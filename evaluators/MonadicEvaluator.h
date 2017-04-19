#pragma once

#include "../UMEVector.h"

#include "../utilities/ExpressionPrinter.h"

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
        int VEC_LEN,
        int SIMD_STRIDE,
        typename EXP_T>
        inline MonadicEvaluator(
        UME::VECTOR::Vector<SCALAR_TYPE, VEC_LEN, SIMD_STRIDE> & dst,
        UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);

        for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            auto t0 = reinterpret_exp.template evaluate<SIMD_STRIDE>(i);
            dst.update<SIMD_STRIDE>(t0, i);
        }

        for (int i = reinterpret_exp.LOOP_PEEL_OFFSET(); i < reinterpret_exp.LENGTH(); i++) {
            auto t1 = reinterpret_exp.template evaluate<1>(i);
            dst.update<1>(t1, i);
        }

        // Dispose of the expression and release all temporary storage.
        reinterpret_exp.dispose();
    }

    // Evaluate expression with scalar destination (e.g. reduction operation)
    template<
        typename SCALAR_TYPE,
        int SIMD_STRIDE,
        typename EXP_T>
        inline MonadicEvaluator(
            SCALAR_TYPE * dst,
            UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);

        UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_exp.template evaluate<1>(0);
        *dst = t1[0];
    }

    // Evaluate expression with no destination, but side-effects (e.g. destructive ADD operation).
    template<
        typename SCALAR_TYPE,
        int SIMD_STRIDE,
        typename EXP_T>
        inline MonadicEvaluator(
            UME::VECTOR::ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, EXP_T> & exp)
    {
        // Need to reinterpret vec to E to propagate to proper expression
        // evaluator.
        EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);
        for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            auto t0 = reinterpret_exp.template evaluate<SIMD_STRIDE>(i);
        }

        for (int i = reinterpret_exp.LOOP_PEEL_OFFSET(); i < reinterpret_exp.LENGTH(); i++) {
            auto t1 = reinterpret_exp.template evaluate<1>(i);
        }
    }

};

}
}
