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

        void dispose() {}
    };

}
}
#endif
