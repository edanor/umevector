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

// This example shows that it is possible to make some lightweight analysis on the expression.
// In this case we are gathering some metrics regarding the count of specific basic expressions.
// and depth of the expression graph. The same concept can be extended for some user-directed
// analysis or for debugging.

#include <assert.h>

#include "../UMEVector.h"

#define VECTOR_LEN 1000
#define SIMD_LEN 8

class ComplexityAnalysis {
public:
    int load_count;
    int store_count;

    int mul_count;
    int add_count;

    int sin_count;
    int abs_count;

    int max_depth;
    int curr_depth;

    // There is always at least one store operation per expression traversal.
    ComplexityAnalysis() :
        load_count(0),
        store_count(1),
        mul_count(0),
        add_count(0),
        sin_count(0),
        abs_count(0),
        max_depth(0),
        curr_depth(0) {}

    int total_uops() {
        return mul_count + add_count + sin_count + abs_count;
    }

    int total_memops() {
        return load_count + store_count;
    }

    void inc_depth() {
        curr_depth++;
        if (curr_depth > max_depth) max_depth = curr_depth;
    }

    void dec_depth() {
        curr_depth--;
    }
};

template<typename SCALAR_TYPE, int VEC_LEN, int SIMD_STRIDE>
void getEstimate(UME::VECTOR::FloatVector<SCALAR_TYPE, VEC_LEN, SIMD_STRIDE> exp, ComplexityAnalysis & result) {
    result.inc_depth();
    result.load_count++;
    result.dec_depth();
}

template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
void getEstimate(UME::VECTOR::ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> exp, ComplexityAnalysis & result) {
    result.inc_depth();
    result.add_count++;
    getEstimate(exp._e1, result);
    getEstimate(exp._e2, result);
    result.dec_depth();
}

template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
void getEstimate(UME::VECTOR::ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> exp, ComplexityAnalysis & result) {
    result.inc_depth();
    result.mul_count++;
    getEstimate(exp._e1, result);
    getEstimate(exp._e2, result);
    result.dec_depth();
}

template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
void getEstimate(UME::VECTOR::ArithmeticSINExpression<SCALAR_TYPE, SIMD_STRIDE, E1> exp, ComplexityAnalysis & result) {
    result.inc_depth();
    result.sin_count++;
    getEstimate(exp._e1, result);
    result.dec_depth();
}

template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1>
void getEstimate(UME::VECTOR::ArithmeticABSExpression<SCALAR_TYPE, SIMD_STRIDE, E1> exp, ComplexityAnalysis & result) {
    result.inc_depth();
    result.abs_count++;
    getEstimate(exp._e1, result);
    result.dec_depth();
}

int main()
{
    float raw_a[VECTOR_LEN], raw_b[VECTOR_LEN], raw_c[VECTOR_LEN], raw_d[VECTOR_LEN], raw_e[VECTOR_LEN];
    float raw_f[VECTOR_LEN], raw_g[VECTOR_LEN], raw_h[VECTOR_LEN], raw_i[VECTOR_LEN], raw_j[VECTOR_LEN];
    float raw_res[VECTOR_LEN];

    UME::VECTOR::Vector<float, VECTOR_LEN, SIMD_LEN>
        A(raw_a), B(raw_b), C(raw_c), D(raw_d), E(raw_e),
        F(raw_f), G(raw_g), H(raw_h), I(raw_i), J(raw_j);
    UME::VECTOR::Vector<float, VECTOR_LEN, SIMD_LEN> RES(raw_res);

    auto t0 = A * B;
    auto t1 = C * t0;
    auto t2 = D * t1;
    auto t3 = E * t2;
    auto t4 = F * G;
    auto t5 = t3 + t4;
    auto t6 = t5 * H;
    auto t7 = I * J;
    auto t8 = t6 * t7;
    auto t9 = t8.sin();
    auto t10 = t9.abs();

    ComplexityAnalysis c0;
    getEstimate(t0, c0);
    std::cout << "t0: "
        << "load: " << c0.load_count << " "
        << "store: " << c0.store_count << " "
        << "add: " << c0.add_count << " "
        << "mul: " << c0.mul_count << " "
        << "sin: " << c0.sin_count << " "
        << "abs: " << c0.abs_count << "\n";

    ComplexityAnalysis c1;
    getEstimate(t3, c1);
    std::cout << "t3: " 
        << "load: " << c1.load_count << " "
        << "store: " << c1.store_count << " "
        << "add: " << c1.add_count << " "
        << "mul: " << c1.mul_count << " "
        << "sin: " << c1.sin_count << " "
        << "abs: " << c1.abs_count << "\n";

    ComplexityAnalysis c2;
    getEstimate(t10, c2);
    std::cout << "t10: "
        << "load: " << c2.load_count << " "
        << "store: " << c2.store_count << " "
        << "add: " << c2.add_count << " "
        << "mul: " << c2.mul_count << " "
        << "sin: " << c2.sin_count << " "
        << "abs: " << c2.abs_count << "\n";

    // Mind that analysis is performed on the expression graph only.
    // Actual evaluation is deferred until here.
    RES = t10;

    std::cout << "Total Memory Ops         : " << E.LOOP_COUNT()*c2.total_memops() << "\n";
    std::cout << "Total Floating Point Ops : " << E.LOOP_COUNT()*c2.total_uops() << "\n";
    std::cout << "Expression depth         : " << c2.max_depth << "\n";

    return 0;
}