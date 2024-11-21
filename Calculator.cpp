//
// Created by radamir on 20.11.24.
//

#include "Calculator.h"
#include "stack.h"
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
                    long double r = stackForNumbers.top().getValue();
                    stackForNumbers>>(1);
                    long double l = stackForNumbers.top().getValue();
                    stackForNumbers>>(1);

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
                        long double r = stackForNumbers.top().getValue();
                        stackForNumbers>>(1);
                        long double l = stackForNumbers.top().getValue();
                        stackForNumbers>>(1);

                        stackForNumbers<<Number(dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(l,r));
                        stackForBracetsAndOperations>>(1);
                   }
            stackForBracetsAndOperations<<(expr[i]);
           // std::cout<<dynamic_cast<Operation*>(expr[i])->getPriority()<<'\n';
        }
    }
    while (!(dynamic_cast<Bracket*>(stackForBracetsAndOperations.top()) &&
                        dynamic_cast<Bracket*>(stackForBracetsAndOperations.top())->bracketType() == '(')) {
        long double r = stackForNumbers.top().getValue();
        stackForNumbers>>(1);
        long double l = stackForNumbers.top().getValue();
        stackForNumbers>>(1);

        res += dynamic_cast<Operation*>(stackForBracetsAndOperations.top())->makeOperation(l,r);
        stackForBracetsAndOperations>>(1);
    }
    while (!stackForNumbers.empty()) {
        res+=stackForNumbers.top().getValue();
        stackForNumbers>>(1);
    }
    return res;
}
