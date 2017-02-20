// The MIT License (MIT)
//
// Copyright (c) 2016 CERN
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

#ifndef UME_BENCH_H_
#define UME_BENCH_H_

#include "../../../UMEVector.h"

template<typename FLOAT_T>
UME_NEVER_INLINE TIMING_RES test_ume_single(int ARRAY_SIZE)
{
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

    start = get_timestamp();

    UME::VECTOR::Vector<float> x_vec(ARRAY_SIZE, x);
    UME::VECTOR::Vector<float> y_vec(ARRAY_SIZE, y);
    UME::VECTOR::Scalar<float> alpha_s(alpha);
    
    y_vec = alpha_s*x_vec + y_vec;    
    
    end = get_timestamp();

    UME::DynamicMemory::AlignedFree(x);
    UME::DynamicMemory::AlignedFree(y);

    return end - start;
}

template<typename FLOAT_T>
UME_NEVER_INLINE TIMING_RES test_ume_chained(int ARRAY_SIZE)
{
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
    alpha = (FLOAT_T*) UME::DynamicMemory::AlignedMalloc(10*sizeof(FLOAT_T), sizeof(FLOAT_T));
  
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
    }
    
    for(int i = 0; i < 10; i++) {
        alpha[i] = static_cast <FLOAT_T> (rand()) / static_cast <FLOAT_T> (RAND_MAX);
    }

    start = get_timestamp();

    UME::VECTOR::Vector<float> x0_vec(ARRAY_SIZE, x0);
    UME::VECTOR::Vector<float> x1_vec(ARRAY_SIZE, x1);
    UME::VECTOR::Vector<float> x2_vec(ARRAY_SIZE, x2);
    UME::VECTOR::Vector<float> x3_vec(ARRAY_SIZE, x3);
    UME::VECTOR::Vector<float> x4_vec(ARRAY_SIZE, x4);
    UME::VECTOR::Vector<float> x5_vec(ARRAY_SIZE, x5);
    UME::VECTOR::Vector<float> x6_vec(ARRAY_SIZE, x6);
    UME::VECTOR::Vector<float> x7_vec(ARRAY_SIZE, x7);
    UME::VECTOR::Vector<float> x8_vec(ARRAY_SIZE, x8);
    UME::VECTOR::Vector<float> x9_vec(ARRAY_SIZE, x9);
    UME::VECTOR::Vector<float> y_vec(ARRAY_SIZE, y);
    
    UME::VECTOR::Scalar<float> alpha0(alpha[0]);
    UME::VECTOR::Scalar<float> alpha1(alpha[1]);
    UME::VECTOR::Scalar<float> alpha2(alpha[2]);
    UME::VECTOR::Scalar<float> alpha3(alpha[3]);
    UME::VECTOR::Scalar<float> alpha4(alpha[4]);
    UME::VECTOR::Scalar<float> alpha5(alpha[5]);
    UME::VECTOR::Scalar<float> alpha6(alpha[6]);
    UME::VECTOR::Scalar<float> alpha7(alpha[7]);
    UME::VECTOR::Scalar<float> alpha8(alpha[8]);
    UME::VECTOR::Scalar<float> alpha9(alpha[9]);
    
    y_vec = y_vec + alpha0*x0_vec + alpha1*x1_vec + 
                    alpha2*x2_vec + alpha3*x3_vec + 
                    alpha4*x4_vec + alpha5*x5_vec + 
                    alpha6*x6_vec + alpha7*x7_vec + 
                    alpha8*x8_vec + alpha9*x9_vec;
    
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

    return end - start;
}

#endif
