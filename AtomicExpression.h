//
// Created by radamir on 20.11.24.
//

#ifndef ATOMICEXPRESSION_H
#define ATOMICEXPRESSION_H
#include <map>
#include <functional>
#include <string>
#include <utility>
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
    static std::map<std::string,std::tuple< std::function<long double(long double , long double)>,
                                            std::function<bool(long double, long double)>,
                                            int>> definedOperations;
    std::function<long double(long double , long double)> operation;
    std::function<bool(long double, long double)> isAbleToMakeOperation;
    int priority;
public:
    static bool isDefined(std::string _operation);
    static std::function<long double(long double, long double)> getOperation(std::string _operation);
    static std::function<bool(long double, long double)> getAbleToMakeOperation(std::string _operation);
    static void defineOperation(std::string operationNotation,
                      std::function<long double (long double, long double)> operationLogic,
                      std::function<bool (long double, long double)> isAbleChecker,
                      int priority);
    static void removeOperation(std::string operationNotation);
    static int getPriority(std::string _operation);
    long double makeOperation(Number l, Number r);
    bool checkIsAbleToMakeOperation(long double a, long double b);
    int getPriority();
    Operation(std::function<long double(long double , long double)> _operation,
            std::function<bool(long double, long double)> _isAbleToMakeOperation,int _priority);
};
class Bracket : public AtomicExpression {
    char bracket;
public:
    Bracket(char _bracket);
    char bracketType();
};



#endif //ATOMICEXPRESSION_H
