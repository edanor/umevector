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
// ***This file has been automatically generated***
//
#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_

namespace UME {
namespace VECTOR {
    template<typename SCALAR_TYPE, int SIMD_STRIDE> class Scalar;

    template<int SIMD_STRIDE, typename E1> class LogicalLNOTExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISFINExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISINFExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISANExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISNANExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISNORMExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISSUBExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISZEROExpression;
    template<int SIMD_STRIDE, typename E1> class LogicalISZEROSUBExpression;

    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLANDExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLORExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLXORExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalLANDNOTExpression;

    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPGTExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPLTExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPGEExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPLEExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPEQExpression;
    template<int SIMD_STRIDE, typename E1, typename E2> class LogicalCMPNEExpression;


    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticRCPExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticNEGExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticABSExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticSQRTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticROUNDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticFLOORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticCEILExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticEXPExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOGExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOG10Expression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticLOG2Expression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticSINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticCOSExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticTANExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticATANExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticBNOTExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticSSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMAXExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticMINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticBANDNOTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticREMExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticLSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticRSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticROLExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2> class ArithmeticRORExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticBLENDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMDIVExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMSSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMAXExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMMINExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMBANDNOTExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMLSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMRSHExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMROLExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E_MASK, typename E2> class ArithmeticMRORExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFMULSUBExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFADDMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1, typename E2, typename E3> class ArithmeticFSUBMULExpression;

    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHADDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHMULExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBANDExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticHBXORExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTINCExpression;
    template<typename SCALAR_TYPE, int SIMD_STRIDE, typename E1> class ArithmeticPOSTDECExpression;
}
}

#include "expressions/UMELogicalExpressionInterface.h"
#include "expressions/UMEArithmeticExpressionInterface.h"

// Scalar expression is a necessary wrapper for scalar types.
#include "terminals/UMEScalar.h"

// Logical expressions should be included before arithmetic expressions

#include "expressions/logical/UMELnotExpression.h"
#include "expressions/logical/UMEIsfinExpression.h"
#include "expressions/logical/UMEIsinfExpression.h"
#include "expressions/logical/UMEIsanExpression.h"
#include "expressions/logical/UMEIsnanExpression.h"
#include "expressions/logical/UMEIsnormExpression.h"
#include "expressions/logical/UMEIssubExpression.h"
#include "expressions/logical/UMEIszeroExpression.h"
#include "expressions/logical/UMEIszerosubExpression.h"
#include "expressions/logical/UMELandExpression.h"
#include "expressions/logical/UMELorExpression.h"
#include "expressions/logical/UMELxorExpression.h"
#include "expressions/logical/UMELandnotExpression.h"

#include "expressions/logical/UMECmpgtExpression.h"
#include "expressions/logical/UMECmpltExpression.h"
#include "expressions/logical/UMECmpgeExpression.h"
#include "expressions/logical/UMECmpleExpression.h"
#include "expressions/logical/UMECmpeqExpression.h"
#include "expressions/logical/UMECmpneExpression.h"


#include "expressions/arithmetic/UMERcpExpression.h"
#include "expressions/arithmetic/UMENegExpression.h"
#include "expressions/arithmetic/UMEAbsExpression.h"
#include "expressions/arithmetic/UMESqrtExpression.h"
#include "expressions/arithmetic/UMERoundExpression.h"
#include "expressions/arithmetic/UMEFloorExpression.h"
#include "expressions/arithmetic/UMECeilExpression.h"
#include "expressions/arithmetic/UMEExpExpression.h"
#include "expressions/arithmetic/UMELogExpression.h"
#include "expressions/arithmetic/UMELog10Expression.h"
#include "expressions/arithmetic/UMELog2Expression.h"
#include "expressions/arithmetic/UMESinExpression.h"
#include "expressions/arithmetic/UMECosExpression.h"
#include "expressions/arithmetic/UMETanExpression.h"
#include "expressions/arithmetic/UMEAtanExpression.h"
#include "expressions/arithmetic/UMEBnotExpression.h"

#include "expressions/arithmetic/UMEAddExpression.h"
#include "expressions/arithmetic/UMESaddExpression.h"
#include "expressions/arithmetic/UMEMulExpression.h"
#include "expressions/arithmetic/UMEDivExpression.h"
#include "expressions/arithmetic/UMESubExpression.h"
#include "expressions/arithmetic/UMESsubExpression.h"
#include "expressions/arithmetic/UMEMaxExpression.h"
#include "expressions/arithmetic/UMEMinExpression.h"
#include "expressions/arithmetic/UMEBandExpression.h"
#include "expressions/arithmetic/UMEBorExpression.h"
#include "expressions/arithmetic/UMEBxorExpression.h"
#include "expressions/arithmetic/UMEBandnotExpression.h"
#include "expressions/arithmetic/UMERemExpression.h"
#include "expressions/arithmetic/UMELshExpression.h"
#include "expressions/arithmetic/UMERshExpression.h"
#include "expressions/arithmetic/UMERolExpression.h"
#include "expressions/arithmetic/UMERorExpression.h"

#include "expressions/arithmetic/UMEBlendExpression.h"
#include "expressions/arithmetic/UMEMaddExpression.h"
#include "expressions/arithmetic/UMEMsaddExpression.h"
#include "expressions/arithmetic/UMEMmulExpression.h"
#include "expressions/arithmetic/UMEMdivExpression.h"
#include "expressions/arithmetic/UMEMsubExpression.h"
#include "expressions/arithmetic/UMEMssubExpression.h"
#include "expressions/arithmetic/UMEMmaxExpression.h"
#include "expressions/arithmetic/UMEMminExpression.h"
#include "expressions/arithmetic/UMEMbandExpression.h"
#include "expressions/arithmetic/UMEMborExpression.h"
#include "expressions/arithmetic/UMEMbxorExpression.h"
#include "expressions/arithmetic/UMEMbandnotExpression.h"
#include "expressions/arithmetic/UMEMlshExpression.h"
#include "expressions/arithmetic/UMEMrshExpression.h"
#include "expressions/arithmetic/UMEMrolExpression.h"
#include "expressions/arithmetic/UMEMrorExpression.h"

#include "expressions/arithmetic/UMEFmuladdExpression.h"
#include "expressions/arithmetic/UMEFmulsubExpression.h"
#include "expressions/arithmetic/UMEFaddmulExpression.h"
#include "expressions/arithmetic/UMEFsubmulExpression.h"

#include "expressions/arithmetic/UMEHaddExpression.h"
#include "expressions/arithmetic/UMEHmulExpression.h"
#include "expressions/arithmetic/UMEHbandExpression.h"
#include "expressions/arithmetic/UMEHborExpression.h"
#include "expressions/arithmetic/UMEHbxorExpression.h"

#include "expressions/arithmetic/UMEPostincExpression.h"
#include "expressions/arithmetic/UMEPostdecExpression.h"

#include "expressions/cast/UMEItofExpression.h"
#include "expressions/cast/UMEFtoiExpression.h"
#include "expressions/cast/UMEUtofExpression.h"
#include "expressions/cast/UMEFtouExpression.h"
#include "expressions/cast/UMEItouExpression.h"
#include "expressions/cast/UMEUtoiExpression.h"

#include "expressions/UMEUintExpressionInterface.h"
#include "expressions/UMEIntExpressionInterface.h"
#include "expressions/UMEFloatExpressionInterface.h"

#endif

