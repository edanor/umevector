#ifndef UME_MADD_EXPRESSION_H_
#define UME_MADD_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE> class ScalarExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSUBExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2>
    class ArithmeticMADDExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E_MASK & _e_mask;
        E2 & _e2;

    public:
        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK & e_mask, E2 & e2) :
            _e1(std::move(e1)),
            _e_mask(e_mask),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK && e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(std::move(e_mask)),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK && e_mask, E2 & e2) :
            _e1(std::move(e1)),
            _e_mask(std::move(e_mask)),
            _e2(e2) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK & e_mask, E2 && e2) :
            _e1(std::move(e1)),
            _e_mask(e_mask),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK && e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(std::move(e_mask)),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK && e_mask, E2 && e2) :
            _e1(std::move(e1)),
            _e_mask(std::move(e_mask)),
            _e2(std::move(e2)) {}

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e_mask.evaluate_SIMD(index);
            auto t2 = _e2.evaluate_SIMD(index);
            auto t3 = t0.add(t1, t2);
            return t3;
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e_mask.evaluate_scalar(index);
            auto t2 = _e2.evaluate_scalar(index);
            auto t3 = t0.add(t1, t2);
            return t3;
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > add(T2 && srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> mul(T2 & srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > mul(T2 && srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> div(T2 & srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > div(T2 && srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2> sub(T2 & srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2 > sub(T2 && srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2> (*this, srcB);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }
    };

}
}

#endif
