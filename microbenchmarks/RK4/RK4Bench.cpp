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

#include <UMEVector.h>

#include <random>

#include "ScalarTest.h"
#include "UMETest.h"

#define STEPS 20
#define VEC_LEN 64
#define STRIDE 8

int main()
{
    BenchmarkHarness harness;

    harness.registerTest(new ScalarTest<float, 1, 1000>());
    harness.registerTest(new UMETest<float, 1, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 1, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 10, 1000>());
    harness.registerTest(new UMETest<float, 10, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 10, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 100, 1000>());
    harness.registerTest(new UMETest<float, 100, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 100, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 1000, 1000>());
    harness.registerTest(new UMETest<float, 1000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 1000, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 10000, 1000>());
    harness.registerTest(new UMETest<float, 10000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 10000, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 100000, 1000>());
    harness.registerTest(new UMETest<float, 100000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 100000, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 1000000, 1000>());
    harness.registerTest(new UMETest<float, 1000000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 1000000, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 10000000, 1000>());
    harness.registerTest(new UMETest<float,    10000000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float,    10000000, 16, 1000>());

    harness.registerTest(new ScalarTest<float, 100000000, 1000>());
    harness.registerTest(new UMETest<float, 100000000, UME_DEFAULT_SIMD_STRIDE, 1000>());
    harness.registerTest(new UMETest<float, 100000000, 16, 1000>());

    harness.runAllTests(10);



    return 0;
}