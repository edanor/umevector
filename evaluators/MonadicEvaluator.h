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
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename DST_T,
            typename EXP_T>
            inline MonadicEvaluator(
                DST_T & dst,
                ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> & exp)
        {
            EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);

            for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                auto t0 = reinterpret_exp.template evaluate<SIMD_STRIDE>(i);
                dst.template update<SIMD_STRIDE>(t0, i);
            }

            for (int i = reinterpret_exp.LOOP_PEEL_OFFSET(); i < reinterpret_exp.LENGTH(); i++) {
                auto t1 = reinterpret_exp.template evaluate<1>(i);
                dst.template update<1>(t1, i);
            }

            // Dispose of the expression and release all temporary storage.
            reinterpret_exp.dispose();
        }

        // Evaluate expression with scalar destination (e.g. reduction operation)
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename EXP_T>
            inline MonadicEvaluator(
                SCALAR_T * dst,
                ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> & exp)
        {
            EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);

            UME::SIMD::SIMDVec<SCALAR_T, SIMD_STRIDE> t1 = reinterpret_exp.template evaluate<SIMD_STRIDE>(0);
            *dst = t1[0];
        }

        // Evaluate expression with no destination, but side-effects (e.g. destructive ADD operation).
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename EXP_T>
            inline MonadicEvaluator(
                ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> & exp)
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

        // Evaluate with a comuted scatter indices
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename DST_T,
            typename EXP_T,
            typename EXP_INDICES>
            inline MonadicEvaluator(
                DST_T & dst,
                ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> & exp,
                ArithmeticExpression<uint32_t, SIMD_STRIDE, EXP_INDICES> & exp_indices)
        {
            EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);
            EXP_INDICES & reinterpret_indices = static_cast<EXP_INDICES &>(exp_indices);
            for (int i = 0; i < reinterpret_exp.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                auto t0 = reinterpret_exp.template evaluate<SIMD_STRIDE>(i);
                auto t1 = reinterpret_indices.template evaluate<SIMD_STRIDE>(i);
                dst.template update<SIMD_STRIDE>(t0, t1);
            }
            for (int i = reinterpret_indices.LOOP_PEEL_OFFSET(); i < reinterpret_indices.LENGTH(); i += 1) {
                auto t0 = reinterpret_exp.template evaluate<1>(i);
                auto t1 = reinterpret_indices.template evaluate<1>(i);
                dst.template <update<1>(t0, t1);
            }
        }
    };
}
}
