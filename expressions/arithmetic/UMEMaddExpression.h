#ifndef UME_MADD_EXPRESSION_H_
#define UME_MADD_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2>
    class ArithmeticMADDExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E_MASK & _e_mask;
        E2 & _e2;

        bool _e1_ownership;
        bool _e_mask_ownership;
        bool _e2_ownership;

    public:
        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(e2),
            _e1_ownership(false),
            _e_mask_ownership(false),
            _e2_ownership(false) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK & e_mask, E2 & e2) :
            _e1(*(new E1(e1))),
            _e_mask(e_mask),
            _e2(e2),
            _e1_ownership(true),
            _e_mask_ownership(false),
            _e2_ownership(false) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK && e_mask, E2 & e2) :
            _e1(e1),
            _e_mask(*(new E_MASK(e_mask))),
            _e2(e2),
            _e1_ownership(false),
            _e_mask_ownership(true),
            _e2_ownership(false) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(e_mask),
            _e2(*(new E2(e2))),
            _e1_ownership(false),
            _e_mask_ownership(false),
            _e2_ownership(true) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK && e_mask, E2 & e2) :
            _e1(*(new E1(e1))),
            _e_mask(*(new E_MASK(e_mask))),
            _e2(e2),
            _e1_ownership(true),
            _e_mask_ownership(true),
            _e2_ownership(false) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK & e_mask, E2 && e2) :
            _e1(*(new E1(e1))),
            _e_mask(e_mask),
            _e2(*(new E2(e2))),
            _e1_ownership(true),
            _e_mask_ownership(false),
            _e2_ownership(true) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 & e1, E_MASK && e_mask, E2 && e2) :
            _e1(e1),
            _e_mask(*(new E_MASK(e_mask))),
            _e2(*(new E2(e2))),
            _e1_ownership(false),
            _e_mask_ownership(true),
            _e2_ownership(true) {}

        UME_FORCE_INLINE ArithmeticMADDExpression(E1 && e1, E_MASK && e_mask, E2 && e2) :
            _e1(*(new E1(e1))),
            _e_mask(*(new E_MASK(e_mask))),
            _e2(*(new E2(e2))),
            _e1_ownership(false),
            _e_mask_ownership(true),
            _e2_ownership(true) {}

        UME_FORCE_INLINE void dispose() {
            if (_e1_ownership) delete &_e1;
            else _e1.dispose();
            if (_e_mask_ownership) delete &_e_mask;
            else _e_mask.dispose();
            if (_e2_ownership) delete &_e2;
            else _e2.dispose();
        }

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
    };

}
}

#endif
