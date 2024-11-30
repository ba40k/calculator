//
// Created by radamir on 20.11.24.
//

#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <string>
#include "Expression.h"
#include "stack.h"

class Calculator {
private:
    std::map<std::string,std::tuple< std::function<long double(std::vector<long double>&)>,
                                            std::function<bool(std::vector<long double>&)>,
                                            int,int>> definedOperations;

    void processNumberCase(Expression &expr, int curPosition,Stack<Number> &stackForNumbers);

    void processBracketCase(Expression &expr, int curPosition,
        Stack<AtomicExpression*>  &stackForBracketsAndOperations,
        Stack<Number> &stackForNumbers);

    void processOperationsCase(Expression &expr, int curPosition,
        Stack<AtomicExpression*>  &stackForBracketsAndOperations,
        Stack<Number> &stackForNumbers);
    void processRemainingOperations(Stack<Number> &stackForNumbers,
                          Stack<AtomicExpression*>  &stackForBracketsAndOperations,
                          long double &res);
    void executeOperation(Stack<Number> &stackForNumbers,
                          Stack<AtomicExpression*>  &stackForBracketsAndOperations);
public:
    Calculator();
    void addOperation(std::string operationNotation,
                      std::function<long double (std::vector<long double>&)> operationLogic,
                      std::function<bool (std::vector<long double>&)> isAbleChecker,
                      int priority, int numberOfOperands);
    void removeOperation(std::string operationNotation);
    long double calculate(std::string &stringExpression);
    ~Calculator() = default;
};



#endif //CALCULATOR_H
