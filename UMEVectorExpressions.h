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
#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_

#include "expressions/UMEExpressionInterface.h"

// Terminal symbols:
// Scalar expression is a necessary wrapper for scalar types.
#include "expressions/UMEScalarExpression.h"

// Logical expressions should be included before arithmetic expressions

// Binary logical expressions
#include "expressions/logical/UMELandExpression.h"
#include "expressions/logical/UMELorExpression.h"

// Binary logical comparison expressions
#include "expressions/logical/UMECmpgtExpression.h"
#include "expressions/logical/UMECmpltExpression.h"
#include "expressions/logical/UMECmpgeExpression.h"
#include "expressions/logical/UMECmpleExpression.h"
#include "expressions/logical/UMECmpeqExpression.h"
#include "expressions/logical/UMECmpneExpression.h"

// Unary expressions
#include "expressions/arithmetic/UMEPostincExpression.h"
#include "expressions/arithmetic/UMESqrtExpression.h"

// Binary expressions
#include "expressions/arithmetic/UMEAddExpression.h"
#include "expressions/arithmetic/UMESubExpression.h"
#include "expressions/arithmetic/UMEMulExpression.h"
#include "expressions/arithmetic/UMEDivExpression.h"


// Binary expressions with mask
#include "expressions/arithmetic/UMEMaddExpression.h"
#include "expressions/arithmetic/UMEMsubExpression.h"
#include "expressions/arithmetic/UMEMmulExpression.h"
#include "expressions/arithmetic/UMEMdivExpression.h"
#include "expressions/arithmetic/UMEBlendExpression.h"

// Ternary expressions
#include "expressions/arithmetic/UMEFmuladdExpression.h"
#include "expressions/arithmetic/UMEFaddmulExpression.h"
#include "expressions/arithmetic/UMEFmulsubExpression.h"
#include "expressions/arithmetic/UMEFsubmulExpression.h"

// Unary reduction expressions
#include "expressions/arithmetic/UMEHaddExpression.h"
#include "expressions/arithmetic/UMEHmulExpression.h"
#include "expressions/arithmetic/UMEHbandExpression.h"
#include "expressions/arithmetic/UMEHborExpression.h"
#include "expressions/arithmetic/UMEHbxorExpression.h"

// Cast expressions
#include "expressions/cast/UMEItofExpression.h"
#include "expressions/cast/UMEFtoiExpression.h"
#include "expressions/cast/UMEUtofExpression.h"
#include "expressions/cast/UMEFtouExpression.h"
#include "expressions/cast/UMEItouExpression.h"
#include "expressions/cast/UMEUtoiExpression.h"

#endif
