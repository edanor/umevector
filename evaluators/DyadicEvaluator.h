#pragma once

#include "../UMEVector.h"

namespace UME
{
namespace VECTOR {

// Dyadic evaluator can be used to trigger evaluation
// of a two expressions. Values in destinations are not
// updated until the moment they are known for all
// expressions.
class DyadicEvaluator {
public:
    // This constructor permits evaluation of expressions with a
    // vector destination.
    template<
        typename SCALAR_T_1,
        typename SCALAR_T_2,
        int SIMD_STRIDE,
        typename DST_T_1,
        typename DST_T_2,
        typename EXP_T_1,
        typename EXP_T_2>
    inline DyadicEvaluator(
        DST_T_1 & dst1,
        ArithmeticExpression<SCALAR_T_1, SIMD_STRIDE, EXP_T_1> & exp1,
        DST_T_2 & dst2,
        ArithmeticExpression<SCALAR_T_2, SIMD_STRIDE, EXP_T_2> & exp2)
    {
        EXP_T_1 & reinterpret_exp1 = static_cast<EXP_T_1 &>(exp1);
        EXP_T_2 & reinterpret_exp2 = static_cast<EXP_T_2 &>(exp2);

        assert(dst1.LENGTH() == dst2.LENGTH());

        for (int i = 0; i < dst1.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            auto t0 = reinterpret_exp1.template evaluate<SIMD_STRIDE>(i);
            auto t1 = reinterpret_exp2.template evaluate<SIMD_STRIDE>(i);
            dst1.update<SIMD_STRIDE>(t0, i);
            dst2.update<SIMD_STRIDE>(t1, i);
        }

        for (int i = dst1.LOOP_PEEL_OFFSET(); i < dst1.LENGTH(); i++) {
            auto t0 = reinterpret_exp1.template evaluate<1>(i);
            auto t1 = reinterpret_exp2.template evaluate<1>(i);
            dst1.update<1>(t0, i);
            dst2.update<1>(t1, i);
        }
    }

    template<
        typename SCALAR_T_1,
        typename SCALAR_T_2,
        int SIMD_STRIDE,
        typename EXP_T_1,
        typename EXP_T_2>
    inline DyadicEvaluator(
            SCALAR_T_1 * dst1,
            ArithmeticExpression<SCALAR_T_1, SIMD_STRIDE, EXP_T_1> & exp1,
            SCALAR_T_2 * dst2,
            ArithmeticExpression<SCALAR_T_2, SIMD_STRIDE, EXP_T_2> & exp2)
    {
        // TODO: Assumption made is that both exp1 and exp2 are reduction expressions.
        //       The type hierarchy should be modified, so that a distinct 'ArithmeticReductionExpression'
        //       type was used explicitly. This should reduce confusion an possibly eliminate some practical
        //       problems.
        EXP_T_1 & reinterpret_exp1 = static_cast<EXP_T_1 &>(exp1);
        EXP_T_2 & reinterpret_exp2 = static_cast<EXP_T_2 &>(exp2);

        // Cannot compute using this scheme if the expressions have different lengths.
        // Use monadic evaluation scheme to calculate each of them separately.
        assert(reinterpret_exp1.LENGTH() == reinterpret_exp2.LENGTH());

        // Accumulate values from peel loop
        UME::SIMD::SIMDVec<SCALAR_T_1, SIMD_STRIDE> acc1_SIMD_N = reinterpret_exp1.template neutral_element<SIMD_STRIDE>();
        UME::SIMD::SIMDVec<SCALAR_T_1, SIMD_STRIDE> acc2_SIMD_N = reinterpret_exp2.template neutral_element<SIMD_STRIDE>();
        for (int i = 0; i < reinterpret_exp1.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            acc1_SIMD_N = reinterpret_exp1.template accumulate<SIMD_STRIDE>(i, acc1_SIMD_N);
            acc2_SIMD_N = reinterpret_exp2.template accumulate<SIMD_STRIDE>(i, acc2_SIMD_N);
        }

        // Accumulate valued from remainder loop
        UME::SIMD::SIMDVec<SCALAR_T_1, 1> acc1_SIMD_1 = reinterpret_exp2.template reduce<SIMD_STRIDE>(acc1_SIMD_N);
        UME::SIMD::SIMDVec<SCALAR_T_1, 1> acc2_SIMD_1 = reinterpret_exp2.template reduce<SIMD_STRIDE>(acc2_SIMD_N);
        for (int i = reinterpret_exp1.LOOP_PEEL_OFFSET(); i < reinterpret_exp1.LENGTH(); i++) {
            acc1_SIMD_1 = reinterpret_exp1.template accumulate<1>(i, acc1_SIMD_1);
            acc2_SIMD_1 = reinterpret_exp2.template accumulate<1>(i, acc2_SIMD_1);
        }

        // Perform final reduction
        *dst1 = acc1_SIMD_1[0];
        *dst2 = acc2_SIMD_1[0];
    }

    // First expression evaluates to a vector,
    // second expression evaluates to a scalar.
    template<
        typename SCALAR_T_1,
        typename SCALAR_T_2,
        int SIMD_STRIDE,
        typename DST_T_1,
        typename EXP_T_1,
        typename EXP_T_2>
    inline DyadicEvaluator(
            DST_T_1 & dst1,
            ArithmeticExpression<SCALAR_T_1, SIMD_STRIDE, EXP_T_1> & exp1,
            SCALAR_T_2 * dst2,
            ArithmeticExpression<SCALAR_T_2, SIMD_STRIDE, EXP_T_2> & exp2)
    {
        // TODO: Assumption made is that both exp1 and exp2 are reduction expressions.
        //       The type hierarchy should be modified, so that a distinct 'ArithmeticReductionExpression'
        //       type was used explicitly. This should reduce confusion an possibly eliminate some practical
        //       problems.
        EXP_T_1 & reinterpret_exp1 = static_cast<EXP_T_1 &>(exp1);
        EXP_T_2 & reinterpret_exp2 = static_cast<EXP_T_2 &>(exp2);

        // Cannot compute using this scheme if the expressions have different lengths.
        // Use monadic evaluation scheme to calculate each of them separately.
        assert(reinterpret_exp1.LENGTH() == reinterpret_exp2.LENGTH());

        // Accumulate values from peel loop
        UME::SIMD::SIMDVec<SCALAR_T_1, SIMD_STRIDE> acc2_SIMD_N = reinterpret_exp2.template neutral_element<SIMD_STRIDE>();
        for (int i = 0; i < reinterpret_exp1.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            auto t0 = reinterpret_exp1.template evaluate<SIMD_STRIDE>(i);
            acc2_SIMD_N = reinterpret_exp2.template accumulate<SIMD_STRIDE>(i, acc2_SIMD_N);

            // Partial update after partial evaluation
            dst1.template update<SIMD_STRIDE>(t0, i);
        }

        // Accumulate valued from remainder loop
        UME::SIMD::SIMDVec<SCALAR_T_1, 1> acc2_SIMD_1 = reinterpret_exp2.template reduce<SIMD_STRIDE>(acc2_SIMD_N);
        for (int i = reinterpret_exp1.LOOP_PEEL_OFFSET(); i < reinterpret_exp1.LENGTH(); i++) {
            auto t0 = reinterpret_exp1.template evaluate<1>(i);
            acc2_SIMD_1 = reinterpret_exp2.template accumulate<1>(i, acc2_SIMD_1);

            // Partial update after partial evaluation
            dst1.template update<1>(t0, i);
        }

        // Perform final reduction of the second operand
        *dst2 = acc2_SIMD_1[0];
    }

};




}
}
