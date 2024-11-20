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
Operation::Operation(std::function<long double(long double, long double)> _operation,int _priority) : AtomicExpression("Operation"), operation(_operation) ,
                                                                                        priority(_priority){}
long double Operation::makeOperation(Number l, Number r) {
    return operation(l.getValue(),r.getValue());
}
int Operation::getPriority()  {
    return priority;
}

Bracket::Bracket(char _bracket) : AtomicExpression("Bracket") {
    bracket=_bracket;
}
char Bracket::bracketType() {
    return bracket;
}

