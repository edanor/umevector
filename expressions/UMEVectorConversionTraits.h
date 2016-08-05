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
#ifndef UME_VECTOR_CONVERSION_TRAITS_H_
#define UME_VECTOR_CONVERSION_TRAITS_H_

namespace UME {
namespace VECTOR {
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticITOFExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticFTOIExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticUTOFExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticFTOUExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticUTOIExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E2> class ArithmeticITOUExpression;

    // ITOF
    template<typename T, int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait<int32_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOFExpression<float, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOFTrait<int64_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOFExpression<double, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    // FTOI
    template<typename T, int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait<float, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOIExpression<int32_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOITrait<int64_t, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOIExpression<int64_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    // UTOF
    template<typename T, int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait<uint32_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOFExpression<float, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOFTrait<uint64_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOFExpression<double, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    // FTOU
    template<typename T, int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait<float, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOUExpression<uint32_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename FLOAT_EXP>
    class FTOUTrait<uint64_t, SIMD_STRIDE, FLOAT_EXP> {
    public:
        typedef ArithmeticFTOUExpression<uint64_t, SIMD_STRIDE, FLOAT_EXP> CAST_TYPE;
    };

    //UTOI
    template<typename T, int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint8_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int8_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint16_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int16_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint32_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int32_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename UINT_EXP>
    class UTOITrait<uint64_t, SIMD_STRIDE, UINT_EXP> {
    public:
        typedef ArithmeticUTOIExpression<int64_t, SIMD_STRIDE, UINT_EXP> CAST_TYPE;
    };

    // ITOU
    template<typename T, int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait {
    public:
        typedef void CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int8_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint8_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int16_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint16_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int32_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint32_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };

    template<int SIMD_STRIDE, typename INT_EXP>
    class ITOUTrait<int64_t, SIMD_STRIDE, INT_EXP> {
    public:
        typedef ArithmeticITOUExpression<uint64_t, SIMD_STRIDE, INT_EXP> CAST_TYPE;
    };
}
}


#endif