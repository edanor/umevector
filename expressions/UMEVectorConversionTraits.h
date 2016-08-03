#ifndef UME_VECTOR_CONVERSION_TRAITS_H_
#define UME_VECTOR_CONVERSION_TRAITS_H_

namespace UME {
namespace VECTOR {
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticITOFExpression;

    template<typename T, int SIMD_STRIDE, typename INTEGER_EXP>
    class ITOFTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INTEGER_EXP>
    class ITOFTrait<int32_t, SIMD_STRIDE, INTEGER_EXP> {
    public:
        typedef ArithmeticITOFExpression<float, SIMD_STRIDE, INTEGER_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INTEGER_EXP>
    class ITOFTrait<int64_t, SIMD_STRIDE, INTEGER_EXP> {
    public:
        typedef ArithmeticITOFExpression<double, SIMD_STRIDE, INTEGER_EXP> CAST_TYPE;
    };
}
}


#endif