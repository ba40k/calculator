#include "stack.h"

#include <iostream>

#include "calculator.h"
#include "cmake-build-debug/AtomicExpression.h"
#include "cmake-build-debug/AtomicExpression.h"
#include "expression.h"
int main() {
    std::string input;
    std::cin >> input;
    calculator calculatorDevice;
    expression formula(input);
    std::cout<<calculatorDevice.calculate(formula);
}
