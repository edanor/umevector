#ifndef UME_SCALAR_EXPRESSION_H_
#define UME_SCALAR_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE>
    class ScalarExpression : public ArithmeticExpression < SCALAR_TYPE, SIMD_STRIDE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> >
    {
        SCALAR_TYPE _e1;

    public:
        UME_FORCE_INLINE ScalarExpression(SCALAR_TYPE value) : _e1(value) {}

        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> evaluate_SIMD(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE>(_e1);
        }

        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, 1>(_e1);
        }
    };
}
}
#endif
