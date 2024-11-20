//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>


class calculator {
private:

public:
    calculator() = default;
    bool isCorrect(std::string &expression);
    long double calculate(std::string &expression);
    ~calculator() = default;
};



#endif //CALCULATOR_H
