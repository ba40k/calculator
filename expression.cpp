//
// Created by radamir on 20.11.24.
//

#include "expression.h"

#include <cstring>
#include <string>
#include <vector>
#include <utility>
expression::expression(std::string &str) {
    isHaveUnidentified=0;
    std::vector<std::pair<long double, int>> numbers;
    std::vector<std::pair<char, int>> operations;
    std::vector<std::pair<char, int>> brackets;
    int identifiedSize=0;
    for (int i =0;i<str.size();i++) {
            if (str[i] == '(' || str[i]==')') {
                brackets.push_back({str[i],identifiedSize});
                ++identifiedSize;
            }
    }

    for (int i =0;i<str.size();i++) {
        if (str[i] == '+' || str[i]=='-' || str[i]=='*'
            || str[i]=='/' || str[i]=='^') {
            operations.push_back({str[i],identifiedSize});
            ++identifiedSize;
        }
    }

    std::string buf;

    for (int i =0; i<str.size();i++) {
        if ((str[i]>='0' && str[i]<='9') || str[i]=='.') {
            buf+=str[i];
            ++identifiedSize;
        }
        else {
            long double number = stold(buf);
            numbers.push_back({number,identifiedSize});
            buf.clear();
        }
    }

    if (identifiedSize!=str.size()) {
        isHaveUnidentified=1;
    }
    int expressionSize=0;
    expressionSize += numbers.size();
    expressionSize += operations.size();
    expressionSize += brackets.size();
    expr = new AtomicExpression*[expressionSize];
    for (int i =0;i<numbers.size();i++) {
        expr[numbers[i].second] = new Number(numbers[i].first);
    }
    for (int i =0;i<operations.size();i++) {

    }

}
