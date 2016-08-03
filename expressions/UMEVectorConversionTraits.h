#ifndef UME_VECTOR_CONVERSION_TRAITS_H_
#define UME_VECTOR_CONVERSION_TRAITS_H_

namespace UME {
namespace VECTOR {
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticITOFExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticFTOIExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticUTOFExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticFTOUExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticUTOIExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticITOUExpression;

    // ITOF
    template<typename T, int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait<int32_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOFExpression<float, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait<int64_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOFExpression<double, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    // FTOI
    template<typename T, int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait<float, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOIExpression<int32_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait<int64_t, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOIExpression<int64_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    // UTOF
    template<typename T, int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait<uint32_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOFExpression<float, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait<uint64_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOFExpression<double, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    // FTOU
    template<typename T, int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait<float, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOUExpression<uint32_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait<uint64_t, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOUExpression<uint64_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    //UTOI
    template<typename T, int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint8_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int8_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint16_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int16_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint32_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int32_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint64_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int64_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    // ITOU
    template<typename T, int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int8_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint8_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int16_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint16_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int32_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint32_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int64_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint64_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };
}
}


#endif