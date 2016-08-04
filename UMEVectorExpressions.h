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
