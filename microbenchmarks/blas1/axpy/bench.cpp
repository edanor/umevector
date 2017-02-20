// The MIT License (MIT)
//
// Copyright (c) 2016-2017 CERN
//
// Author: Przemyslaw Karpinski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//
//  This piece of code was developed as part of ICE-DIP project at CERN.
//  "ICE-DIP is a European Industrial Doctorate project funded by the European Community's
//  7th Framework programme Marie Curie Actions under grant PITN-GA-2012-316596".
//

#include <iostream>
#include <memory>

#if defined(__i386__) || defined(__x86_64__)
#include <immintrin.h> 
#endif

#include <cmath>
#include <time.h>
#include <stdlib.h>
#include <string>

//#define UME_SIMD_SHOW_EMULATION_WARNINGS 1
#include <umesimd/UMESimd.h>
#include <umesimd/microbenchmarks/utilities/TimingStatistics.h>

// Introducing inline assembly forces compiler to generate
#define BREAK_COMPILER_OPTIMIZATION() __asm__ ("NOP");

#include "scalar_bench.h"
#include "blas_bench.h"
#include "ume_bench.h"

int main()
{
    
    const int ITERATIONS = 100;
    const int ARRAY_SIZE = 1000000;

    TimingStatistics stats_scalar_single_f, stats_ume_single_f, stats_blas_single_f;
    
    std::cout << "Single execution:\n";

    // SCALAR    
    for (int i = 0; i < ITERATIONS; i++) {
        stats_scalar_single_f.update(test_scalar_single<float>(ARRAY_SIZE));
    }

    std::cout << "Scalar code, (single, float): " << (unsigned long long) stats_scalar_single_f.getAverage()
              << ", dev: " << (unsigned long long) stats_scalar_single_f.getStdDev()
              << " (speedup: 1.0x)\n";
    
    // UME
    for (int i = 0; i < ITERATIONS; i++) {
        stats_ume_single_f.update(test_ume_single<float>(ARRAY_SIZE));
    }

    std::cout << "UME code, (single, float): " << (unsigned long long) stats_ume_single_f.getAverage()
              << ", dev: " << (unsigned long long) stats_ume_single_f.getStdDev()
              << " (speedup: " << stats_scalar_single_f.getAverage() / stats_ume_single_f.getAverage() << ")\n";

    // BLAS
    for (int i = 0; i < ITERATIONS; i++) {
        stats_blas_single_f.update(test_blas_single<float>(ARRAY_SIZE));
    }
    
    std::cout << "BLAS code, (single, float): " << (unsigned long long) stats_blas_single_f.getAverage()
              << ", dev: " << (unsigned long long) stats_blas_single_f.getStdDev()
              << " (speedup: " << stats_scalar_single_f.getAverage() / stats_blas_single_f.getAverage() << ")\n";
    
    // Single execution, double precision
    TimingStatistics stats_scalar_single_d, stats_ume_single_d, stats_scalar_chained_d, stats_ume_chained_d;


    // Chained execution
    std::cout << "Chained execution:\n";
    TimingStatistics stats_scalar_chained_f, stats_ume_chained_f, stats_blas_chained_f;    
    
    // SCALAR
    for (int i = 0; i < ITERATIONS; i++) {
        stats_scalar_chained_f.update(test_scalar_chained<float>(ARRAY_SIZE));
    }

    std::cout << "Scalar code, (chained, float): " << (unsigned long long) stats_scalar_chained_f.getAverage()
              << ", dev: " << (unsigned long long) stats_scalar_chained_f.getStdDev()
              << " (speedup: 1.0x)\n";

    // UME
    for (int i = 0; i < ITERATIONS; i++) {
        stats_ume_chained_f.update(test_ume_chained<float>(ARRAY_SIZE));
    }

    std::cout << "UME code, (chained, float): " << (unsigned long long) stats_ume_chained_f.getAverage()
              << ", dev: " << (unsigned long long) stats_ume_chained_f.getStdDev()
              << " (speedup: " << stats_scalar_chained_f.getAverage() / stats_ume_chained_f.getAverage() << ")\n";
              
    // BLAS
    for (int i = 0; i < ITERATIONS; i++) {
        stats_blas_chained_f.update(test_blas_chained<float>(ARRAY_SIZE));
    }

    std::cout << "BLAS code, (chained, float): " << (unsigned long long) stats_blas_chained_f.getAverage()
              << ", dev: " << (unsigned long long) stats_blas_chained_f.getStdDev()
              << " (speedup: " << stats_scalar_chained_f.getAverage() / stats_blas_chained_f.getAverage() << ")\n";

}
