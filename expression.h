//
// Created by radamir on 20.11.24.
//

#ifndef EXPRESSION_H
#define EXPRESSION_H
#include "cmake-build-debug/AtomicExpression.h"
#include <string>
#include "OperationFunctions.h"

class expression {
    AtomicExpression** expr;
    bool isHaveUnidentified;
    OperationFunctions funcs;
public:
    expression(std::string &str);
    template<typename T>
    T operator[](int i);


};


#endif //EXPRESSION_H
