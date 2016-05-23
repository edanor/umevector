#ifndef UME_POSTINC_EXPRESSION_H_
#define UME_POSTINC_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
    class ArithmeticPOSTINCExpression :
    public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, E1> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;

    public:

        ArithmeticPOSTINCExpression(E1 & e1) : _e1(e1) {}

        inline SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = t0.postinc();
            _e1.update_SIMD(t0, index); // For postinc expression, the _e1 operand should be a proper lvalue.
            return t1;
        }

        inline SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = t0.postinc();
            _e1.update_scalar(t0, index); // For postinc expression, the _e1 subexpression should be a proper lvalue.
            return t1;
        }
    };

}
}

#endif
