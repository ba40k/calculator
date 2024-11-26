//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "Expression.h"

class Calculator {
public:
    Calculator();
    void appOperation(std::string operationNotation,
                      std::function<long double (long double, long double)> operationLogic,
                      std::function<bool (long double, long double)> isAbleChecker,
                      int priority, int numberOfOperands);
    void removeOperation(std::string operationNotation);
    long double calculate(std::string &stringExpression);
    ~Calculator() = default;
};



#endif //CALCULATOR_H
