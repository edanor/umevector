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
#ifndef BLAS_BENCH_H_
#define BLAS_BENCH_H_

#include <assert.h>

#include <umesimd/UMESimd.h>
#include <cblas.h>

template<typename FLOAT_T>
UME_NEVER_INLINE TIMING_RES test_blas_single(int ARRAY_SIZE)
{
  // Only specialized versions of this function allowed.
    assert(false);
}

template<>
UME_NEVER_INLINE TIMING_RES test_blas_single<float>(int ARRAY_SIZE)
{
    typedef float FLOAT_T;
    
    unsigned long long start, end; // Time measurements
    FLOAT_T *x, *y;
    FLOAT_T alpha;

    x = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    y = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));

    srand ((unsigned int)time(NULL));
    // Initialize arrays with random data
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        // Generate random numbers in range (0.0;1.0)
        x[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        y[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
    }
    
    alpha = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        
    // Start evaluation
    start = get_timestamp();

    cblas_saxpy(ARRAY_SIZE, alpha, x, 1, y, 1);

    end = get_timestamp();

    UME::DynamicMemory::AlignedFree(x);
    UME::DynamicMemory::AlignedFree(y);

    return end - start;
}

template<typename FLOAT_T>
UME_NEVER_INLINE TIMING_RES test_blas_chained(int ARRAY_SIZE)
{
  // Only specialized versions of this function allowed.
    assert(false);
}

template<>
UME_NEVER_INLINE TIMING_RES test_blas_chained<float>(int ARRAY_SIZE)
{
    typedef float FLOAT_T;

    unsigned long long start, end; // Time measurements
    FLOAT_T *x0, *x1, *x2, *x3, *x4, *x5, *x6, *x7, *x8, *x9, *y, *alpha;

    x0 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x1 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x2 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x3 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x4 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x5 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x6 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x7 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x8 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    x9 = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    y = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(ARRAY_SIZE*sizeof(FLOAT_T), sizeof(FLOAT_T));
    alpha = (FLOAT_T *) UME::DynamicMemory::AlignedMalloc(10*sizeof(FLOAT_T), sizeof(FLOAT_T));
    
    srand ((unsigned int)time(NULL));    
    
    // Initialize arrays with random data
    for(int i = 0; i < ARRAY_SIZE; i++)
    {
        // Generate random numbers in range (0.0;1.0)
        x0[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x1[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x2[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x3[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x4[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x5[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x6[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x7[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x8[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        x9[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
        y[i] = 0.0f;
    }

    for(int i = 0; i < 10; i++)
    {
        alpha[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);    
    }
    // Start evaluation
    start = get_timestamp();
    
    cblas_saxpy(ARRAY_SIZE, alpha[0], x0, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[1], x1, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[2], x2, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[3], x3, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[4], x4, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[5], x5, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[6], x6, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[7], x7, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[8], x8, 1, y, 1);
    cblas_saxpy(ARRAY_SIZE, alpha[9], x9, 1, y, 1);

    end = get_timestamp();

    UME::DynamicMemory::AlignedFree(x0);
    UME::DynamicMemory::AlignedFree(x1);
    UME::DynamicMemory::AlignedFree(x2);
    UME::DynamicMemory::AlignedFree(x3);
    UME::DynamicMemory::AlignedFree(x4);
    UME::DynamicMemory::AlignedFree(x5);
    UME::DynamicMemory::AlignedFree(x6);
    UME::DynamicMemory::AlignedFree(x7);
    UME::DynamicMemory::AlignedFree(x8);
    UME::DynamicMemory::AlignedFree(x9);
    UME::DynamicMemory::AlignedFree(y);
    UME::DynamicMemory::AlignedFree(alpha);

    return end - start;
}

#endif
