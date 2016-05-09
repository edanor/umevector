#ifndef UME_VECTOR_SCALAR_OPERATORS_H_
#define UME_VECTOR_SCALAR_OPERATORS_H_

namespace UME
{
    namespace BLAS
    {
        // ADD
        // Operators to handle "Exp1 + Exp2" expressions.
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E1> & srcA, 
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> & srcB) 
        {
            return ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E1> && srcA, 
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> && srcB) 
        {
            return ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 + float" expressions
        template<typename E1>
        inline ArithmeticADDExpression<float, E1::GET_SIMD_STRIDE(), E1, float> operator+ (
            ArithmeticExpression<float, E1::GET_SIMD_STRIDE(), E1> & srcA, 
            float srcB) 
        {
            return ArithmeticADDExpression<float, E1::GET_SIMD_STRIDE(), E1, float>(srcA, srcB);
        }
        // Operators to handle "float + Exp1" expressions
        template<typename E2>
        inline ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), float, E2> operator+ (
            float srcA,
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<float, E2::GET_SIMD_STRIDE(), float, E2>(srcA, srcB);
        }

        // Operators to handle "Exp1 + Exp2" expressions.
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<double, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<double, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions
        template<typename E1, typename E2>
        inline ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<double, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<double, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 + double" expressions
        template<typename E1>
        inline ArithmeticADDExpression<double, E1::GET_SIMD_STRIDE(), E1, double> operator+ (
            ArithmeticExpression<double, E1::GET_SIMD_STRIDE(), E1> & srcA,
            double srcB)
        {
            return ArithmeticADDExpression<double, E1::GET_SIMD_STRIDE(), E1, double>(srcA, srcB);
        }
        // Operators to handle "double + Exp1" expressions
        template<typename E2>
        inline ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), double, E2> operator+ (
            double srcA,
            ArithmeticExpression<double, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<double, E2::GET_SIMD_STRIDE(), double, E2>(srcA, srcB);
        }

        // MUL

        template<typename E1, typename E2>
        inline ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions
        template<typename E1, typename E2>
        inline ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 + float" expressions
        template<typename E1>
        inline ArithmeticMULExpression<float, E1::GET_SIMD_STRIDE(), E1, float> operator* (
            ArithmeticExpression<float, E1::GET_SIMD_STRIDE(), E1> & srcA,
            float srcB)
        {
            return ArithmeticMULExpression<float, E1::GET_SIMD_STRIDE(), E1, float>(srcA, srcB);
        }
        // Operators to handle "float + Exp1" expressions
        template<typename E2>
        inline ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), float, E2> operator* (
            float srcA,
            ArithmeticExpression<float, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), float, E2>(srcA, srcB);
        }

        /*
        // Templated operator to handle '*' expression with scalar LH operand.
        template<typename E2>
        inline ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), float, E2> operator* (float srcA, E2 & srcB) {
            return ArithmeticMULExpression<float, E2::GET_SIMD_STRIDE(), float, E2>(srcA, srcB);
        }
        template<typename E2>
        inline ArithmeticMULExpression<double, E2::GET_SIMD_STRIDE(), double, E2> operator* (double srcA, E2 & srcB) {
            return ArithmeticMULExpression<double, E2::GET_SIMD_STRIDE(), double, E2>(srcA, srcB);
        }*/
    }
}

#endif