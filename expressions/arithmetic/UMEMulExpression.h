#ifndef UME_MUL_EXPRESSION_H_
#define UME_MUL_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
    class ArithmeticMULExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> > {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E2 & _e2;

        bool _e1_ownership;
        bool _e2_ownership;

    public:
        ArithmeticMULExpression(E1 & e1, E2 & e2) :
            _e1(e1), _e2(e2), _e1_ownership(false), _e2_ownership(false) {
        }

        ArithmeticMULExpression(E1 & e1, E2 && e2) :
            _e1(e1),
            _e2(*(new E2(e2))),
            _e1_ownership(false),
            _e2_ownership(true) {}

        ArithmeticMULExpression(E1 && e1, E2 & e2) :
            _e1(*(new E1(e1))),
            _e2(e2),
            _e1_ownership(true),
            _e2_ownership(false) {}

        ArithmeticMULExpression(E1 && e1, E2 && e2) :
            _e1(*(new E1(e1))),
            _e2(*(new E2(e2))),
            _e1_ownership(true),
            _e2_ownership(true) {}

        void dispose() {
            if (_e1_ownership) delete &_e1;
            else _e1.dispose();
            if (_e2_ownership) delete &_e2;
            else _e2.dispose();
        }

        inline SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            return t0.mul(t1);
        }

        inline SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            return t0.mul(t1);
        }
    };

    // MUL
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 * RVALUE Exp2" expressions
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 * Exp2" expressions
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 * RVALUE Exp2" expressions
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator* (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }
    // Operators to handle "Exp1 * scalar" expressions
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator* (
        ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
        SCALAR_TYPE srcB)
    {
        return ArithmeticMULExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> >(
            srcA,
            ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
    }

    // Operators to handle "scalar * Exp1" expressions
    template<typename SCALAR_TYPE, typename E2>
    UME_FORCE_INLINE ArithmeticMULExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator* (
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
