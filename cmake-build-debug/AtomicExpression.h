//
// Created by radamir on 20.11.24.
//

#ifndef ATOMICEXPRESSION_H
#define ATOMICEXPRESSION_H
#include <functional>
#include <string>

class AtomicExpression {
public:
    AtomicExpression() = default;
    ~AtomicExpression() = default;
};
class Number : public AtomicExpression {
private:
    long double value;
public:
    Number(std::string &str);
    Number(long double _val);
    long double getValue() const;

};
class Operation : public AtomicExpression {
private:
    std::function<long double(long double , long double)> operation;
public:
    long double makeOperation(Number l, Number r);

    Operation(std::function<long double(long double , long double)> _operation);
};
class Bracket : public AtomicExpression {
    char bracket;
public:
    Bracket(char _bracket);
    char bracketType();
};



#endif //ATOMICEXPRESSION_H
