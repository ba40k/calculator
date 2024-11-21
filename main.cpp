#include "stack.h"

#include <iostream>

#include "Calculator.h"
int main() {
    std::string input;
    std::cin >> input;
    std::cout<<Calculator::calculate(input);
}
