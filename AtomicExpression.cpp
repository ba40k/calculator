//
// Created by radamir on 20.11.24.
//

#include "AtomicExpression.h"

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



long double Operation::makeOperation(std::vector<long double> &operands) {
    return operation(operands);
}

int Operation::getPriority()  {
    return priority;
}

bool Operation::checkIsAbleToMakeOperation(std::vector<long double> &operands) {
    return isAbleToMakeOperation(operands);
}

int Operation::getNumberOfOperands() {
    return numberOfOperands;
}


Bracket::Bracket(char _bracket) : AtomicExpression("Bracket") {
    bracket=_bracket;
}

char Bracket::bracketType() {
    return bracket;
}

