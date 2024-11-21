//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "Expression.h"

class Calculator {
public:
    Calculator() = delete;

    static long double calculate(std::string &stringExpression);
    ~Calculator() = delete;
};



#endif //CALCULATOR_H
