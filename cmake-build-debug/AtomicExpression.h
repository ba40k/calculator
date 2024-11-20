//
// Created by radamir on 20.11.24.
//

#ifndef ATOMICEXPRESSION_H
#define ATOMICEXPRESSION_H
#include <functional>
#include <string>

class AtomicExpression {
private:
    std::string type;
public:
    AtomicExpression() = default;
    std::string getType() {
        return type;
    }
    AtomicExpression(std::string _type) : type(_type) {};
    virtual ~AtomicExpression() = default;
};
class Number : public AtomicExpression {
private:
    long double value;
public:
    Number() = default;
    Number(std::string &str);
    Number(long double _val);
    long double getValue() const;

};
class Operation : public AtomicExpression {
private:
    std::function<long double(long double , long double)> operation;
    bool division;
    int priority;
public:
    long double makeOperation(Number l, Number r);
    int getPriority();
    Operation(std::function<long double(long double , long double)> _operation, int _priority);
};
class Bracket : public AtomicExpression {
    char bracket;
public:
    Bracket(char _bracket);
    char bracketType();
};



#endif //ATOMICEXPRESSION_H
