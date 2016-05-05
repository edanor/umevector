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
        auto t0 = _u.evaluate_scalar(index);
        auto t1 = _v.evaluate_scalar(index);
        auto t2 = t0.add(t1);
        return t2;
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

template <typename SCALAR_TYPE, int STRIDE, typename E1>
class ArithmeticMULExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE> :
    public ArithmeticExpression<ArithmeticMULExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE> >
{
    E1 & _u;
    SCALAR_TYPE _v;

public:
    ArithmeticMULExpression(ArithmeticExpression<E1> & u, SCALAR_TYPE v) : _u(u), _v(v) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).mul(_v);
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).mul(_v);
    }
};

template <typename SCALAR_TYPE, int STRIDE, typename E1, typename E2, typename E3>
class ArithmeticFMULADDExpression : public ArithmeticExpression<ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, E2, E3> > {
    E1 & _u;
    E2 & _v;
    E3 & _w;

public:
    ArithmeticFMULADDExpression(
        ArithmeticExpression<E1> & u, 
        ArithmeticExpression<E2> & v,
        ArithmeticExpression<E3> & w) : _u(u), _v(v), _w(w) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).fmuladd(_v.evaluate_SIMD(index), _w.evaluate_SIMD(index));
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).fmuladd(_v.evaluate_scalar(index), _w.evaluate_scalar(index));
    }
};


template <typename SCALAR_TYPE, int STRIDE, typename E1>
class ArithmeticPOSTINCExpression : public ArithmeticExpression<ArithmeticPOSTINCExpression<SCALAR_TYPE, STRIDE, E1> > {
    E1 & _u;

public:
    ArithmeticPOSTINCExpression(ArithmeticExpression<E1> & u) : _u(u) {}

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        auto t0 = _u.evaluate_SIMD(index);
        auto t1 = t0.postinc();
        _u.update_SIMD(t0, index);
        return t1;
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        auto t0 = _u.evaluate_scalar(index);
        auto t1 = t0.postinc();
        _u.update_scalar(t0, index);
        return t1;
    }
};

#endif
