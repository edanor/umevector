#ifndef UME_ADD_EXPRESSION_H_
#define UME_ADD_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
    class ArithmeticADDExpression :
    public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E2 & _e2;

    public:

        UME_FORCE_INLINE ArithmeticADDExpression(E1 & e1, E2 & e2) :
            _e1(e1), _e2(e2) {}

        UME_FORCE_INLINE ArithmeticADDExpression(E1 & e1, E2 && e2) :
            _e1(e1),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticADDExpression(E1 && e1, E2 & e2) :
            _e1(std::move(e1)),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticADDExpression(E1 && e1, E2 && e2) :
            _e1(std::move(e1)),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            return t0.add(t1);
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            return t0.add(t1);
        }
    };

    // Operators to handle "Exp1 + Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 + RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> & srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 + Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "RVALUE Exp1 + RVALUE Exp2" expressions.
    template<typename SCALAR_TYPE, typename E1, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2> operator+ (
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1> && srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> && srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E1, E2>(srcA, srcB);
    }

    // Operators to handle "Exp1 + scalar" expressions.
    template<typename SCALAR_TYPE, typename E1>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()> > operator+ (
        ArithmeticExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1> & srcA,
        SCALAR_TYPE srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE(), E1, ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>>(
            srcA,
            ScalarExpression<SCALAR_TYPE, E1::GET_SIMD_STRIDE()>(srcB));
    }

    // Operators to handle "scalar + Exp1" expressions.
    template<typename SCALAR_TYPE, typename E2>
    UME_FORCE_INLINE ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2> operator+ (
        SCALAR_TYPE srcA,
        ArithmeticExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), E2> & srcB)
    {
        return ArithmeticADDExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE(), ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>, E2>(
            ScalarExpression<SCALAR_TYPE, E2::GET_SIMD_STRIDE()>(srcA),
            srcB);
    }

}
}

#endif
