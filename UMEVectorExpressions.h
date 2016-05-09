#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_

template<typename E>
class LogicalExpression{
public:
    operator E&() { return static_cast<E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }
};

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

template<int STRIDE, typename E1, typename E2>
class LogicalORExpression : public LogicalExpression < LogicalORExpression<STRIDE, E1, E2> > {
    E1 & _e1;
    E2 & _e2;

public:
    LogicalORExpression(LogicalExpression<E1> & e1, LogicalExpression<E2> & e2) : _e1(e1), _e2(e2) {
    }

    inline UME::SIMD::SIMDVecMask<STRIDE> evaluate_SIMD(int index) {
        auto t0 = _e1.evaluate_SIMD(index);
        auto t1 = _e2.evaluate_SIMD(index);
        auto t2 = t0.lor(t1);
        return t2;
    }
    inline UME::SIMD::SIMDVecMask<1> evaluate_scalar(int index) {
        auto t0 = _e1.evaluate_scalar(index);
        auto t1 = _e2.evaluate_scalar(index);
        auto t2 = t0.lor(t1);
        return t2;
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename T>
class ArithmeticEvaluatorHelper {
public:
    static inline auto evaluate_SIMD(T & element, int index)  ->
        decltype (element.evaluate_SIMD(index))
    {
        return element.evaluate_SIMD(index);
    }

    static inline auto evaluate_scalar(T & element, int index)  ->
        decltype (element.evaluate_scalar(index))
    {
        return element.evaluate_scalar(index);
    }
};

// Define specializations for scalar types:
template<int SIMD_STRIDE>
class ArithmeticEvaluatorHelper<float, SIMD_STRIDE, float> {
public:
    static inline UME::SIMD::SIMDVec<float, SIMD_STRIDE> evaluate_SIMD(float element, int index) {
        return  UME::SIMD::SIMDVec<float, SIMD_STRIDE>(element);
    }
    static inline UME::SIMD::SIMDVec<float, 1> evaluate_scalar(float element, int index) {
        return UME::SIMD::SIMDVec<float, 1>(element);
    }
};

template<int SIMD_STRIDE>
class ArithmeticEvaluatorHelper<double, SIMD_STRIDE, double> {
public:
    static inline UME::SIMD::SIMDVec<double, SIMD_STRIDE> evaluate_SIMD(double element, int index) {
        return  UME::SIMD::SIMDVec<double, SIMD_STRIDE>(element);
    }
    static inline UME::SIMD::SIMDVec<double, 1> evaluate_scalar(double element, int index) {
        return UME::SIMD::SIMDVec<double, 1>(element);
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E>
class ArithmeticExpression {
public:
    int LOOP_COUNT() { return static_cast<E&>(*this).LOOP_COUNT(); }

    static constexpr int GET_SIMD_STRIDE() { return SIMD_STRIDE; }

    operator E&() { return static_cast<E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
class ArithmeticADDExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> > {

    E1 & _e1;
    E2 & _e2;

public:
    ArithmeticADDExpression(E1 & e1, E2 & e2) : _e1(e1), _e2(e2) {}

    inline auto evaluate_SIMD(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index).add(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index))
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index);
        return t0.add(t1);
    }

    inline auto evaluate_scalar(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index).add(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_scalar(_e2, index))
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_scalar(_e2, index);
        return t0.add(t1);
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2>
class ArithmeticMADDExpression : 
    public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E_MASK, E2> >
{
    E1 & _e1;
    E_MASK & _e_mask;
    E2 & _e2;

public:
    ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 & e2) : _e1(e1), _e_mask(e_mask), _e2(e2) {}

    inline auto evaluate_SIMD(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index).add(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E_MASK>::evaluate_SIMD(_e_mask, index),
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index)
                )
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E_MASK>::evaluate_SIMD(_e_mask, index);
        auto t2 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index);
        auto t3 = t0.add(t1, t2);
        return t3;
    }

    inline auto evaluate_scalar(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E1>::evaluate_scalar(_e1, index).add(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E_MASK>::evaluate_scalar(_e_mask, index),
                ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E2>::evaluate_scalar(_e2, index)
                )
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E1>::evaluate_scalar(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E_MASK>::evaluate_scalar(_e_mask, index);
        auto t2 = ArithmeticEvaluatorHelper<SCALAR_TYPE, 1, E2>::evaluate_scalar(_e2, index);
        auto t3 = t0.add(t1, t2);
        return t3;
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
class ArithmeticMULExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> > {
    E1 & _e1;
    E2 & _e2;

public:
    ArithmeticMULExpression(E1 & e1, E2 & e2) : _e1(e1), _e2(e2) {
    }

    inline auto evaluate_SIMD(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index).mul(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index))
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_SIMD(_e2, index);
        return t0.mul(t1);
    }

    inline auto evaluate_scalar(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index).mul(
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_scalar(_e2, index))
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index);
        auto t1 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E2>::evaluate_scalar(_e2, index);
        return t0.mul(t1);
    }
};

/*
template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
class ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, SCALAR_TYPE> :
    public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, SCALAR_TYPE> >
{
    E1 & _u;
    SCALAR_TYPE _v;

public:
    ArithmeticMULExpression(E1 & u, SCALAR_TYPE v) : _u(u), _v(v) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).mul(_v);
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).mul(_v);
    }
};*/
/*
// FMULADD(VEC, VEC, VEC)
template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3>
class ArithmeticFMULADDExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2, E3> > {
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

// FMULADD(VEC, VEC, SCALAR_TYPE)
template <typename SCALAR_TYPE, int STRIDE, typename E1, typename E2>
class ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, E2, SCALAR_TYPE> : 
    public ArithmeticExpression<ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, E2, SCALAR_TYPE> > 
{
    E1 & _u;
    E2 & _v;
    SCALAR_TYPE _w;

public:
    ArithmeticFMULADDExpression(
        ArithmeticExpression<E1> & u,
        ArithmeticExpression<E2> & v,
        SCALAR_TYPE w) : _u(u), _v(v), _w(w) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        // UME::SIMD does not support scalar operands for FMULADD. For the time being 
        // this can be patched here.
        auto t0 = _u.evaluate_SIMD(index);
        auto t1 = _v.evaluate_SIMD(index);
        auto t2 = t0.mul(t1);
        auto t3 = t2.add(_w);
        return t3;
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        // UME::SIMD does not support scalar operands for FMULADD. For the time being 
        // this can be patched here.
        auto t0 = _u.evaluate_scalar(index);
        auto t1 = _v.evaluate_scalar(index);
        auto t2 = t0.mul(t1);
        auto t3 = t2.add(_w);
        return t3;
    }
};


// FMULADD(VEC, SCALAR_TYPE, VEC)
template <typename SCALAR_TYPE, int STRIDE, typename E1, typename E3>
class ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE, E3> :
    public ArithmeticExpression<ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE, E3> >
{
    E1 & _u;
    SCALAR_TYPE _v;
    E3 & _w;

public:
    ArithmeticFMULADDExpression(
        ArithmeticExpression<E1> & u,
        SCALAR_TYPE v,
        ArithmeticExpression<E3> & w) : _u(u), _v(v), _w(w) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        // UME::SIMD does not support scalar operands for FMULADD. For the time being 
        // this can be patched here.
        auto t0 = _u.evaluate_SIMD(index);
        auto t1 = _w.evaluate_SIMD(index);
        auto t2 = t0.mul(_v);
        auto t3 = t2.add(t1);
        return t3;
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        // UME::SIMD does not support scalar operands for FMULADD. For the time being 
        // this can be patched here.
        auto t0 = _u.evaluate_scalar(index);
        auto t1 = _w.evaluate_scalar(index);
        auto t2 = t0.mul(_v);
        auto t3 = t2.add(t1);
        return t3;
    }
};

// FMULADD (VEC, SCALAR, SCALAR)
template <typename SCALAR_TYPE, int STRIDE, typename E1>
class ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE, SCALAR_TYPE> : 
    public ArithmeticExpression<ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, E1, SCALAR_TYPE, SCALAR_TYPE> > 
{
    E1 & _u;
    SCALAR_TYPE _v;
    SCALAR_TYPE _w;

public:
    ArithmeticFMULADDExpression(
        ArithmeticExpression<E1> & u,
        SCALAR_TYPE v,
        SCALAR_TYPE w) : _u(u), _v(v), _w(w) {
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> evaluate_SIMD(int index) {
        return (_u.evaluate_SIMD(index)).fmuladd(_v, _w);
    }
    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index) {
        return (_u.evaluate_scalar(index)).fmuladd(_v, _w);
    }
};*/

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
class ArithmeticPOSTINCExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, E1> > {
    E1 & _e1;

public:
    ArithmeticPOSTINCExpression(E1 & e1) : _e1(e1) {}


    inline auto evaluate_SIMD(int index) ->
        decltype (
                ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index).postinc()
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_SIMD(_e1, index);
        auto t1 = t0.postinc();
        _e1.update_SIMD(t0, index);
        return t1;
    }

    inline auto evaluate_scalar(int index) ->
        decltype (
            ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index).postinc()
            )
    {
        auto t0 = ArithmeticEvaluatorHelper<SCALAR_TYPE, SIMD_STRIDE, E1>::evaluate_scalar(_e1, index);
        auto t1 = t0.postinc();
        _e1.update_scalar(t0, index);
        return t1;
    }
};

#endif
