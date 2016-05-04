#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_


template <typename E>
class ArithmeticExpression {
public:
    int LOOP_COUNT() { return static_cast<E&>(*this).LOOP_COUNT(); }

    operator E&() { return static_cast<E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }

};


template <typename SCALAR_TYPE, int STRIDE, typename E1, typename E2>
class ArithmeticADDExpression : public ArithmeticExpression<ArithmeticADDExpression<SCALAR_TYPE, STRIDE, E1, E2> > {
    E1 & _u;
    E2 & _v;

public:
    ArithmeticADDExpression(ArithmeticExpression<E1> & u, ArithmeticExpression<E2> & v) : _u(u), _v(v) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).add(_v.evaluate_SIMD(index));
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) { 
        return (_u.evaluate_scalar(index)).add(_v.evaluate_scalar(index));
    }
};

template <typename SCALAR_TYPE, int STRIDE, typename E1>
class ArithmeticADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE> : 
    public ArithmeticExpression<ArithmeticADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE> >
{
    E1 & _u;
    SCALAR_TYPE _v;

public:
    ArithmeticADDExpression(ArithmeticExpression<E1> & u, SCALAR_TYPE v) : _u(u), _v(v) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).add(_v);
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).add(_v);
    }
};

template <typename SCALAR_TYPE, int STRIDE, typename E1, typename E2>
class ArithmeticMULExpression : public ArithmeticExpression<ArithmeticMULExpression<SCALAR_TYPE, STRIDE, E1, E2> > {
    E1 & _u;
    E2 & _v;

public:
    ArithmeticMULExpression(ArithmeticExpression<E1> & u, ArithmeticExpression<E2> & v) : _u(u), _v(v) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).mul(_v.evaluate_SIMD(index));
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).mul(_v.evaluate_scalar(index));
    }
};

#endif
