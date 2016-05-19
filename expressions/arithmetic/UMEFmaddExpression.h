#ifndef UME_FMADD_EXPRESSION_H_
#define UME_FMADD_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3>
    class ArithmeticFMULADDExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3> > {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;
        E2 & _e2;
        E3 & _e3;

        bool _e1_ownership;
        bool _e2_ownership;
        bool _e3_ownership;

    public:
        ArithmeticFMULADDExpression(E1 & e1,
            E2 & e2,
            E3 & e3) :
            _e1(e1),
            _e2(e2),
            _e3(e3),
            _e1_ownership(false),
            _e2_ownership(false),
            _e3_ownership(false) {
        }

        ArithmeticFMULADDExpression(E1 && e1, E2 & e2, E3 & e3) :
            _e1(*(new E1(e1))),
            _e2(e2),
            _e3(e3),
            _e1_ownership(true),
            _e2_ownership(false),
            _e3_ownership(false) {}

        ArithmeticFMULADDExpression(E1 & e1, E2 && e2, E3 & e3) :
            _e1(e1),
            _e2(*(new E2(e2))),
            _e3(e3),
            _e1_ownership(false),
            _e2_ownership(true),
            _e3_ownership(false) {}

        ArithmeticFMULADDExpression(E1 & e1, E2 & e2, E3 && e3) :
            _e1(e1),
            _e2(e2),
            _e3(*(new E3(e3))),
            _e1_ownership(false),
            _e2_ownership(false),
            _e3_ownership(true) {}

        ArithmeticFMULADDExpression(E1 && e1, E2 && e2, E3 & e3) :
            _e1(*(new E1(e1))),
            _e2(*(new E2(e2))),
            _e3(e3),
            _e1_ownership(true),
            _e2_ownership(true),
            _e3_ownership(false) {}

        ArithmeticFMULADDExpression(E1 && e1, E2 & e2, E3 && e3) :
            _e1(*(new E1(e1))),
            _e2(e2),
            _e3(*(new E3(e3))),
            _e1_ownership(true),
            _e2_ownership(false),
            _e3_ownership(true) {}

        ArithmeticFMULADDExpression(E1 & e1, E2 && e2, E3 && e3) :
            _e1(e1),
            _e2(*(new E2(e2))),
            _e3(*(new E3(e3))),
            _e1_ownership(false),
            _e2_ownership(true),
            _e3_ownership(true) {}

        ArithmeticFMULADDExpression(E1 && e1, E2 && e2, E3 && e3) :
            _e1(*(new E1(e1))),
            _e2(*(new E2(e2))),
            _e3(*(new E3(e3))),
            _e1_ownership(true),
            _e2_ownership(true),
            _e3_ownership(true) {}

        void dispose() {
            if (_e1_ownership) delete &_e1;
            else _e1.dispose();
            if (_e2_ownership) delete &_e2;
            else _e2.dispose();
            if (_e3_ownership) delete &_e3;
            else _e3.dispose();
        }

        inline SIMD_TYPE evaluate_SIMD(int index)
        {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            auto t2 = _e3.evaluate_SIMD(index);
            return t0.fmuladd(t1, t2);
        }

        inline SIMD_1_TYPE evaluate_scalar(int index)
        {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            auto t2 = _e3.evaluate_scalar(index);
            return t0.fmuladd(t1, t2);
        }
    };

}
}

#endif