#pragma once

#include "../UMEVector.h"

#include <assert.h>

#pragma warning("Triadic evaluator is an experimental feature.")

namespace UME
{
    namespace VECTOR {

// This class allows calculation of the depth of an expression. Terminal nodes
// have depth equal to '1'.
//
// The implementation is type oriented, so it should be statically deducible
// leading to efficient compiler const-optimizations. The idea is to force
// the compiler to perform as much computation as possible during compile
// time.
template<typename SCALAR_TYPE, int SIMD_STRIDE>
class ExpressionDepth{
public:
    int depth;

    template<typename E1>
    UME_FORCE_INLINE ExpressionDepth(E1 & exp) {
        assert(false);
        static_assert(false, "Error");
    }

    UME_FORCE_INLINE ExpressionDepth(UME::VECTOR::Scalar<SCALAR_TYPE, SIMD_STRIDE> & exp) {
        depth = 1;
    }

    template<int VEC_LEN>
    UME_FORCE_INLINE ExpressionDepth(UME::VECTOR::FloatVector<SCALAR_TYPE, VEC_LEN, SIMD_STRIDE> & exp) {
        depth = 1;
    }

    // FTOI
    template<typename E1>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticFTOIExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp) {
        // SCALAR_TYPE has to be int
        // We therefor need to get a correlated 'float' type
        typedef typename UME::SIMD::SIMDTraits<UME::SIMD::SIMDVec<SCALAR_TYPE, 1>>::SCALAR_FLOAT_T SCALAR_FLOAT_T;

        // Next 'depth' counter has to be of derived type.
        ExpressionDepth<SCALAR_FLOAT_T, SIMD_STRIDE> e1_depth(exp._e1);

        depth = e1_depth.depth + 1;
    }

    // ADD
    template<typename E1, typename E2>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp) {
        ExpressionDepth e1_depth(exp._e1);
        ExpressionDepth e2_depth(exp._e2);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
    }

    // MUL
    template<typename E1, typename E2>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
    }

    // DIV
    template<typename E1, typename E2>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
    }

    // SQRT
    template<typename E1>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticSQRTExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        depth = e1_depth.depth + 1;
    }

    // BLEND
    template<typename E1, typename E_MASK, typename E2>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticBLENDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> emask_depth(exp._e_mask);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);

        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
        depth = emask_depth.depth > depth ? emask_depth.depth + 1 : depth;
    }

    // CMPLT
    template<typename E1, typename E2>
    UME_FORCE_INLINE ExpressionDepth(LogicalCMPLTExpression<SIMD_STRIDE, E1, E2> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
    }

    // CMPGE
    template<typename E1, typename E2>
    UME_FORCE_INLINE ExpressionDepth(LogicalCMPGEExpression<SIMD_STRIDE, E1, E2> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
    }

    // FMULADD
    template<typename E1, typename E2, typename E3>
    UME_FORCE_INLINE ExpressionDepth(ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3> & exp) {
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e1_depth(exp._e1);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e2_depth(exp._e2);
        ExpressionDepth<SCALAR_TYPE, SIMD_STRIDE> e3_depth(exp._e3);
        depth = e1_depth.depth > e2_depth.depth ? e1_depth.depth + 1 : e2_depth.depth + 1;
        depth = depth > e3_depth.depth ? e3_depth.depth + 1 : depth;
    }
    //
};


// This class is used to compare two expressions.
// Both subexpressions are compared for both structure and terminal symbols
// equality.
// The implementation is type oriented, so it should be statically deducible
// leading to efficient compiler const-optimizations. The idea is to force
// the compiler to perform as much computation as possible during compile
// time.
template<int SIMD_STRIDE>
class CompareExpressions {
public:
    bool value;

    // By default assume that the expressions are different.
    template<typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(E1 & exp1, E2 & exp2) {
        value = false;
    }

    template<typename SCALAR_TYPE, int VEC_LEN>
    UME_FORCE_INLINE CompareExpressions(Scalar<SCALAR_TYPE, SIMD_STRIDE> & exp1, Scalar<SCALAR_TYPE, SIMD_STRIDE> & exp2) {
        value = exp1._e1 == exp2._e1;
    }

    template<typename SCALAR_TYPE, int VEC_LEN>
    UME_FORCE_INLINE CompareExpressions(FloatVector<SCALAR_TYPE, VEC_LEN, SIMD_STRIDE> & exp1, FloatVector<SCALAR_TYPE, VEC_LEN, SIMD_STRIDE> & exp2) {
        value = exp1.elements == exp2.elements;
    }

    // FTOI
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticFTOIExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp1,
        ArithmeticFTOIExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        value = comp1.value;
    }

    // ADD
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp1,
        ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value;
    }

    // MUL
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp1,
        ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value;
    }

    // DIV
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp1,
        ArithmeticDIVExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value;
    }

    // SQRT
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticSQRTExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp1,
        ArithmeticSQRTExpression<SCALAR_TYPE, SIMD_STRIDE, E1> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);

        value = comp1.value;
    }

    // BLEND
    template<typename SCALAR_TYPE, typename E1, typename E_MASK, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticBLENDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> & exp1,
        ArithmeticBLENDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e_mask, exp2._e_mask);
        CompareExpressions comp3(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value && comp3.value;
    }

    // CMPLT
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        LogicalCMPLTExpression<SIMD_STRIDE, E1, E2> & exp1,
        LogicalCMPLTExpression<SIMD_STRIDE, E1, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value;
    }

    // CMPGE
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE CompareExpressions(
        LogicalCMPGEExpression<SIMD_STRIDE, E1, E2> & exp1,
        LogicalCMPGEExpression<SIMD_STRIDE, E1, E2> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);

        value = comp1.value && comp2.value;
    }

    // FMULADD
    template<typename SCALAR_TYPE, typename E1, typename E2, typename E3>
    UME_FORCE_INLINE CompareExpressions(
        ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3> & exp1,
        ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3> & exp2)
    {
        CompareExpressions comp1(exp1._e1, exp2._e1);
        CompareExpressions comp2(exp1._e2, exp2._e2);
        CompareExpressions comp2(exp1._e3, exp2._e3);

        value = comp1.value && comp2.value && comp3.value;
    }

};

class TriadicEvaluator {
public:
    template<
        typename SCALAR_TYPE1,
        typename SCALAR_TYPE2,
        typename SCALAR_TYPE3,
        int SIMD_STRIDE,
        typename VEC1_T,
        typename VEC2_T,
        typename VEC3_T,
        typename EXP1,
        typename EXP2,
        typename EXP3>
    UME_FORCE_INLINE TriadicEvaluator (
        VEC1_T & dst1,
        UME::VECTOR::ArithmeticExpression<SCALAR_TYPE1, SIMD_STRIDE, EXP1> & exp1,
        VEC2_T & dst2,
        UME::VECTOR::ArithmeticExpression<SCALAR_TYPE2, SIMD_STRIDE, EXP2> & exp2,
        VEC3_T & dst3,
        UME::VECTOR::ArithmeticExpression<SCALAR_TYPE3, SIMD_STRIDE, EXP3> & exp3
        )
    {
        // Need to reinterpret expressions to to propagate to proper expression
        // evaluator.
        EXP1 & reinterpret_exp1 = static_cast<EXP1 &>(exp1);
        EXP2 & reinterpret_exp2 = static_cast<EXP2 &>(exp2);
        EXP3 & reinterpret_exp3 = static_cast<EXP3 &>(exp3);

        assert(dst1.LENGTH() == dst2.LENGTH());
        assert(dst1.LENGTH() == dst3.LENGTH());
        // TODO: transform original expression

        //ExpressionDepth<SCALAR_TYPE1, SIMD_STRIDE> depth1(reinterpret_exp1);
        //ExpressionDepth<SCALAR_TYPE2, SIMD_STRIDE> depth2(reinterpret_exp2);
        //ExpressionDepth<SCALAR_TYPE3, SIMD_STRIDE> depth3(reinterpret_exp3);

        // std::cout << "Exp1 depth: " << depth1.depth << "\n";
        // std::cout << "Exp2 depth: " << depth2.depth << "\n";
        // std::cout << "Exp3 depth: " << depth3.depth << "\n";

        //CompareExpressions<SIMD_STRIDE> cmp1(reinterpret_exp1, reinterpret_exp2);

        for (int i = 0; i < dst1.LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
            UME::SIMD::SIMDVec<SCALAR_TYPE1, SIMD_STRIDE> t0 = reinterpret_exp1.evaluate_SIMD(i);
            UME::SIMD::SIMDVec<SCALAR_TYPE2, SIMD_STRIDE> t1 = reinterpret_exp2.evaluate_SIMD(i);
            UME::SIMD::SIMDVec<SCALAR_TYPE3, SIMD_STRIDE> t2 = reinterpret_exp3.evaluate_SIMD(i);
            t0.store(&dst1.elements[i]);
            t1.store(&dst2.elements[i]);
            t2.store(&dst3.elements[i]);
        }

        for (int i = dst1.LOOP_PEEL_OFFSET(); i < dst1.LENGTH(); i++) {
            UME::SIMD::SIMDVec<SCALAR_TYPE1, 1> t0 = reinterpret_exp1.evaluate_scalar(i);
            UME::SIMD::SIMDVec<SCALAR_TYPE2, 1> t1 = reinterpret_exp2.evaluate_scalar(i);
            UME::SIMD::SIMDVec<SCALAR_TYPE3, 1> t2 = reinterpret_exp3.evaluate_scalar(i);
            t0.store(&dst1.elements[i]);
            t1.store(&dst2.elements[i]);
            t2.store(&dst3.elements[i]);
        }
    }
};

    }
}