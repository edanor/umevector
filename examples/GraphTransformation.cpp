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

// This code requires C++14 enabled (-std=c++14)

// This example shows that it is possible to make some lightweight transformations on the expression.
// While this technique is crude and definitely not as powerfull as as dynamic graph handling,
// it still can be usefull for some user-directed transformations e.g. to change the order of
// associative operations.


#include <assert.h>

#include "../UMEVector.h"

#define VECTOR_LEN 1000
#define SIMD_LEN 8

using namespace UME::VECTOR; //we need this to simplify the notation

// Replace an ADD(E1, E2) node with a MUL(E1, E2) node
template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
transform(ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> exp) {
    return ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>(exp._e1, exp._e2);
}

// Replace a MUL(E1, E2) node with an ADD(E1, E2) node
template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2>
ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>
transform(ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2> exp) {
    return ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>(exp._e1, exp._e2);
}

// Replace a sub-expression: ADD(MUL(E1, E2), MUL(E3, E4)) with MUL(ADD(E1, E2), ADD(E3, E4))
template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3, typename E4>
auto transform(
    // The type of input expression. E1-E4 can be either other sub-expressions, scalars or vectors.
    ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE,
    ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
    ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE, E3, E4>> exp)
{
    return ArithmeticMULExpression<SCALAR_TYPE, SIMD_STRIDE,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>,
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E3, E4>>
        (
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E1, E2>(exp._e1._e1, exp._e1._e2),
            ArithmeticADDExpression<SCALAR_TYPE, SIMD_STRIDE, E3, E4>(exp._e2._e1, exp._e2._e2)
        );
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
    auto t1 = transform(t0);

    RES = t1;

    auto t2 = transform(t1);

    RES = t2;

    auto t3 = C * D;
    auto t4 = E * F;
    auto t5 = t3 + t4;

    // t5 is an expression (C*D) + (E*F)
    auto t6 = transform(t5);

    // t6 should now be an expression of (C+D)*(E+F)
    RES = t6;

    return 0;
}