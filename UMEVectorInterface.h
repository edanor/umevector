#ifndef UME_VECTOR_INTERFACE_H_
#define UME_VECTOR_INTERFACE_H_

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <stdlib.h>

#include <cassert>

namespace UME {
namespace BLAS {

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
    class ArithmeticVectorInterface {
    private:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1>      SIMD1_TYPE;

    protected:
        ~ArithmeticVectorInterface() {}

    public:
        inline DERIVED_VECTOR_TYPE & add(DERIVED_VECTOR_TYPE const & srcB, DERIVED_VECTOR_TYPE & dst) const {
            DERIVED_VECTOR_TYPE const & srcA = static_cast<DERIVED_VECTOR_TYPE const &>(*this);
            BINARY_VEC_VEC_OPERATION(srcA, srcB, dst, add, SIMD_TYPE, SIMD1_TYPE );
            return dst;
        }

        inline DERIVED_VECTOR_TYPE & add(SCALAR_TYPE srcB, DERIVED_VECTOR_TYPE & dst) const {
            DERIVED_VECTOR_TYPE const & srcA = static_cast<DERIVED_VECTOR_TYPE const &>(*this);
            BINARY_VEC_SCALAR_OPERATION(srcA, srcB, dst, add, SIMD_TYPE, SIMD1_TYPE);
            return dst;
        }

        inline DERIVED_VECTOR_TYPE & adda(DERIVED_VECTOR_TYPE const & srcB) {
            assert(mLength == srcB.mLength);
            DERIVED_VECTOR_TYPE const & srcA = static_cast<DERIVED_VECTOR_TYPE &>(*this);
            BINARY_VEC_VEC_OPERATION_ASSIGN(srcA, srcB, adda, SIMD_TYPE, SIMD1_TYPE);
            return *this;
        }

        inline DERIVED_VECTOR_TYPE & adda(SCALAR_TYPE srcB) {
            DERIVED_VECTOR_TYPE const & srcA = static_cast<DERIVED_VECTOR_TYPE &>(*this);
            BINARY_VEC_SCALAR_OPERATION_ASSIGN(srcA, srcB, adda, SIMD_TYPE, SIMD1_TYPE);
            return *this;
        }

        inline DERIVED_VECTOR_TYPE & postinc(DERIVED_VECTOR_TYPE & dst) {
            //        UNARY_POSTFIX_VEC_OPERATION(
            //           static_cast<DERIVED_VECTOR_TYPE const &>(*this),
            //          dst, postinc, ++,
            //         srcB.LOOP_COUNT(), srcB.LOOP_PEEL_OFFSET(), STRIDE, srcB.LENGTH(), SIMD_TYPE);
            return dst;
        }

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
    };

    /* Dynamic vector template. The main difference with static vectors is, that
       the the length may not be known at compile time. For that reason stack allocation
       is not possible. Hence, the data needs to be stored on heap. This class can still use
       ArithmeticVectorInterface, but it require some additional functionality to support
       type conversions between static and dynamic vectors.*/
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
    };
}
}

#endif
