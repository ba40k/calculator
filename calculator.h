//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "expression.h"

class calculator {
public:
    calculator() = default;
    long double calculate(expression& exp);
    ~calculator() = default;
};



#endif //CALCULATOR_H
