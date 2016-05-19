#ifndef UME_VECTOR_EXPRESSIONS_H_
#define UME_VECTOR_EXPRESSIONS_H_

#include "expressions\UMEExpressionInterface.h"

// Scalar expression is a necessary wrapper for scalar types.
#include "expressions\UMEScalarExpression.h"

// Logical expressions should be included before arithmetic expressions

// Binary expressions
#include "expressions\logical\UMELandExpression.h"
#include "expressions\logical\UMELorExpression.h"

// Unary expressions
#include "expressions\arithmetic\UMEPostincExpression.h"

// Binary expressions
#include "expressions\arithmetic\UMEAddExpression.h"
#include "expressions\arithmetic\UMESubExpression.h"
#include "expressions\arithmetic\UMEMulExpression.h"
#include "expressions\arithmetic\UMEDivExpression.h"

// Binary expressions with mask
#include "expressions\arithmetic\UMEMaddExpression.h"

// Ternary expressions
#include "expressions\arithmetic\UMEFmaddExpression.h"

// Unary reduction expressions
#include "expressions\arithmetic\UMEHaddExpression.h"


#endif
