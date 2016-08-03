#ifndef UME_ADD_EXPRESSION_H_
#define UME_ADD_EXPRESSION_H_

#include "../UMEVectorConversionTraits.h"

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

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTINCExpression;

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

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2> add(T2 & srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2 > add(T2 && srcB)
        {
            return ArithmeticADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2> mul(T2 & srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2 > mul(T2 && srcB)
        {
            return ArithmeticMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2> div(T2 & srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2 > div(T2 && srcB)
        {
            return ArithmeticDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2> sub(T2 & srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename T2>
        UME_FORCE_INLINE ArithmeticSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2 > sub(T2 && srcB)
        {
            return ArithmeticSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2> (*this, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> add(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> add(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> mul(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> mul(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> div(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMDIVExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> div(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMDIVExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 & srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> sub(E_MASK & mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename E_MASK, typename T2>
        UME_FORCE_INLINE ArithmeticMSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            E_MASK,
            T2> sub(E_MASK && mask, T2 && srcB)
        {
            return ArithmeticMSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                E_MASK,
                T2> (*this, mask, srcB);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmuladd(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmuladd(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> faddmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFADDMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> faddmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFADDMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmulsub(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFMULSUBExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fmulsub(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFMULSUBExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 & srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fsubmul(T2 & srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        template<typename T2, typename T3>
        UME_FORCE_INLINE ArithmeticFSUBMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>, // this expression
            T2,
            T3> fsubmul(T2 && srcB, T3 && srcC)
        {
            return ArithmeticFSUBMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
                T2,
                T3> (*this, srcB, srcC);
        }

        UME_FORCE_INLINE ArithmeticHADDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> // this expression
            > hadd()
        {
            return ArithmeticHADDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHMULExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> // this expression
            > hmul()
        {
            return ArithmeticHMULExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBANDExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> // this expression
            > hband()
        {
            return ArithmeticHBANDExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> // this expression
            > hbor()
        {
            return ArithmeticHBORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
                > (*this);
        }

        UME_FORCE_INLINE ArithmeticHBXORExpression<
            SCALAR_TYPE,
            SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> // this expression
            > hbxor()
        {
            return ArithmeticHBXORExpression<
                SCALAR_TYPE,
                SIMD_STRIDE,
                ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
                > (*this);
        }

        typedef typename ITOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE ITOF_EXPRESSION_TYPE;
        typedef typename FTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE FTOI_EXPRESSION_TYPE;
        typedef typename UTOFTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE UTOF_EXPRESSION_TYPE;
        typedef typename FTOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE FTOU_EXPRESSION_TYPE;
        typedef typename UTOITrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE UTOI_EXPRESSION_TYPE;
        typedef typename ITOUTrait<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>>::CAST_TYPE ITOU_EXPRESSION_TYPE;

        UME_FORCE_INLINE ITOF_EXPRESSION_TYPE itof() {
            return ITOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOI_EXPRESSION_TYPE ftoi() {
            return FTOI_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE UTOF_EXPRESSION_TYPE utof() {
            return UTOF_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE FTOU_EXPRESSION_TYPE ftou() {
            return FTOU_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE UTOI_EXPRESSION_TYPE utoi() {
            return UTOI_EXPRESSION_TYPE(*this);
        }
        UME_FORCE_INLINE ITOU_EXPRESSION_TYPE itou() {
            return ITOU_EXPRESSION_TYPE(*this);
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
