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
    explicit AtomicExpression(const std::string &_type) : type(_type) {};
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
    static std::map<std::string,std::tuple< std::function<long double(std::vector<long double>&)>,
                                            std::function<bool(std::vector<long double>&)>,
                                            int,int>> definedOperations;

    std::function<long double(std::vector<long double>&)> operation;
    std::function<bool(std::vector<long double>&)> isAbleToMakeOperation;
    int numberOfOperands;
    int priority;
public:
    static bool isDefined(const std::string &_operation);
    static std::function<long double(std::vector<long double>&)> getOperation(std::string _operation);
    static std::function<bool(std::vector<long double>&)> getAbleToMakeOperation(std::string _operation);
    static void defineOperation(const std::string &operationNotation,
                      std::function<long double (std::vector<long double>&)> operationLogic,
                      std::function<bool (std::vector<long double>&)> isAbleChecker,
                      int priority, int numberOfOperands);
    static void removeOperation(const std::string &operationNotation);
    static int getPriority(const std::string &_operation);
    long double makeOperation(std::vector<long double> &operands);
    bool checkIsAbleToMakeOperation(std::vector<long double> &operands);
    int getPriority();
    int getNumberOfOperands();
    static int getNumberOfOperands (const std::string &_operation);
    Operation(std::function<long double(std::vector<long double>&)> _operation,
            std::function<bool(std::vector<long double>&)> _isAbleToMakeOperation,int _priority,
            int _numberOfOperands);
};
class Bracket : public AtomicExpression {
    char bracket;
public:
    Bracket(char _bracket);
    char bracketType();
};



#endif //ATOMICEXPRESSION_H
