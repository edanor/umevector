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

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E>
class ArithmeticExpression {
public:
    int LOOP_COUNT() { return static_cast<E&>(*this).LOOP_COUNT(); }

    static constexpr int GET_SIMD_STRIDE() { return SIMD_STRIDE; }

    operator E&() { return static_cast<E&>(*this); }
    operator E const&() const { return static_cast<const E&>(*this); }

    void dispose() {}
};


template<typename SCALAR_TYPE, int SIMD_STRIDE>
class ScalarExpression : public ArithmeticExpression < SCALAR_TYPE, SIMD_STRIDE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> >
{
    SCALAR_TYPE _e1;

public:
    ScalarExpression(SCALAR_TYPE value) : _e1(value) {}

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> evaluate_SIMD(int index)
    {
        return UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE>(_e1);
    }

    inline UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index)
    {
        return UME::SIMD::SIMDVec<SCALAR_TYPE, 1>(_e1);
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
class ArithmeticADDExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> > {
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;
    E1 & _e1;
    E2 & _e2;

    bool _e1_ownership;
    bool _e2_ownership;

public:
    ArithmeticADDExpression(E1 & e1, E2 & e2) :
        _e1(e1), _e2(e2), _e1_ownership(false), _e2_ownership(false) {
    }

    ArithmeticADDExpression(E1 & e1, E2 && e2) :
        _e1(e1),
        _e2(*(new E2(e2))),
        _e1_ownership(false),
        _e2_ownership(true) {}

    ArithmeticADDExpression(E1 && e1, E2 & e2) :
        _e1(*(new E1(e1))),
        _e2(e2),
        _e1_ownership(true),
        _e2_ownership(false) {}

    ArithmeticADDExpression(E1 && e1, E2 && e2) :
        _e1(*(new E1(e1))),
        _e2(*(new E2(e2))),
        _e1_ownership(true),
        _e2_ownership(true) {}

    void dispose() {
        if (_e1_ownership) delete &_e1;
        else _e1.dispose();
        if (_e2_ownership) delete &_e2;
        else _e2.dispose();
    }

    inline SIMD_TYPE evaluate_SIMD(int index)
    {
        auto t0 = _e1.evaluate_SIMD(index);
        auto t1 = _e2.evaluate_SIMD(index);
        return t0.add(t1);
    }

    inline SIMD_1_TYPE evaluate_scalar(int index)
    {
        auto t0 = _e1.evaluate_scalar(index);
        auto t1 = _e2.evaluate_scalar(index);
        return t0.add(t1);
    }
};

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
    ArithmeticMADDExpression(E1 & e1, E_MASK & e_mask, E2 & e2) : _e1(e1), _e_mask(e_mask), _e2(e2) {}

    inline SIMD_TYPE evaluate_SIMD(int index)
    {
        auto t0 = _e1.evaluate_SIMD(index);
        auto t1 = _e_mask.evaluate_SIMD(index);
        auto t2 = _e2.evaluate_SIMD(index);
        auto t3 = t0.add(t1, t2);
        return t3;
    }

    inline SIMD_1_TYPE evaluate_scalar(int index)
    {
        auto t0 = _e1.evaluate_scalar(index);
        auto t1 = _e_mask.evaluate_scalar(index);
        auto t2 = _e2.evaluate_scalar(index);
        auto t3 = t0.add(t1, t2);
        return t3;
    }
};

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
class ArithmeticMULExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> > {
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

    E1 & _e1;
    E2 & _e2;

    bool _e1_ownership;
    bool _e2_ownership;

public:
    ArithmeticMULExpression(E1 & e1, E2 & e2) : 
        _e1(e1), _e2(e2), _e1_ownership(false), _e2_ownership(false) {
    }

    ArithmeticMULExpression(E1 & e1, E2 && e2) : 
        _e1(e1), 
        _e2(*(new E2(e2))),
        _e1_ownership(false),
        _e2_ownership(true) {}

    ArithmeticMULExpression(E1 && e1, E2 & e2) :
        _e1(*(new E1(e1))),
        _e2(e2),
        _e1_ownership(true),
        _e2_ownership(false) {}

    ArithmeticMULExpression(E1 && e1, E2 && e2) :
        _e1(*(new E1(e1))),
        _e2(*(new E2(e2))),
        _e1_ownership(true),
        _e2_ownership(true) {}

    void dispose() {
        if (_e1_ownership) delete &_e1;
        else _e1.dispose();
        if (_e2_ownership) delete &_e2;
        else _e2.dispose();
    }

    inline SIMD_TYPE evaluate_SIMD(int index)
    {
        auto t0 = _e1.evaluate_SIMD(index);
        auto t1 = _e2.evaluate_SIMD(index);
        return t0.mul(t1);
    }

    inline SIMD_1_TYPE evaluate_scalar(int index) 
    {
        auto t0 = _e1.evaluate_scalar(index);
        auto t1 = _e2.evaluate_scalar(index);
        return t0.mul(t1);
    }
};

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

template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
class ArithmeticPOSTINCExpression : public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, E1> > {
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
    typedef typename UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD_1_TYPE;

    E1 & _e1;

public:
    ArithmeticPOSTINCExpression(E1 & e1) : _e1(e1) {}

    inline SIMD_TYPE evaluate_SIMD(int index)
    {
        auto t0 = _e1.evaluate_SIMD(index);
        auto t1 = t0.postinc();
        _e1.update_SIMD(t0, index); // For postinc expression, the _e1 operand should be a proper lvalue.
        return t1;
    }

    inline SIMD_1_TYPE evaluate_scalar(int index)
    {
        auto t0 = _e1.evaluate_scalar(index);
        auto t1 = t0.postinc();
        _e1.update_scalar(t0, index); // For postinc expression, the _e1 subexpression should be a proper lvalue.
        return t1;
    }
};

#endif
