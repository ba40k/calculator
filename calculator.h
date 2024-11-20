//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>


class calculator {
private:
     char* operations;
public:
    calculator();
    bool isCorrect(std::string &expression) const;
    long double calculate(std::string &expression);
    ~calculator();
};



#endif //CALCULATOR_H
