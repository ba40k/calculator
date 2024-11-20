//
// Created by radamir on 20.11.24.
//

#include "AtomicExpression.h"


Number::Number(std::string &str): AtomicExpression() {
    const long double num=stold(str);
    value=num;
}
Number::Number(long double _val): AtomicExpression() {
    value=_val;
}
long double Number::getValue() const {
    return value;
}
Operation::Operation(std::function<long double(long double, long double)> _operation) : AtomicExpression() {
    operation = _operation;
}
long double Operation::makeOperation(Number l, Number r) {
    return operation(l.getValue(),r.getValue());
}
Bracket::Bracket(char _bracket) : AtomicExpression() {
    bracket=bracket;
}
char Bracket::bracketType() {
    return bracket;
}

