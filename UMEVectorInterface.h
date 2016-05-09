#ifndef UME_VECTOR_INTERFACE_H_
#define UME_VECTOR_INTERFACE_H_

#include <cassert>

namespace UME {
namespace BLAS {

#include "UMEVectorExpressions.h"

    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class RowVector;
    template<typename SCALAR_TYPE, int VEC_LEN, int STRIDE> class ColumnVector;

    // Vectors of DYNAMIC_LENGTH may have lengths that
    // are unknowns at compile time. While the internal behaviour 
    // is different than for static vector lengths, the interoperation
    // of static and dynamic vectors should still take place correctly,
    // as long as vector lengths are the same. For performance reasons
    // it is best to use static vectors since then it is possible for the
    // compiler to perform additional code optimizations.
    const int DYNAMIC_LENGTH = -1;

    template<
        typename DERIVED_MASK_TYPE,
        int STRIDE>
    class MaskInterface :
        public LogicalExpression<DERIVED_MASK_TYPE> {
    protected:
        ~MaskInterface() {}

    public: 
        typedef UME::SIMD::SIMDVecMask<STRIDE> SIMD_TYPE;

        inline LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> land(bool srcB) {
            return LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        inline LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator& (bool srcB) {
            return LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        inline LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> land(E2 & srcB) {
            return LogicalANDExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator& (E2 & srcB) {
            return land(srcB);
        }

        template<typename E2>
        inline LogicalANDExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator&& (E2 & srcB) {
            return land(srcB);
        }


        inline LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool> lor(bool srcB) {
            return LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }
        inline LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool> operator| (bool srcB) {
            return LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, bool>((*this), srcB);
        }

        template<typename E2>
        inline LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> lor(E2 & srcB) {
            return LogicalORExpression <STRIDE, DERIVED_MASK_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator| (E2 & srcB) {
            return lor(srcB);
        }

        template<typename E2>
        inline LogicalORExpression<STRIDE, DERIVED_MASK_TYPE, E2> operator|| (E2 & srcB) {
            return lor(srcB);
        }
    };


    template<int STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class MaskVector : public MaskInterface<
        MaskVector<STRIDE, VEC_LEN>,
        STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVecMask<STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        inline int LENGTH() const { return VEC_LEN; }
        inline int LOOP_COUNT() const { return VEC_LEN / STRIDE; }
        inline int PEEL_COUNT() const { return VEC_LEN % STRIDE; }
        inline int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * STRIDE; }
        inline int SIMD_STRIDE() const { return STRIDE; }

        alignas(SIMD_TYPE::alignment()) bool elements[VEC_LEN];

        MaskVector() { }
        MaskVector(bool x) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = x;
        }
        MaskVector(bool *p) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = p[i];
        }

        template<typename E>
        MaskVector<STRIDE, VEC_LEN>(LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        inline SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.loada(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Every expression evaluation starts with loading values from memory
        // storage into proper scalar equivalent.
        inline SIMD1_TYPE evaluate_scalar(int index) const {
            SIMD1_TYPE t0;
            t0.load(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        inline void update_SIMD(SIMD_TYPE & x, int index) {
            x.storea(&elements[index]);
        }

        inline void update_scalar(SIMD1_TYPE & x, int index) {
            x.store(&elements[index]);
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        inline operator MaskVector<STRIDE, DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            MaskVector<STRIDE, DYNAMIC_LENGTH> temp(VEC_LEN);
            for (int i = 0; i < VEC_LEN;i++) temp.elements[i] = elements[i];
            return temp;
        }

        MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        MaskVector& operator= (MaskVector<STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //RowVector(ArithmeticExpression<E> & vec) {
        MaskVector& operator= (LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        MaskVector& operator= (bool x) {
            SIMD_TYPE t0(x);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                elements[i] = x;
            }
            return *this;
        }

        MaskVector& operator= (bool* x) {
            for (int i = 0; i < VEC_LEN; i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int SIMD_STRIDE>
    class ArithmeticVectorInterface :
        public ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> {
    protected:
        ~ArithmeticVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>          MASK_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>               MASK1_TYPE;

        template<typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }
        
        template<typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> add(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        inline ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> > add(SCALAR_TYPE srcB) {
            return ArithmeticADDExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        // MADD
        template<typename E1, typename E2>
        inline ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> & mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMADDExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        template<typename E1, typename E2>
        inline ArithmeticMADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2> add(LogicalExpression<E1> && mask, ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMADDExpression < SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E1, E2>((*this), mask, srcB);
        }

        // MUL

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        // Explicitly specialize to support RH scalar operand
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>> mul(SCALAR_TYPE srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>>((*this), ScalarExpression<SCALAR_TYPE, SIMD_STRIDE>(srcB));
        }

        /*
        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }
        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> operator* (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> & srcB) {
            return mul(srcB);
        }

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> mul(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2> operator* (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E2> && srcB) {
            return mul(srcB);
        }

        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE> mul(SCALAR_TYPE srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE>((*this), srcB);
        }
        inline ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE> operator* (SCALAR_TYPE & srcB) {
            return mul(srcB);
        }
        /*
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE, SCALAR_TYPE> fmuladd(SCALAR_TYPE srcB, SCALAR_TYPE srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>((*this), srcB, srcC);
        }

        template<typename E2>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, SCALAR_TYPE> fmuladd(E2 & srcB, SCALAR_TYPE srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, SCALAR_TYPE>((*this), srcB, srcC);
        }

        template<typename E2>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, SCALAR_TYPE> fmuladd(E2 && srcB, SCALAR_TYPE srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, SCALAR_TYPE>((*this), srcB, srcC);
        }

        template<typename E3>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE, E3> fmuladd(SCALAR_TYPE srcB, E3 & srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE, E3>((*this), srcB, srcC);
        }
        template<typename E3>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE, E3> fmuladd(SCALAR_TYPE srcB, E3 && srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE, E3>((*this), srcB, srcC);
        }

        template<typename E2, typename E3>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(E2 & srcB, E3 & srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>((*this), srcB, srcC);
        }

        template<typename E2, typename E3>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(E2 && srcB, E3 && srcC) {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE, E2, E3>((*this), srcB, srcC);
        }
        */
        inline ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE> postinc() {
            return ArithmeticPOSTINCExpression<SCALAR_TYPE, SIMD_STRIDE, DERIVED_VECTOR_TYPE>((*this));
        }
        /*
        inline DERIVED_VECTOR_TYPE & postinc(DERIVED_VECTOR_TYPE & dst) {
            //        UNARY_POSTFIX_VEC_OPERATION(
            //           static_cast<DERIVED_VECTOR_TYPE const &>(*this),
            //          dst, postinc, ++,
            //         srcB.LOOP_COUNT(), srcB.LOOP_PEEL_OFFSET(), STRIDE, srcB.LENGTH(), SIMD_TYPE);
            return dst;
        }*/

        inline SCALAR_TYPE dotProduct(DERIVED_VECTOR_TYPE const & srcB) const {
            SIMD_TYPE A, B, C(SCALAR_TYPE(0));

            for (int i = 0; i < srcB.LOOP_COUNT(); i++) {
                A.loada(&(static_cast<DERIVED_VECTOR_TYPE const &>(*this)).elements[i*SIMD_STRIDE]);
                B.loada(&srcB.elements[i*SIMD_STRIDE]);
                C = A.fmuladd(B, C);
            }
            SCALAR_TYPE result = C.hadd();

            for (int i = srcB.LOOP_PEEL_OFFSET(); i < srcB.LENGTH(); i++) {
                result += (static_cast<DERIVED_VECTOR_TYPE const &>(*this)).elements[i] * srcB.elements[i];
            }

            return result;
        }
    };

    /* Static vector template. This template*/
    template<typename SCALAR_TYPE, int SIMD_STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class RowVector : public ArithmeticVectorInterface<
        RowVector<SCALAR_TYPE, SIMD_STRIDE, VEC_LEN>,
        SCALAR_TYPE,
        SIMD_STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD1_TYPE;

        inline int LENGTH() const { return VEC_LEN; }
        inline int LOOP_COUNT() const { return VEC_LEN / SIMD_STRIDE; }
        inline int PEEL_COUNT() const { return VEC_LEN % SIMD_STRIDE; }
        inline int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }
        //inline int SIMD_STRIDE() const { return SIMD_STRIDE; }

        alignas(SIMD_TYPE::alignment()) SCALAR_TYPE elements[VEC_LEN];

        RowVector() { }
        RowVector(SCALAR_TYPE x) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = x;
        }
        RowVector(SCALAR_TYPE *p) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = p[i];
        }

        template<typename E>
        RowVector (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        inline SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.loada(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Every expression evaluation starts with loading values from memory
        // storage into proper scalar equivalent.
        inline SIMD1_TYPE evaluate_scalar(int index) const {
            SIMD1_TYPE t0;
            t0.load(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        inline void update_SIMD(SIMD_TYPE & x, int index) {
            x.storea(&elements[index]);
        }

        inline void update_scalar(SIMD1_TYPE & x, int index) {
            x.store(&elements[index]);
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        inline operator RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> temp(VEC_LEN);
            memcpy(temp.elements, elements, VEC_LEN*sizeof(SCALAR_TYPE));
            return temp;
        }

        RowVector& operator= (RowVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        RowVector& operator= (RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation. This is necessary for using
        // RVALUE expressions on the right hand of assignment operator.
        template<typename E>
        RowVector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            // Dispose of the expression and release all temporary storage.
            reinterpret_vec.dispose();
            return *this;
        }

        // Initialize with expression template evaluation. This is necessary for using
        // 'auto' variable on the right hand of assignment operator.
        template<typename E>
        RowVector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            // Dispose of the expression and release all temporary storage.
            reinterpret_vec.dispose();
            return *this;
        }

        // Broadcast scalar value to all elements of the vector.
        RowVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                elements[i] = x;
            }
            return *this;
        }

        // Copy values from memory location
        RowVector& operator= (SCALAR_TYPE* x) {
            for (int i = 0; i < VEC_LEN; i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

    // Dynamic vector template. The main difference with static vectors is, that
    // the the length may not be known at compile time. For that reason stack allocation
    // is not possible and the data needs to be stored on heap. This class can still use
    // ArithmeticVectorInterface, but it require some additional user-invisible functionality
    // to support type conversions between static and dynamic vectors.
    template<typename SCALAR_TYPE, int SIMD_STRIDE>
    class RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> : public ArithmeticVectorInterface<
        RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH>,
        SCALAR_TYPE,
        SIMD_STRIDE>
    {
    private:
        int mLength;

        //template<int L> 
        //friend class RowVector<SCALAR_TYPE, STRIDE, L>;

    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;

        inline int LENGTH() const { return mLength; }
        inline int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        inline int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        inline int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }
        //inline int SIMD_STRIDE() const { return STRIDE; }

        SCALAR_TYPE* elements;

        RowVector(int length) :
            mLength(length)
        {
            elements = (SCALAR_TYPE*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(SCALAR_TYPE),
                SIMD_TYPE::alignment());
        }

        RowVector(int length, SCALAR_TYPE value) :
            mLength(length)
        {
            elements = (SCALAR_TYPE*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(SCALAR_TYPE),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = value;
        }

        RowVector(int length, SCALAR_TYPE *values) :
            mLength(length)
        {
            elements = (SCALAR_TYPE*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(SCALAR_TYPE),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = values[i];
        }

        RowVector(RowVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            origin.elements = NULL;
        }

        ~RowVector() {
            UME::DynamicMemory::AlignedFree(elements);
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        inline SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.loada(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Every expression evaluation starts with loading values from memory
        // storage into proper scalar equivalent.
        inline SIMD1_TYPE evaluate_scalar(int index) const {
            SIMD1_TYPE t0;
            t0.load(&elements[index]);
            return t0;
        }

        RowVector& operator= (RowVector & origin) {
            if (mLength != origin.mLength) {
                // Dimensions do not match - reallocate
                UME::DynamicMemory::AlignedFree(elements);
                elements = (SCALAR_TYPE*)UME::DynamicMemory::AlignedMalloc(origin.mLength*sizeof(SCALAR_TYPE), SIMD_TYPE::alignment());
                mLength = origin.mLength;
            }

            for (int i = 0; i < mLength; i++) elements[i] = origin.elements[i];

            return *this;
        }

        RowVector& operator= (RowVector&& origin) {
            UME::DynamicMemory::AlignedFree(elements);
            elements = origin.elements;
            origin.elements = NULL;
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //RowVector(ArithmeticExpression<E> & vec) {
        RowVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        RowVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < mLength(); i++) {
                elements[i] = x;
            }
            return *this;
        }

        RowVector& operator= (SCALAR_TYPE* x) {
            for (int i = 0; i < mLength(); i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };
}
}

#endif
