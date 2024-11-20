#include "stack.h"

#include <iostream>

#include "calculator.h"
#include "AtomicExpression.h"
#include "AtomicExpression.h"
#include "expression.h"
int main() {
    std::string input;
    std::cin >> input;
    calculator calculatorDevice;
    expression formula(input);
    std::cout<<calculatorDevice.calculate(formula);
}
