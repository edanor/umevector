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
#ifndef UME_SCALAR_H_
#define UME_SCALAR_H_

namespace UME {
namespace VECTOR {

    template<typename SCALAR_TYPE, int SIMD_STRIDE = UME_DEFAULT_SIMD_STRIDE>
    class Scalar : public ArithmeticExpression < SCALAR_TYPE, SIMD_STRIDE, Scalar<SCALAR_TYPE, SIMD_STRIDE> >
    {
        const SCALAR_TYPE _e1;
        //SCALAR_TYPE * _e1;

    public:
    
        UME_FORCE_INLINE Scalar(SCALAR_TYPE & value) : _e1(value) {}
        UME_FORCE_INLINE Scalar(SCALAR_TYPE && value) : _e1(value) {}

        UME_FORCE_INLINE Scalar(Scalar && other) : _e1(other._e1) { } //: _e1(value._e1) {}
        UME_FORCE_INLINE Scalar(const Scalar & other) : _e1(other._e1) { }

        UME_FORCE_INLINE static int LENGTH() { return 1; }
        
        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE> evaluate_SIMD(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, SIMD_STRIDE>(_e1);
        }

        UME_FORCE_INLINE UME::SIMD::SIMDVec<SCALAR_TYPE, 1> evaluate_scalar(int index)
        {
            return UME::SIMD::SIMDVec<SCALAR_TYPE, 1>(_e1);
        }

        Scalar& operator=(Scalar&& other) {
            _e1 = other._e1;
            return *this;
        }

    };

    template<int SIMD_STRIDE>
    class Scalar<bool, SIMD_STRIDE> : public LogicalExpression <SIMD_STRIDE, Scalar<bool, SIMD_STRIDE> >
    {
        const bool _e1;
        //SCALAR_TYPE * _e1;

    public:
        UME_FORCE_INLINE Scalar(bool & value) : _e1(value) {}
        UME_FORCE_INLINE Scalar(bool && value) : _e1(value) {}

        UME_FORCE_INLINE Scalar(Scalar && other) : _e1(other._e1) { } //: _e1(value._e1) {}
        UME_FORCE_INLINE Scalar(const Scalar & other) : _e1(other._e1) { }

        UME_FORCE_INLINE static int LENGTH() { return 1; }

        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<SIMD_STRIDE> evaluate_SIMD(int index)
        {
            return UME::SIMD::SIMDVecMask<SIMD_STRIDE>(_e1);
        }

        UME_FORCE_INLINE UME::SIMD::SIMDVecMask<1> evaluate_scalar(int index)
        {
            return UME::SIMD::SIMDVecMask<1>(_e1);
        }

        Scalar& operator=(Scalar&& other) {
            _e1 = other._e1;
            return *this;
        }
    };

}
}
#endif
