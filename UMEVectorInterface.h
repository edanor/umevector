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

#define UNARY_PREFIX_VEC_OPERATION(vecA, vecDst, SIMD_OP, SCALAR_OP) \
        VEC_TYPE A, B, C; \
\
    for (int i = 0; i < LOOP_COUNT; i++) { \
        A.loada(&vecA.elements[i*STRIDE]); \
        B.loada(&vecB.elements[i*STRIDE]); \
        C = A.SIMD_OP(); \
        C.storea(&vecDst.elements[i*STRIDE]); \
    } \
\
for (int i = LOOP_PEEL_OFFSET; i < VEC_LEN; i++) { \
    vecDst.elements[i] = SCALAR_OP elements[i]; \
}

#define UNARY_POSTFIX_VEC_OPERATION(vecDst, SIMD_OP, SCALAR_OP) \
        VEC_TYPE A, B; \
\
    for (int i = 0; i < LOOP_COUNT; i++) { \
        A.loada(&elements[i*STRIDE]); \
        B = A.SIMD_OP(); \
        B.storea(&vecDst.elements[i*STRIDE]); \
    } \
\
for (int i = LOOP_PEEL_OFFSET; i < VEC_LEN; i++) { \
    vecDst.elements[i] = elements[i] SCALAR_OP; \
}

    // Performs binary operation of the form:
    //
    //  vecDst = vecA.SIMD_OP(vecB);
    //
    // For loop peeled elements, SIMD1 is used.

#define BINARY_VEC_VEC_OPERATION(vecA, vecB, vecDst, SIMD_OP, SIMD_TYPE, SIMD1_TYPE) \
        assert((vecA).LENGTH() == (vecB).LENGTH()); \
        assert((vecA).LENGTH() == (vecDst).LENGTH()); \
        SIMD_TYPE A, B, C; \
\
    for (int i = 0; i < (vecA).LOOP_COUNT(); i++) { \
        A.loada(&(vecA).elements[i*(vecA).SIMD_STRIDE()]); \
        B.loada(&(vecB).elements[i*(vecA).SIMD_STRIDE()]); \
        C = A.SIMD_OP(B); \
        C.storea(&(vecDst).elements[i*(vecA).SIMD_STRIDE()]); \
    } \
\
    SIMD1_TYPE A1, B1, C1; \
    for (int i = (vecA).LOOP_PEEL_OFFSET(); i < (vecA).LENGTH(); i++) { \
        A1.load(&(vecA).elements[i]); \
        B1.load(&(vecB).elements[i]); \
        C1 = A1.SIMD_OP(B1); \
        C1.store(&(vecDst).elements[i]); \
    }

#define BINARY_VEC_SCALAR_OPERATION(vecA, scalarB, vecDst, SIMD_OP, SIMD_TYPE, SIMD1_TYPE) \
        assert(vecA.LENGTH() == (vecDst).LENGTH()); \
        SIMD_TYPE A, B(scalarB), C; \
\
    for (int i = 0; i < (vecA).LOOP_COUNT(); i++) { \
        A.loada(&(vecA).elements[i*(vecA).SIMD_STRIDE()]); \
        C = A.SIMD_OP(B); \
        C.storea(&(vecDst).elements[i*(vecA).SIMD_STRIDE()]); \
    } \
\
    SIMD1_TYPE A1, B1(scalarB), C1; \
    for (int i = (vecA).LOOP_PEEL_OFFSET(); i < (vecA).LENGTH(); i++) { \
        A1.load(&(vecA).elements[i]); \
        C1 = A1.SIMD_OP(B1); \
        C1.store(&(vecDst).elements[i]); \
    }

#define BINARY_VEC_VEC_OPERATION_ASSIGN(vecA, vecB, SIMD_OP, SIMD_TYPE, SIMD1_TYPE) \
        assert((vecA).LENGTH() == (vecB).LENGTH()); \
        SIMD_TYPE A, B; \
\
    for (int i = 0; i < LOOP_COUNT; i++) { \
        A.loada(&(vecA).elements[i*STRIDE]); \
        B.loada(&(vecB).elements[i*STRIDE]); \
        A.SIMD_OP(B); \
        A.storea(&(vecA).elements[i*STRIDE]); \
    } \
\
    SIMD1_TYPE A2, B2; \
    for (int i = LOOP_PEEL_OFFSET; i < VEC_LEN; i++) { \
        A2.load(&(vecA).elements[i*STRIDE]); \
        B2.load(&(vecB).elements[i*STRIDE]); \
        A2.SIMD_OP(B2); \
        A2.store(&(vecA).elements[i*STRIDE]); \
    }

#define BINARY_VEC_SCALAR_OPERATION_ASSIGN(vecA, scalarB, SIMD_OP, SIMD_TYPE, SIMD1_TYPE) \
        SIMD_TYPE A, B(scalarB); \
\
    for (int i = 0; i < LOOP_COUNT; i++) { \
        A.loada(&(vecA).elements[i*STRIDE]); \
        A.SIMD_OP(B); \
        A.storea(&(vecA).elements[i*STRIDE]); \
    } \
\
    SIMD1_TYPE A2, B2(scalarB); \
    for (int i = LOOP_PEEL_OFFSET; i < VEC_LEN; i++) { \
        A2.load(&(vecA).elements[i*STRIDE]); \
        A2.SIMD_OP(B2); \
        A2.store(&(vecA).elements[i*STRIDE]); \
    }

    template<
        typename DERIVED_VECTOR_TYPE,
        typename SCALAR_TYPE,
        int STRIDE>
    class ArithmeticVectorInterface :
        public ArithmeticExpression<DERIVED_VECTOR_TYPE> {
    private:

    protected:
        ~ArithmeticVectorInterface() {}

    public:
        // Can we make this private?
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;

        inline ArithmeticADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE> add(SCALAR_TYPE srcB) {
            return ArithmeticADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2> add(E2 & srcB) {
            return ArithmeticADDExpression < SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2> add(E2 && srcB) {
            return ArithmeticADDExpression < SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        inline ArithmeticMULExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE> mul(SCALAR_TYPE srcB) {
            return ArithmeticMULExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, SCALAR_TYPE>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2> mul(E2 & srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2>
        inline ArithmeticMULExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2> mul(E2 && srcB) {
            return ArithmeticMULExpression <SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2>((*this), srcB);
        }

        template<typename E2, typename E3>
        inline ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2, E3> fmuladd(E2 const & srcB, E3 const & srcC) const {
            return ArithmeticFMULADDExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE, E2, E3>((*this), srcB, srcC);
        }

        inline ArithmeticPOSTINCExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE> postinc() {
            return ArithmeticPOSTINCExpression<SCALAR_TYPE, STRIDE, DERIVED_VECTOR_TYPE>((*this));
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
                A.loada(&(static_cast<DERIVED_VECTOR_TYPE const &>(*this)).elements[i*STRIDE]);
                B.loada(&srcB.elements[i*STRIDE]);
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
    template<typename SCALAR_TYPE, int STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class RowVector : public ArithmeticVectorInterface<
        RowVector<SCALAR_TYPE, STRIDE, VEC_LEN>,
        SCALAR_TYPE,
        STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD1_TYPE;

        inline int LENGTH() const { return VEC_LEN; }
        inline int LOOP_COUNT() const { return VEC_LEN / STRIDE; }
        inline int PEEL_COUNT() const { return VEC_LEN % STRIDE; }
        inline int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * STRIDE; }
        inline int SIMD_STRIDE() const { return STRIDE; }

        alignas(SIMD_TYPE::alignment()) SCALAR_TYPE elements[VEC_LEN];

        RowVector() { }
        RowVector(SCALAR_TYPE x) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = x;
        }
        RowVector(SCALAR_TYPE *p) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = p[i];
        }

        template<typename E>
        RowVector<SCALAR_TYPE, STRIDE, VEC_LEN>(ArithmeticExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
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
        inline operator RowVector<SCALAR_TYPE, STRIDE, DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            RowVector<SCALAR_TYPE, STRIDE, DYNAMIC_LENGTH> temp(VEC_LEN);
            memcpy(temp.elements, elements, VEC_LEN*sizeof(SCALAR_TYPE));
            return temp;
        }

        RowVector& operator= (RowVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        RowVector& operator= (RowVector<SCALAR_TYPE, STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //RowVector(ArithmeticExpression<E> & vec) {
        RowVector& operator= (ArithmeticExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }
    };

    // Dynamic vector template. The main difference with static vectors is, that
    // the the length may not be known at compile time. For that reason stack allocation
    // is not possible and the data needs to be stored on heap. This class can still use
    // ArithmeticVectorInterface, but it require some additional user-invisible functionality
    // to support type conversions between static and dynamic vectors.
    template<typename SCALAR_TYPE, int STRIDE>
    class RowVector<SCALAR_TYPE, STRIDE, DYNAMIC_LENGTH> : public ArithmeticVectorInterface<
        RowVector<SCALAR_TYPE, STRIDE, DYNAMIC_LENGTH>,
        SCALAR_TYPE,
        STRIDE>
    {
    private:
        int mLength;

        //template<int L> 
        //friend class RowVector<SCALAR_TYPE, STRIDE, L>;

    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;

        inline int LENGTH() const { return mLength; }
        inline int LOOP_COUNT() const { return mLength / STRIDE; }
        inline int PEEL_COUNT() const { return mLength % STRIDE; }
        inline int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*STRIDE; }
        inline int SIMD_STRIDE() const { return STRIDE; }

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
        RowVector& operator= (ArithmeticExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < mLength; i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }
    };
}
}

#endif
