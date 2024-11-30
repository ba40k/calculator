//
// Created by radamir on 20.11.24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "AtomicExpression.h"
#include <string>


class Expression {
    AtomicExpression** expr;
    bool isHaveUnidentified;
    bool relatesToNumbers(char ch);
    bool relatesToBrackets(char ch);
    bool relatesToOperations(std::string &str);
    int curSize;
public:
    Expression(std::string &str);
    bool isCorrect();
    AtomicExpression* operator[](int i);
    int size() const;
    ~Expression();
};


#endif //EXPRESSION_H
