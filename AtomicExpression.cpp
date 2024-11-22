//
// Created by radamir on 20.11.24.
//

#include "AtomicExpression.h"

std::map<std::string,std::tuple< std::function<long double(long double , long double)>,
                                            std::function<bool(long double, long double)>,
                                            int>> Operation::definedOperations={};
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
Operation::Operation(std::function<long double(long double, long double)> _operation,
                    std::function<bool(long double, long double)> _isAbleToMakeOperation, int _priority) : AtomicExpression("Operation"), operation(_operation) ,
                                                                                                            isAbleToMakeOperation(_isAbleToMakeOperation),
                                                                                                            priority(_priority){}
 std::function<long double(long double, long double)> Operation::getOperation(std::string _operation) {
    return std::get<0>(definedOperations[_operation]);
}
std::function<bool(long double, long double)> Operation::getAbleToMakeOperation(std::string _operation) {
    return std::get<1>(definedOperations[_operation]);
}
int Operation::getPriority(std::string _operation) {
    return std::get<2>(definedOperations[_operation]);
}
long double Operation::makeOperation(Number l, Number r) {
    return operation(l.getValue(),r.getValue());
}
int Operation::getPriority()  {
    return priority;
}
bool Operation::isDefined(std::string _operation) {
    return (definedOperations.find(_operation)!=definedOperations.end());
}
void Operation::defineOperation(std::string operationNotation,
                      std::function<long double (long double, long double)> operationLogic,
                      std::function<bool (long double, long double)> isAbleChecker,
                      int priority) {
    definedOperations[operationNotation] = {operationLogic,isAbleChecker,priority};
}
void Operation::removeOperation(std::string operationNotation) {
    definedOperations.erase(operationNotation);
}
bool Operation::checkIsAbleToMakeOperation(long double a, long double b) {
    return isAbleToMakeOperation(a,b);
}

Bracket::Bracket(char _bracket) : AtomicExpression("Bracket") {
    bracket=_bracket;
}
char Bracket::bracketType() {
    return bracket;
}

