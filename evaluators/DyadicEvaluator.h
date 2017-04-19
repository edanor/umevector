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
    UME_FORCE_INLINE DyadicEvaluator(
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

        // Dispose of the expression and release all temporary storage.
        reinterpret_exp1.dispose();
        reinterpret_exp2.dispose();
    }
};




}
}
