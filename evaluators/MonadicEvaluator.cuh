#pragma once

#include <cuda_runtime.h>

#include "../UMEVector.h"

// CUDA programming language does not allow static member functions to be used for evaluation.
// For this reason all evaluators here take a form of C-like functions, callable from host code.

namespace UME
{
    namespace VECTOR {
        // CUDA does not allow pass-by-reference for __global__ functions. This means, that
        // any expression has to be fully copied to the device memory at kernel startup.
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename DST_T,
            typename EXP_T>
            __global__ void MonadicEvaluator(DST_T dst, EXP_T exp) {
            int i = blockIdx.x*blockDim.x + threadIdx.x;
            if (i < dst.LENGTH()) {
                EXP_T & reinterpret_exp = static_cast<EXP_T &>(exp);
                auto t0 = reinterpret_exp.template evaluate<1>(i);
                dst.update<1>(t0, i);
            }
        }

        // Evaluate expression with scalar destination (e.g. reduction operation)
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename EXP_T>
            __global__ void MonadicEvaluator(SCALAR_T * dst, ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> exp)
        {
            // TODO
        }

        // Evaluate expression with no destination, but side effects (e.g. destructive ADD operation).
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename EXP_T>
            __global__ void MonadicEvaluator(ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> exp)
        {
            // TODO
        }

        // Evaluate with a computed scatter indices
        template<
            typename SCALAR_T,
            int SIMD_STRIDE,
            typename DST_T,
            typename EXP_T,
            typename EXP_INDICES_T>
            __global__ void MonadicEvaluator(
                DST_T dst,
                ArithmeticExpression<SCALAR_T, SIMD_STRIDE, EXP_T> exp,
                ArithmeticExpression<uint32_t, SIMD_STRIDE, EXP_INDICES_T> exp_indices)
        {
            // TODO
        }
    }
}