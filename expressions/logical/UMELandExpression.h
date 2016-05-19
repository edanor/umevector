#ifndef UME_LAND_EXPRESSION_H_
#define UME_LAND_EXPRESSION_H_


namespace UME {
namespace VECTOR {
    template<int STRIDE, typename E1, typename E2>
    class LogicalANDExpression : public LogicalExpression < LogicalANDExpression<STRIDE, E1, E2> > {
        E1 & _e1;
        E2 & _e2;

    public:
        LogicalANDExpression(LogicalExpression<E1> & e1, LogicalExpression<E2> & e2) : _e1(e1), _e2(e2) {
        }

        inline UME::SIMD::SIMDVecMask<STRIDE> evaluate_SIMD(int index) {
            auto t0 = _e1.evaluate_SIMD(index);
            auto t1 = _e2.evaluate_SIMD(index);
            auto t2 = t0.land(t1);
            return t2;
        }
        inline UME::SIMD::SIMDVecMask<1> evaluate_scalar(int index) {
            auto t0 = _e1.evaluate_scalar(index);
            auto t1 = _e2.evaluate_scalar(index);
            auto t2 = t0.land(t1);
            return t2;
        }
    };

}
}

#endif
