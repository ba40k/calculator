//
// Created by radamir on 20.11.24.
//

#include "Expression.h"
#include "stack.h"
#include <cstring>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <math.h>
#include <ostream>

Expression::Expression(std::string &str) {

    std::string addNullsBeforeMinuses;
    for (int i =0;i<str.size();i++) {
        char ch = str[i];
        if (ch == '-' && (i==0 || str[i-1] == '(')) {
            addNullsBeforeMinuses.push_back('0');
        }
        addNullsBeforeMinuses.push_back(ch);
    }
    str = addNullsBeforeMinuses;

    isHaveUnidentified=false;
    std::vector<std::string> tokens;
    std::string buf;
    for (int i = 0; i < str.size(); i++) {
        if ((str[i]>='0' && str[i]<='9') || str[i]=='.') {
            if (!buf.empty()) {
                std::cerr<<"Invalid expression"<<std::endl;
                exit(EXIT_FAILURE);
            }
            buf += str[i];
            if (i == str.size() - 1) {
                tokens.push_back(buf);
                buf.clear();
            }
            else {
                if (!((str[i+1]>='0' && str[i+1]<='9') || str[i+1]=='.')) {
                    tokens.push_back(buf);
                    buf.clear();
                }
            }
            continue;
        }
        if (str[i] == '(' || str[i] == ')') {
            if (!buf.empty()) {
                std::cerr<<"Invalid expression"<<std::endl;
                exit(EXIT_FAILURE);
            }
            std::string token;
            token+=str[i];
            tokens.push_back(token);
            continue;
        }
        buf.push_back(str[i]);
        if (Operation::isDefined(buf)) {
            tokens.push_back(buf);
            buf.clear();
        }

    }
    if (!buf.empty()) {
        isHaveUnidentified=1;
    }
    expr = new AtomicExpression*[tokens.size()];
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i]=="(" || tokens[i]==")") {
            expr[i] = new Bracket(tokens[i][0]);
            continue;
        }
        if (Operation::isDefined(tokens[i])) {
            expr[i] = new Operation(Operation::getOperation(tokens[i]),
                                    Operation::getAbleToMakeOperation(tokens[i]),
                                    Operation::getPriority(tokens[i]),
                                    Operation::getNumberOfOperands(tokens[i]));
        }
        if (tokens[i][0]>='0' && tokens[i][0]<='9') {
            expr[i] = new Number(stold(tokens[i]));
        }
    }
    curSize = tokens.size();
    if (isHaveUnidentified) {
        std::cerr<<"Unidentified expression"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
}

int Expression::size() const {
    return curSize;
}
bool Expression::isCorrect() {
    int balance=0;
    for (int i = 0; i < curSize; i++) {
        if (dynamic_cast<Bracket*>(expr[i])) {
            auto b = dynamic_cast<Bracket*>(expr[i]);
            if (b->bracketType()==')') {
                --balance;
            }
            else {
                ++balance;
            }
            if (balance<0) {
                return false;
            }
        }
    }
    return true;
}
Expression::~Expression() {
    for (int i = 0; i < curSize; i++) {
        delete expr[i];
    }
    delete [] expr;
}



AtomicExpression* Expression::operator[](int i) {
    return expr[i];
}
