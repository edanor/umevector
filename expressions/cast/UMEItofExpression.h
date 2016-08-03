#ifndef UME_ITOF_EXPRESSION_H_
#define UME_ITOF_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE> class ScalarExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSUBExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSUBExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template <typename SCALAR_FLOAT_TYPE, int SIMD_STRIDE, typename E1>
    class ArithmeticITOFExpression :
    public ArithmeticExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, ArithmeticITOFExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, E1>>
    {

        typedef typename UME::SIMD::SIMDVec<SCALAR_FLOAT_TYPE, SIMD_STRIDE> SIMD_FLOAT_TYPE;

        typedef typename UME::SIMD::SIMDVec<SCALAR_FLOAT_TYPE, 1> SIMD_1_FLOAT_TYPE;

        E1 & _e1;

    public:

        UME_FORCE_INLINE ArithmeticITOFExpression(E1 & e1) :
            _e1(e1) {}

        UME_FORCE_INLINE ArithmeticITOFExpression(E1 && e1) :
            _e1(std::move(e1)) {}

        UME_FORCE_INLINE SIMD_FLOAT_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            return SIMD_FLOAT_TYPE(t0);
        }

        UME_FORCE_INLINE SIMD_1_FLOAT_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            return SIMD_1_FLOAT_TYPE(t0);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_FLOAT_TYPE,
            SIMD_STRIDE,
            ArithmeticITOFExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, E1>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_FLOAT_TYPE,
                SIMD_STRIDE,
                ArithmeticITOFExpression<SCALAR_FLOAT_TYPE, SIMD_STRIDE, E1>,
                T2>(*this, srcB);
        }
    };

}
}

#endif
