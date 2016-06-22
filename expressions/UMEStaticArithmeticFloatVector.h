#ifndef UME_STATIC_ARITHMETIC_FLOAT_VECTOR_H_
#define UME_STATIC_ARITHMETIC_FLOAT_VECTOR_H_

namespace UME {
namespace VECTOR {

    /* Static vector template. This template*/
    template<typename SCALAR_TYPE, int SIMD_STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class FloatVector : public ArithmeticFloatVectorInterface<
        FloatVector<SCALAR_TYPE, SIMD_STRIDE, VEC_LEN>,
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

        SCALAR_TYPE *elements;
    private:
        // Vector class should be intialized with proper user-managed memory buffer.
        UME_FORCE_INLINE FloatVector() {}

    public:
        // p should be properly aligned!
        UME_FORCE_INLINE FloatVector(SCALAR_TYPE *p) : elements(p) {
        }
        UME_FORCE_INLINE FloatVector(FloatVector && origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
        }

        template<typename E>
        UME_FORCE_INLINE FloatVector(ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
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
        UME_FORCE_INLINE operator FloatVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH>() {
            // TODO:
            // Create dynamic Row vector, and copy data
            FloatVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> temp(LENGTH());
            //memcpy(temp.elements, elements, LENGTH()*sizeof(SCALAR_TYPE));
            return temp;
        }

        // TODO: assignment should generate an ASSIGN expression to do lazy evaluation
        UME_FORCE_INLINE FloatVector& operator= (FloatVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        UME_FORCE_INLINE FloatVector& operator= (FloatVector&& origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // TODO: assignment should generate an ASSIGN expression to do lazy evaluation
        UME_FORCE_INLINE FloatVector& operator= (FloatVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation. This is necessary for using
        // RVALUE expressions on the right hand of assignment operator.
        template<typename E>
        UME_FORCE_INLINE FloatVector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
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
        UME_FORCE_INLINE FloatVector& operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            return *this;
        }

        // Broadcast scalar value to all elements of the vector.
        // TODO: also should be done using lazy evaluation
        UME_FORCE_INLINE FloatVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                elements[i] = x;
            }
            return *this;
        }

        // Copy values from memory location
        // TODO: can this be done using lazy evaluation?
        UME_FORCE_INLINE FloatVector& operator= (SCALAR_TYPE* x) {
            for (int i = 0; i < LENGTH(); i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

}
}

#endif
