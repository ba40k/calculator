//
// Created by radamir on 20.11.24.
//

#include "calculator.h"
bool calculator::isCorrect(std::string &expression) {
    int balance =0;
    for (int i =0;i<expression.length();i++) {
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


}
