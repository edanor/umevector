#ifndef UME_FMULADD_EXPRESSION_H_
#define UME_FMULADD_EXPRESSION_H_

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

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3>
    class ArithmeticFMULADDExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>>
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E2 & _e2;
        E3 & _e3;

    public:
        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 & e1,
            E2 & e2,
            E3 & e3) :
            _e1(e1),
            _e2(e2),
            _e3(e3) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 && e1, E2 & e2, E3 & e3) :
            _e1(std::move(e1)),
            _e2(e2),
            _e3(e3) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 & e1, E2 && e2, E3 & e3) :
            _e1(e1),
            _e2(std::move(e2)),
            _e3(e3) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 & e1, E2 & e2, E3 && e3) :
            _e1(e1),
            _e2(e2),
            _e3(std::move(e3)) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 && e1, E2 && e2, E3 & e3) :
            _e1(std::move(e1)),
            _e2(std::move(e2)),
            _e3(e3) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 && e1, E2 & e2, E3 && e3) :
            _e1(std::move(e1)),
            _e2(e2),
            _e3(std::move(e3)) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 & e1, E2 && e2, E3 && e3) :
            _e1(e1),
            _e2(std::move(e2)),
            _e3(std::move(e3)) {}

        UME_FORCE_INLINE ArithmeticFMULADDExpression(E1 && e1, E2 && e2, E3 && e3) :
            _e1(std::move(e1)),
            _e2(std::move(e2)),
            _e3(std::move(e3)) {}

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index) {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            auto t2 = _e3.evaluate_SIMD(index);
            return t0.fmuladd(t1, t2);
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index) {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            auto t2 = _e3.evaluate_scalar(index);
            return t0.fmuladd(t1, t2);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2 > add(T2 && srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2> mul(T2 & srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2 > mul(T2 && srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2> div(T2 & srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2 > div(T2 && srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2> sub(T2 & srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            T2 > sub(T2 && srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                T2> (*this, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3>,
                E_MASK,
                T2> (*this, mask, srcB);
        }
    };

}
}

#endif
