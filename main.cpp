#include "stack.h"

#include <iostream>

#include "Calculator.h"
int main() {
    std::string input;
    std::cin >> input;
    Calculator calculatorDevice;
    std::cout<<calculatorDevice.calculate(input);
}
