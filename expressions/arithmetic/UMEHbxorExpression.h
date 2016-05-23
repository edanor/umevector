#ifndef UME_HBXOR_EXPRESSION_H_
#define UME_HBXOR_EXPRESSION_H_

namespace UME {
namespace VECTOR {

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
    class ArithmeticHBXORExpression :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticHBXORExpression<SCALAR_TYPE, SIMD_STRIDE, E1> >
    {
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

        E1 & _e1;

        bool _e1_ownership;

        // Value of this expression has to be calculated only once, and can be returned for every
        // call to 'evaluate_SIMD' or 'evaluate_scalar'.
        bool _evaluated;
        SCALAR_TYPE _value; // This value is correct only if 'evaluated == true'

    public:
        UME_FORCE_INLINE ArithmeticHBXORExpression(E1 & e1) :
            _e1(e1),
            _e1_ownership(false),
            _evaluated(false) {}

        UME_FORCE_INLINE ArithmeticHBXORExpression(E1 && e1) :
            _e1(*(new E1(e1))),
            _e1_ownership(true),
            _evaluated(false) {}

        UME_FORCE_INLINE void dispose() {
            if (_e1_ownership) delete &_e1;
            else _e1.dispose();
        }

        // First reduce to scalar and then return
        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index)
        {
            if (!_evaluated) {
                SIMD_TYPE A(SCALAR_TYPE(0));
                int loop_count = _e1.LOOP_PEEL_OFFSET();
                for (int i = 0; i < loop_count; i += SIMD_STRIDE) {
                    SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                    A.bxora(t0);
                }
                _value = A.hbxor();
                for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                    SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                    _value ^= t1[0];
                }
                _evaluated = true;
            }
            return SIMD_TYPE(_value);
        }

        UME_FORCE_INLINE SIMD_1_TYPE evaluate_scalar(int index)
        {
            if (!_evaluated)
            {
                SIMD_TYPE A(SCALAR_TYPE(0));
                for (int i = 0; i < _e1.LOOP_COUNT(); i += SIMD_STRIDE) {
                    SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                    A.bxora(t0);
                }
                _value = A.hbxor();
                for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                    SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                    _value ^= t1[0];
                }
                _evaluated = true;
            }
            return SIMD_1_TYPE(_value);
        }

        // Reduction operations require to be cast-able into scalar types.
        UME_FORCE_INLINE operator SCALAR_TYPE() {
            SIMD_TYPE A(SCALAR_TYPE(0));
            for (int i = 0; i < _e1.LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = _e1.evaluate_SIMD(i);
                A.bxora(t0);
            }
            float B = A.hbxor();
            for (int i = _e1.LOOP_PEEL_OFFSET(); i < _e1.LENGTH(); i++) {
                SIMD_1_TYPE t1 = _e1.evaluate_scalar(i);
                B ^= t1[0];
            }
            return B;
        }
    };

}
}

#endif
