//
// Created by radamir on 20.11.24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "AtomicExpression.h"
#include <string>

using operationsStorage = std::map<std::string, std::tuple< std::function<long double(std::vector<long double>&)>, std::function<bool(std::vector<long double>&)>, int, int >>;

class Expression {
    AtomicExpression** expr;
    bool isHaveUnidentified;
    bool relatesToNumbers(char ch);
    bool relatesToBrackets(char ch);
    bool relatesToOperations(std::string &str, operationsStorage &definedOperations);
    int curSize;
    bool isDefined(const std::string &_operation, operationsStorage &definedOperations);
    std::function<long double(std::vector<long double>&)> getOperation(std::string &_operation, operationsStorage &definedOperations);
    std::function<bool(std::vector<long double>&)> getCheckerOfOperationAbility(std::string &_operation, operationsStorage &definedOperations);
    int getPriority(const std::string &_operation, operationsStorage &definedOperations);
    int getNumberOfOperands (const std::string &_operation, operationsStorage &definedOperations);
public:
    Expression(std::string &str,operationsStorage &definedOperations);
    AtomicExpression* operator[](int i);
    int size() const;
    ~Expression();
};


#endif //EXPRESSION_H
