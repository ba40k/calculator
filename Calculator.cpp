//
// Created by radamir on 20.11.24.
//

#include "Calculator.h"
#include "stack.h"
#include <math.h>
void Calculator::appOperation(std::string operationNotation,
                              std::function<long double(long double, long double)> operationLogic,
                              std::function<bool(long double, long double)> isAbleChecker, int priority,
                              int numberOfOperands) {
    Operation::defineOperation(operationNotation, operationLogic, isAbleChecker, priority,numberOfOperands);
}
void Calculator::removeOperation(std::string operationNotation) {
    Operation::removeOperation(operationNotation);
}
Calculator::Calculator() {
    Operation::defineOperation("+",[](long double a, long double b){return a + b;},
                                [](long double a, long double b){return true;},0,2);

    Operation::defineOperation("-",[](long double a, long double b){return a - b;},
                                [](long double a, long double b){return true;},0,2);

    Operation::defineOperation("/",[](long double a, long double b){return a / b;},
                                [](long double a, long double b){return b!=0;},1,2);

    Operation::defineOperation("*",[](long double a, long double b){return a * b;},
                                [](long double a, long double b){return true;},1,2);

    Operation::defineOperation("^",[](long double a, long double b){return std::pow(a,b);},
                                [](long double a, long double b){return (b>0);},2,2);
    Operation::defineOperation("sqrt",[](long double a, long double b =0){return sqrt(a);},
                                [](long double a, long double b){return a>=0;},3,1);
    Operation::defineOperation("sin",[](long double a, long double b =0){return sin(a);},
                                [](long double a, long double b){return true;},3,1);
    Operation::defineOperation("cos",[](long double a, long double b =0){return cos(a);},
                                [](long double a, long double b){return true;},3,1);
}

long double Calculator::calculate(std::string &stringExpression) {
    Expression expr(stringExpression);
    if (!expr.isCorrect()) {
        std::cerr << "Invalid expression: " << stringExpression << std::endl;
        std::exit(EXIT_FAILURE);
    }
    long double res=0;
    int curSize = expr.size();
    Stack<Number> stackForNumbers;
    Stack<AtomicExpression*> stackForBracetsAndOperations;

    stackForBracetsAndOperations<<(new Bracket('('));

    for (int i =0;i<curSize;i++) {
        if (dynamic_cast<Number*>(expr[i])) {
            stackForNumbers<<(*dynamic_cast<Number*>(expr[i]));
        }
        if (dynamic_cast<Bracket*>(expr[i])) {
            char bracketType = dynamic_cast<Bracket*>(expr[i])->bracketType();
            if (bracketType == '(') {
                stackForBracetsAndOperations<<(expr[i]);
            }
            else {
                while (!(dynamic_cast<Bracket*>(stackForBracetsAndOperations.top()) &&
                         dynamic_cast<Bracket*>(stackForBracetsAndOperations.top())->bracketType() == '(')) {
                    if (stackForNumbers.empty()) {
                        std::cerr << "Incrorrext expression"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    long double r = stackForNumbers.top().getValue();
                    stackForNumbers>>(1);

                    if (dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->getNumberOfOperands()==1) {

                        if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(r,0)) {
                            std::cerr << "Incrorrext expression"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }

                        stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(r,0));
                        stackForBracetsAndOperations>>(1);
                        continue;
                    }

                    if (stackForNumbers.empty()) {
                        std::cerr << "Incrorrext expression"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    long double l = stackForNumbers.top().getValue();
                    stackForNumbers>>(1);
                    if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(l,r)) {
                        std::cerr << "Incrorrext expression"<<std::endl;
                        std::exit(EXIT_FAILURE);
                    }
                    stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(l,r));
                    stackForBracetsAndOperations>>(1);

                }
                stackForBracetsAndOperations>>(1);
            }
        }
        if (dynamic_cast<Operation*>(expr[i])) {
            int currentPriority = dynamic_cast<Operation*>(expr[i])->getPriority();
            while (stackForBracetsAndOperations.size()>0 && dynamic_cast<Operation*>(stackForBracetsAndOperations.top()) &&
                   dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->getPriority() >= currentPriority){
                        if (stackForNumbers.empty()) {
                            std::cerr << "Incrorrext expression"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        long double r = stackForNumbers.top().getValue();
                        stackForNumbers>>(1);

                        if (dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->getNumberOfOperands()==1) {

                            if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(r,0)) {
                                std::cerr << "Incrorrext expression"<<std::endl;
                                std::exit(EXIT_FAILURE);
                            }

                            stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(r,0));
                            stackForBracetsAndOperations>>(1);
                            continue;
                        }

                        if (stackForNumbers.empty()) {
                            std::cerr << "Incrorrext expression"<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        long double l = stackForNumbers.top().getValue();
                        stackForNumbers>>(1);
                        if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(l,r)) {
                            std::cerr<<"Invalid operation: "<<std::endl;
                            std::exit(EXIT_FAILURE);
                        }
                        stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(l,r));
                        stackForBracetsAndOperations>>(1);
                   }
            stackForBracetsAndOperations<<(expr[i]);
        }
    }
    while (!(dynamic_cast<Bracket*>(stackForBracetsAndOperations.top()) &&
                        dynamic_cast<Bracket*>(stackForBracetsAndOperations.top())->bracketType() == '(')) {
        if (stackForNumbers.empty()) {
            std::cerr << "Incrorrext expression"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
        long double r = stackForNumbers.top().getValue();
        stackForNumbers>>(1);

        if (dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->getNumberOfOperands()==1) {

            if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(r,0)) {
                std::cerr << "Incrorrext expression"<<std::endl;
                std::exit(EXIT_FAILURE);
            }

            stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(r,0));
            stackForBracetsAndOperations>>(1);
            continue;
        }

        if (stackForNumbers.empty()) {
            std::cerr << "Incrorrext expression"<<std::endl;
            std::exit(EXIT_FAILURE);
        }
        long double l = stackForNumbers.top().getValue();
        stackForNumbers>>(1);
        if (!dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->checkIsAbleToMakeOperation(l,r)) {
            std::cerr<<"Invalid operation: "<<std::endl;
            std::exit(EXIT_FAILURE);
        }

        stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(l,r));
        stackForBracetsAndOperations>>(1);
    }
    while (!stackForNumbers.empty()) {
        res+=stackForNumbers.top().getValue();
        stackForNumbers>>(1);
    }
    return res;
}
