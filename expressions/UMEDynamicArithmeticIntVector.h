#ifndef UME_DYNAMIC_ARITHMETIC_INT_VECTOR_H_
#define UME_DYNAMIC_ARITHMETIC_INT_VECTOR_H_

namespace UME {
namespace VECTOR {

    // Dynamic vector template. The main difference with static vectors is, that
    // the the length may not be known at compile time. For that reason stack allocation
    // is not possible and the data needs to be stored on heap. This class can still use
    // ArithmeticVectorInterface, but it require some additional user-invisible functionality
    // to support type conversions between static and dynamic vectors.
    template<typename SCALAR_TYPE, int SIMD_STRIDE>
    class IntVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> : public ArithmeticIntVectorInterface<
        IntVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH>,
        SCALAR_TYPE,
        SIMD_STRIDE>
    {
    private:
        int mLength;

    public:
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> SIMD_TYPE;
        typedef UME::SIMD::SIMDVec<SCALAR_TYPE, 1> SIMD1_TYPE;

        UME_FORCE_INLINE int LENGTH() const { return mLength; }
        UME_FORCE_INLINE int LOOP_COUNT() const { return mLength / SIMD_STRIDE; }
        UME_FORCE_INLINE int PEEL_COUNT() const { return mLength % SIMD_STRIDE; }
        UME_FORCE_INLINE int LOOP_PEEL_OFFSET() const { return LOOP_COUNT()*SIMD_STRIDE; }
        //UME_FORCE_INLINE int SIMD_STRIDE() const { return STRIDE; }

        SCALAR_TYPE* elements;
    private:
        // Vector class should be intialized with proper user-managed memory buffer.
        UME_FORCE_INLINE IntVector() {}

    public:
        // p should be properly aligned!
        UME_FORCE_INLINE IntVector(int length, SCALAR_TYPE *values) :
            mLength(length), elements(values) {
        }

        UME_FORCE_INLINE IntVector(IntVector && origin) {
            elements = origin.elements;
            mLength = origin.mLength;
            origin.elements = NULL;
        }

        UME_FORCE_INLINE ~IntVector() {
        }

        // Terminal call for SIMD version of expression template expressions. 
        // Every expression evaluation starts with loading values from memory 
        // storage into proper SIMD vectors.
        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index) const {
            SIMD_TYPE t0;
            t0.load(&elements[index]);
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

        UME_FORCE_INLINE IntVector& operator= (IntVector&& origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            return *this;
        }

        // TODO: assignment should generate an ASSIGN expression to do lazy evaluation
        UME_FORCE_INLINE IntVector& operator= (IntVector & origin) {
            for (int i = 0; i < LENGTH(); i++) elements[i] = origin.elements[i];
            return *this;
        }

        // Initialize with expression template evaluation
        template<typename E>
        UME_FORCE_INLINE IntVector<SCALAR_TYPE, SIMD_STRIDE, DYNAMIC_LENGTH> & operator= (ArithmeticExpression<SCALAR_TYPE, SIMD_STRIDE, E> && vec)
        {
            // Need to reinterpret vec to E to propagate to proper expression
            // evaluator.
            E & reinterpret_vec = static_cast<E &>(vec);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0 = reinterpret_vec.evaluate_SIMD(i);
                t0.store(&elements[i]);
            }

            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                UME::SIMD::SIMDVec<SCALAR_TYPE, 1> t1 = reinterpret_vec.evaluate_scalar(i);
                t1.store(&elements[i]);
            }
            return *this;
        }

        UME_FORCE_INLINE IntVector& operator= (SCALAR_TYPE x) {
            UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> t0(x);
            for (int i = 0; i < LOOP_PEEL_OFFSET(); i += SIMD_STRIDE) {
                t0.store(&elements[i]);
            }
            for (int i = LOOP_PEEL_OFFSET(); i < LENGTH(); i++) {
                elements[i] = x;
            }
            return *this;
        }

        UME_FORCE_INLINE IntVector& operator= (ScalarExpression<SCALAR_TYPE, SIMD_STRIDE> & x) {
            for (int i = 0; i < LENGTH(); i++) {
                elements[i] = x[i];
            }
            return *this;
        }
    };

}
}
#endif
