#ifndef UME_VECTOR_SCALAR_OPERATORS_H_
#define UME_VECTOR_SCALAR_OPERATORS_H_

namespace UME
{
    namespace BLAS
    {
        // ADD
        // Operators to handle "Exp1 + Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "Exp1 + RVALUE Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 + Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 + scalar" expressions
        template<typename SCALAR_TYPE, typename E1>
        inline ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator+ (
            ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
            SCALAR_TYPE srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
                srcA, 
                ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> (srcB) );
        }
        // Operators to handle "scalar + Exp1" expressions
        template<typename SCALAR_TYPE, typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator+ (
            SCALAR_TYPE srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
                ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
                srcB);
        }



        // SUB
        // Operators to handle "Exp1 - Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator- (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "Exp1 - RVALUE Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator- (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 - Exp2" expressions.
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator- (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 - RVALUE Exp2" expressions
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator- (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 - scalar" expressions
        template<typename SCALAR_TYPE, typename E1>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator- (
            ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
            SCALAR_TYPE srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
                srcA,
                ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
        }
        // Operators to handle "scalar - Exp1" expressions
        template<typename SCALAR_TYPE, typename E2>
        inline ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator- (
            SCALAR_TYPE srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticSUBExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
                ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
                srcB);
        }


        // MUL
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "Exp1 * RVALUE Exp2" expressions
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 * Exp2" expressions
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }

        // Operators to handle "RVALUE Exp1 * RVALUE Exp2" expressions
        template<typename SCALAR_TYPE, typename E1, typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
        }
        // Operators to handle "Exp1 * scalar" expressions
        template<typename SCALAR_TYPE, typename E1>
        inline ArithmeticMULExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator* (
            ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
            SCALAR_TYPE srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> >(
                srcA, 
                ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
        }

        // Operators to handle "scalar * Exp1" expressions
        template<typename SCALAR_TYPE, typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator* (
            SCALAR_TYPE srcA,
            ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
        {
            return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
                ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA), 
                srcB);
        }
    }
}

#endif