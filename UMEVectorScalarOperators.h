#ifndef UME_VECTOR_SCALAR_OPERATORS_H_
#define UME_VECTOR_SCALAR_OPERATORS_H_

namespace UME
{
    namespace BLAS
    {

        // Templated operator to handle '+' expression with scalar LH operand.
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), E1, E2> operator+ (ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E1> & srcA, ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E2> & srcB) {
            return ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), E1, E2>(srcA, srcB);
        }
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), E1, E2> operator+ (ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E1> && srcA, ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E2> && srcB) {
            return ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), E1, E2>(srcA, srcB);
        }
        template<typename E2>
        inline ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), float, E2> operator+ (float srcA, ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E2> & srcB) {
            return ArithmeticADDExpression<float, E2::TEST_SIMD_VALUE(), float, E2>(srcA, srcB);
        }
        template<typename E2>
        inline ArithmeticADDExpression<double, E2::TEST_SIMD_VALUE(), double, E2> operator+ (double srcA, ArithmeticExpression<float, E2::TEST_SIMD_VALUE(), E2> & srcB) {
            return ArithmeticADDExpression<double, E2::TEST_SIMD_VALUE(), double, E2>(srcA, srcB);
        }

        // Templated operator to handle '*' expression with scalar LH operand.
        template<typename E2>
        inline ArithmeticMULExpression<float, E2::TEST_SIMD_VALUE(), float, E2> operator* (float srcA, E2 & srcB) {
            return ArithmeticMULExpression<float, E2::TEST_SIMD_VALUE(), float, E2>(srcA, srcB);
        }
        template<typename E2>
        inline ArithmeticMULExpression<double, E2::TEST_SIMD_VALUE(), double, E2> operator* (double srcA, E2 & srcB) {
            return ArithmeticMULExpression<double, E2::TEST_SIMD_VALUE(), double, E2>(srcA, srcB);
        }
    }
}

#endif