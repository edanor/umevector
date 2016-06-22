#ifndef UME_DYNAMIC_MASK_H_
#define UME_DYNAMIC_MASK_H_

namespace UME {
namespace VECTOR {

    template<int SIMD_STRIDE>
    class MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH> : public MaskInterface<
        MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH>,
        SIMD_STRIDE>
    {
    private:
        int mLength;

    public:
        typedef UME::SIMD::SIMDVecMask<SIMD_STRIDE>  SIMD_TYPE;
        typedef UME::SIMD::SIMDVecMask<1>       SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return mLength; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT() * SIMD_STRIDE; }
        //UME_FORCE_INLINE int SIMD_STRIDE() const { return SIMD_STRIDE; }

        bool* elements;

        MaskVector(int length) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
        }
        MaskVector(int length, bool value) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = value;
        }
        MaskVector(int length, bool *p) : mLength(length)
        {
            elements = (bool*)UME::DynamicMemory::AlignedMalloc(
                length*sizeof(bool),
                SIMD_TYPE::alignment());
            for (int i = 0; i < length; i++) elements[i] = p[i];
        }

        MaskVector(MaskVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            origin.elements = NULL;
        }

        ~MaskVector() {
            UME::DynamicMemory::AlignedFree(elements);
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


        template<typename E>
        UME_FORCE_INLINE MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH>(LogicalExpression<E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            reinterpret_vec.dispose();
        }

        // Cast operator to convert from static to dynamic form. Because of
        // different allocation method, the data needs to be copied from stack-organized
        // to heap-organized. 
        UME_FORCE_INLINE operator MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH>() {
            // Create dynamic Row vector, and copy data
            MaskVector<SIMD_STRIDE, DYNAMIC_LENGTH> temp(LENGTH());
            for (int i = 0; i < LENGTH();i++) temp.elements[i] = elements[i];
            return temp;
        }

        MaskVector& operator= (MaskVector & origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
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
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }

            reinterpret_vec.dispose();
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        //Vector(ArithmeticExpression<E> & vec) {
        MaskVector& operator= (LogicalExpression<E> & vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                SIMD_TYPE t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.storea(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                SIMD1_TYPE t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        MaskVector& operator= (bool x) {
            SIMD_TYPE t0(x);
            for (int i = 0; i < LOOP_COUNT(); i += SIMD_STRIDE) {
                t0.storea(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                elements[i] = x;
            }
            return *this;
        }

        MaskVector& operator= (bool* x) {
            for (int i = 0; i < LENGTH(); i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

}
}
#endif
