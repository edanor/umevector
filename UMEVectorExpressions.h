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
// ***This file has been automatically generated***
//
#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_

namespace UME {
namespace VECTOR {

#include "expressions/common/UMEForwardDeclarations.h"

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

#include "expressions/arithmetic/UMEGatherExpression.h"

#include "expressions/arithmetic/UMEAddaExpression.h"

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
#include "expressions/arithmetic/UMEHmaxExpression.h"
#include "expressions/arithmetic/UMEHminExpression.h"

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

