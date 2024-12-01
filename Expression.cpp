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
using operationsStorage = std::map<std::string, std::tuple< std::function<long double(std::vector<long double>&)>, std::function<bool(std::vector<long double>&)>, int, int >>;


std::function<long double(std::vector<long double>&)> Expression::getOperation(std::string &_operation,
                                                               operationsStorage &definedOperations) {
    return std::get<0>(definedOperations[_operation]);
}

std::function<bool(std::vector<long double>&)> Expression::getCheckerOfOperationAbility(std::string &_operation,
                                                                        operationsStorage &definedOperations) {
    return std::get<1>(definedOperations[_operation]);
}
int Expression::getPriority(const std::string &_operation,
                    operationsStorage &definedOperations) {
    return std::get<2>(definedOperations[_operation]);
}
bool Expression::isDefined(const std::string &_operation, operationsStorage &definedOperations) {
    return (definedOperations.find(_operation)!=definedOperations.end());
}

int Expression::getNumberOfOperands(const std::string &_operation, operationsStorage &definedOperations) {
    return (std::get<3>(definedOperations[_operation]));
}

bool Expression::relatesToNumbers(char ch) {
    return ((ch>='0' && ch<='9') || ch=='.');
}
bool Expression::relatesToBrackets(char ch) {
    return (ch == '(' || ch == ')');
}

bool Expression::relatesToOperations(std::string &str, operationsStorage &definedOPerations) {
    return isDefined(str,definedOPerations);
}
Expression::Expression(std::string &str, operationsStorage &definedOperations) {
    //небольшой костылек, числа и выражения вида -x будут иметь вид 0-x
    std::string addNullsBeforeMinuses; // преобразованная исходная строка, согласно костылю выше
    for (int i =0;i<str.size();i++) {
        char ch = str[i];
        if (ch == '-' && (i==0 || str[i-1] == '(')) { // проверяем то что у нас унарный минус применяется к числу или выражению
            addNullsBeforeMinuses.push_back('0');
        }
        addNullsBeforeMinuses.push_back(ch);
    }
    str = addNullsBeforeMinuses; // применяем изменения

    isHaveUnidentified=false; // флаг, который говорит о том есть ли неопознанные символы в строке
    std::vector<std::string> tokens;  // строка куда мы складываем опознанные части строки
    std::string buf; // буфер куда мы складываем символы строки на опознание
    for (int i = 0; i < str.size(); i++) {
        if (relatesToNumbers(str[i])) { //  если наткнулись на цифру, то
            buf += str[i];              //  кидаем ее в буфер
            if (i == str.size() - 1) {  //  проверяем, если она последняя в строке, то значит она и есть число
                tokens.push_back(buf);  // кидаем ее в опознанные
                buf.clear();            // чистим буфер
            }
            else {
                if (!relatesToNumbers(str[i+1])) { // если же цифра не последний символ строки, то
                                                   // надо убедиться что после нее нет других цифр
                                                   // если нет, то спокойно кидаем в опознанные и чистим буфер
                    tokens.push_back(buf);
                    buf.clear();
                }
            }
            // если все же есть цифры после, то читаем число дальше
            continue;
        }
        if (relatesToBrackets(str[i])) {
            if (!buf.empty()) { // если буфер не пуст и мы встретили скобку, значит то что в буфере не операция и не число
                                // тогда это нечто неопознанное - выражение неверно
                std::cerr<<"Invalid expression"<<std::endl;
                exit(EXIT_FAILURE);
            }
            // просто кидаем скобку к опознаным
            std::string token;
            token+=str[i];
            tokens.push_back(token);
            continue;
        }
        // если мы дошли дло сюда, значит мы имеем дело не с цифрой и не со скобкой
        // тогда единственный вариант - это часть обозначения операции
        buf.push_back(str[i]); // кидаем в буфер и пытаемся опознать
        if (relatesToOperations(buf,definedOperations)) {
            tokens.push_back(buf);
            buf.clear();
            continue;
        }
        // если мы дошли до конца строки или следующий символ не может быть частью обозначения операции - то выражение неверно
        if (i==str.size() - 1 || relatesToNumbers(str[i+1])
                            || relatesToBrackets(str[i+1])) {
            std::cerr<<"Invalid expression"<<std::endl;
            exit(EXIT_FAILURE);
        }

    }

    if (!buf.empty()) {// если буфер не пуст после предыдущего цикла, значит в нем осталось что-то неопознанное
        isHaveUnidentified=1; // возможно лишний иф
    }

    expr = new AtomicExpression*[tokens.size()]; // создаем выражение
    for (int i = 0; i < tokens.size(); i++) { // идем по опознанным строкам
        // тут все очевидно
        if (relatesToBrackets(tokens[i][0])) {
            expr[i] = new Bracket(tokens[i][0]);
            continue;
        }
        if (relatesToOperations(tokens[i], definedOperations)) {
            expr[i] = new Operation(getOperation(tokens[i], definedOperations),
                                    getCheckerOfOperationAbility(tokens[i], definedOperations),
                                    getPriority(tokens[i],definedOperations),
                                    getNumberOfOperands(tokens[i],definedOperations));
            continue;
        }
        if (relatesToNumbers(tokens[i][0])) {
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
    // проверяем имеем ли мы дело с правильной скобочной последовательностью
    int balance=0;
    for (int i = 0; i < curSize; i++) {

        auto b = dynamic_cast<Bracket*>(expr[i]);
        if (b) {

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
    if (balance != 0) {
        return false;
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
