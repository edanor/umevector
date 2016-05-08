#ifndef UME_VECTOR_SCALAR_OPERATORS_H_
#define UME_VECTOR_SCALAR_OPERATORS_H_

namespace UME
{
    namespace BLAS
    {

        // Templated operator to handle '+' expression with scalar LH operand.
        template<typename E2>
        inline ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), float, E2> operator+ (float srcA, E2 & srcB) {
            return ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), float, E2>(srcA, srcB);
        }
        template<typename E2>
        inline ArithmeticADDExpression<double, E2::TEST_SIMD_VALUE(), double, E2> operator+ (double srcA, E2 & srcB) {
            return ArithmeticADDExpression<double, E2::TEST_SIMD_VALUE(), double, E2>(srcA, srcB);
        }
    }
}

#endif