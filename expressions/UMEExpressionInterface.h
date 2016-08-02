#ifndef UME_EXPRESSION_INTERFACE_H_

namespace UME {
namespace VECTOR {

    template<typename E>
    class LogicalExpression {
    public:
        operator E&() { return static_cast<E&>(*this); }
        operator E const&() const { return static_cast<const E&>(*this); }

        void dispose() {}
    };

    template <typename SCALAR_TYPE, int SIMD_STRIDE, typename E>
    class ArithmeticExpression {
    public:
        int LOOP_COUNT() { return static_cast<E&>(*this).LOOP_COUNT(); }

        static constexpr int GET_SIMD_STRIDE() { return SIMD_STRIDE; }

        operator E&() { return static_cast<E&>(*this); }
        operator E const&() const { return static_cast<const E&>(*this); }

        UME_FORCE_INLINE SIMD_TYPE evaluate_SIMD(int index) {
            auto
        }

        void dispose() {}
    };

}
}
#endif
