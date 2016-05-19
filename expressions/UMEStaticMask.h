#ifndef UME_STATIC_MASK_H_
#define UME_STATIC_MASK_H_

namespace UME {
namespace VECTOR {

    template<int STRIDE = 4, int VEC_LEN = DYNAMIC_LENGTH>
    class MaskVector : public MaskInterface<
        MaskVector<STRIDE, VEC_LEN>,
        STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVecMask<STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return VEC_LEN; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return VEC_LEN / STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return VEC_LEN % STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * STRIDE; }
        UME_FORCE_INLINE int SIMD_STRIDE() const { return STRIDE; }

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
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += STRIDE) {
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
        UME_FORCE_INLINE operator MaskVector<STRIDE, DYNAMIC_LENGTH>() {
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
        //Vector(ArithmeticExpression<E> & vec) {
        MaskVector& operator= (LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += STRIDE) {
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
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += STRIDE) {
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

}
}
#endif
