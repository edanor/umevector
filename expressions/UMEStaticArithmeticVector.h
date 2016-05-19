#ifndef UME_STATIC_ARITHMETIC_VECTOR_H_
#define UME_STATIC_ARITHMETIC_VECTOR_H_

namespace UME {
namespace VECTOR {

    /* Static vector template. This template*/
    template<typename SCALAR_TYPE, int SIMD_STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class Vector : public ArithmeticVectorInterface<
        Vector<SCALAR_TYPE, SIMD_STRIDE, VEC_LEN>,
        SCALAR_TYPE,
        SIMD_STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return VEC_LEN; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return VEC_LEN / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return VEC_LEN % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }
        //UME_FORCE_INLINE int SIMD_STRIDE() const { return SIMD_STRIDE; }

        alignas(SIMD_TYPE::alignment()) SCALAR_TYPE elements[VEC_LEN];

        Vector() { }
        Vector(SCALAR_TYPE x) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = x;
        }
        Vector(SCALAR_TYPE *p) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = p[i];
        }

        template<typename E>
        Vector(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
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
        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.loada(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Every expression evaluation starts with loading values from memory
        // storage into proper scalar equivalent.
        UME_FORCE_INLINE SIMD1_TYPE evaluate_scalar(int index) const {
            SIMD1_TYPE t0;
            t0.load(&elements[index]);
            return t0;
        }

        // Terminal call for scalar version of expression template expressions.
        // Some operations require implicit assignment. This assignment needs to
        // be propagated from evaluated register, back to vector data localization.
        UME_FORCE_INLINE void update_SIMD(SIMD_TYPE & x, int index) {
            x.storea(&elements[index]);
        }

        UME_FORCE_INLINE void update_scalar(SIMD1_TYPE & x, int index) {
            x.store(&elements[index]);
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        UME_FORCE_INLINE operator Vector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            Vector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> temp(VEC_LEN);
            memcpy(temp.elements, elements, VEC_LEN*sizeof(SCALAR_TYPE));
            return temp;
        }

        Vector& operator= (Vector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        Vector& operator= (Vector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation. This is necessary for using
        // RVALUE expressions on the right hand of assignment operator.
        template<typename E>
        Vector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
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
        Vector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
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
        Vector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                elements[i] = x;
            }
            return *this;
        }

        // Copy values from memory location
        Vector& operator= (SCALAR_TYPE* x) {
            for (int i = 0; i < VEC_LEN; i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

}
}

#endif
