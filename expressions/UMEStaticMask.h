#ifndef UME_STATIC_MASK_H_
#define UME_STATIC_MASK_H_

namespace UME {
namespace VECTOR {

    template<int SIMD_STRIDE, int VEC_LEN = DYNAMIC_LENGTH>
    class MaskVector : public MaskInterface<
        MaskVector<SIMD_STRIDE, VEC_LEN>,
        SIMD_STRIDE>
    {
    public:
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return VEC_LEN; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return VEC_LEN / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return VEC_LEN % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }

        bool *elements;

    private:
        MaskVector() { }

    public:
        MaskVector(bool *p) : elements(p) {}

        template<typename E>
        MaskVector(LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
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

        UME_FORCE_INLINE MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector && origin) {
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        UME_FORCE_INLINE MaskVector& operator= (MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH> & origin) {
            assert(VEC_LEN == origin.LENGTH()); // Cannot re-allocate static
            for (int i = 0; i < VEC_LEN; i++) elements[i] = origin.elements[i];
            return *this;
        }

        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        UME_FORCE_INLINE MaskVector& operator= (LogicalExpression<E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        UME_FORCE_INLINE MaskVector& operator= (LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < VEC_LEN; i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

    };

}
}
#endif
