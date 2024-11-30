//
// Created by radamir on 20.11.24.
//

#include "AtomicExpression.h"

std::map<std::string,std::tuple< std::function<long double(std::vector<long double>&)>,
                                            std::function<bool(std::vector<long double>&)>,
                                            int,int>> Operation::definedOperations={};

Number::Number(std::string &str): AtomicExpression("Number") {
    const long double num=stold(str);
    value=num;
}

Number::Number(long double _val): AtomicExpression("Number") {
    value=_val;
}

long double Number::getValue() const {
    return value;
}

Operation::Operation(std::function<long double(std::vector<long double>&)> _operation,
                    std::function<bool(std::vector<long double>&)> _isAbleToMakeOperation, int _priority,
                    int _numberOfOperands) :    AtomicExpression("Operation"), operation(_operation) ,
                                                isAbleToMakeOperation(_isAbleToMakeOperation),
                                                priority(_priority), numberOfOperands(_numberOfOperands){}

 std::function<long double(std::vector<long double>&)> Operation::getOperation(std::string _operation) {
    return std::get<0>(definedOperations[_operation]);
}

std::function<bool(std::vector<long double>&)> Operation::getAbleToMakeOperation(std::string _operation) {
    return std::get<1>(definedOperations[_operation]);
}

int Operation::getPriority(const std::string &_operation) {
    return std::get<2>(definedOperations[_operation]);
}

long double Operation::makeOperation(std::vector<long double> &operands) {
    return operation(operands);
}

int Operation::getPriority()  {
    return priority;
}

bool Operation::isDefined(const std::string &_operation) {
    return (definedOperations.find(_operation)!=definedOperations.end());
}

void Operation::defineOperation(const std::string &operationNotation,
                      std::function<long double (std::vector<long double>&)> operationLogic,
                      std::function<bool (std::vector<long double>&)> isAbleChecker,
                      int priority, int numberOfOperands) {
    definedOperations[operationNotation] = {operationLogic,isAbleChecker,priority,numberOfOperands};
}

void Operation::removeOperation(const std::string &operationNotation) {
    definedOperations.erase(operationNotation);
}

bool Operation::checkIsAbleToMakeOperation(std::vector<long double> &operands) {
    return isAbleToMakeOperation(operands);
}

int Operation::getNumberOfOperands() {
    return numberOfOperands;
}

int Operation::getNumberOfOperands(const std::string &_operation) {
    return (std::get<3>(definedOperations[_operation]));
}


Bracket::Bracket(char _bracket) : AtomicExpression("Bracket") {
    bracket=_bracket;
}

char Bracket::bracketType() {
    return bracket;
}

