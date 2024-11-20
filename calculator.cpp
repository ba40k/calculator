//
// Created by radamir on 20.11.24.
//

#include "calculator.h"
calculator::calculator() {
    operations = new char[5];
    operations[0] = '+';
    operations[1] = '-';
    operations[2] = '*';
    operations[3] = '/';
    operations[4] = '^';
}
calculator::~calculator() {
    delete[] operations;
    operations = nullptr;
}

bool calculator::isCorrect(std::string &expression) const{
    int balance =0;
    for (int i =0;i<expression.size();i++) {
        if(expression[i] == '(') {
            balance++;
        }
        if (expression[i] == ')') {
            balance--;
            if (balance <0) {
                return false;
            }
        }
    }
    for (int i =0;i<expression.size();i++) {

    }

}
