//
// Created by radamir on 20.11.24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "AtomicExpression.h"
#include <string>


class expression {
    AtomicExpression** expr;
    bool isHaveUnidentified;
    int curSize;
public:
    expression(std::string &str);
    bool isCorrect();
    AtomicExpression* operator[](int i);
    int size() const;
    ~expression();
};


#endif //EXPRESSION_H
