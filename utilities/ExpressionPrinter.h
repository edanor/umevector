#pragma once

#include <string>
#include <iostream>

#include "../UMEVector.h"

template<typename EXP>
class ExpressionPrinter
{
    int indent;

public:
    ExpressionPrinter(EXP exp) : indent(0) {
        visit(exp);
    }

    template<typename SCALAR_T, int SIMD_STRIDE>
    void visit(UME::VECTOR::Scalar<SCALAR_T, SIMD_STRIDE> exp) {
        indent++;
        std::cout << std::string(indent, ' ') << "Scalar(" << SIMD_STRIDE << ") : " << exp._e1 << "\n";
        indent--;
    }

    template<typename SCALAR_T, int VEC_LEN, int SIMD_STRIDE>
    void visit(UME::VECTOR::FloatVector<SCALAR_T, VEC_LEN, SIMD_STRIDE> exp) {
        indent++;
        std::cout << std::string(indent, ' ') << "Vector(" << VEC_LEN << ", " << SIMD_STRIDE << ")";
        std::cout << &exp.elements[0] << "\n";
        indent--;
    }

    template<typename SCALAR_T, int SIMD_STRIDE, typename E1, typename E2>
    void visit(UME::VECTOR::ArithmeticADDExpression<SCALAR_T, SIMD_STRIDE, E1, E2> exp) {
        indent++;
        std::cout << std::string(indent, ' ') << "ADD:\n";
        visit(exp._e1);
        visit(exp._e2);
        indent--;
    }

    template<typename SCALAR_T, int SIMD_STRIDE, typename E1, typename E2>
    void visit(UME::VECTOR::ArithmeticMULExpression<SCALAR_T, SIMD_STRIDE, E1, E2> exp) {
        indent++;
        std::cout << std::string(indent, ' ') << "MUL:\n";
        visit(exp._e1);
        visit(exp._e2);
        indent--;
    }

    template<typename SCALAR_T, int SIMD_STRIDE, typename E1>
    void visit(UME::VECTOR::ArithmeticHADDExpression<SCALAR_T, SIMD_STRIDE, E1> exp) {
        indent++;
        std::cout << std::string(indent, ' ') << "HADD(evaluated: " << exp._evaluated << "):\n";
        visit(exp._e1);
        indent--;
    }

};