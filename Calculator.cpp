//
// Created by radamir on 20.11.24.
//

#include "Calculator.h"
#include "stack.h"
#include <math.h>

void Calculator::appOperation(std::string operationNotation,
                              std::function<long double(std::vector<long double>&)> operationLogic,
                              std::function<bool(std::vector<long double>&)> isAbleChecker, int priority,
                              int numberOfOperands) {
    Operation::defineOperation(operationNotation, operationLogic, isAbleChecker, priority, numberOfOperands);
}

void Calculator::removeOperation(std::string operationNotation) {
    Operation::removeOperation(operationNotation);
}

Calculator::Calculator() {
    // добавление операций
    Operation::defineOperation("+", [](std::vector<long double>& operands) { return operands[0] + operands[1]; },
                               [](std::vector<long double> &operands) { return true; }, 0, 2);

    Operation::defineOperation("-", [](std::vector<long double>& operands) { return operands[0] - operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 0, 2);

    Operation::defineOperation("/", [](std::vector<long double>& operands) { return operands[0] / operands[1]; },
                               [](std::vector<long double>& operands) { return operands[1] != 0; }, 1, 2);

    Operation::defineOperation("*", [](std::vector<long double>& operands) { return operands[0] * operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 1, 2);

    Operation::defineOperation("^", [](std::vector<long double>& operands) { return std::pow(operands[0], operands[1]); },
                               [](std::vector<long double>& operands) { return (operands[1] > 0); }, 2, 2);
    Operation::defineOperation("sqrt", [](std::vector<long double>& operands) { return sqrt(operands[0]); },
                               [](std::vector<long double>& operands) { return operands[0] >= 0; }, 3, 1);
    Operation::defineOperation("sin", [](std::vector<long double>& operands) { return sin(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
    Operation::defineOperation("cos", [](std::vector<long double>& operands) { return cos(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
}

void Calculator::executeOperation(Stack<Number> &stackForNumbers,
                                  Stack<AtomicExpression *> &stackForBracketsAndOperations) {
    auto castedTop = dynamic_cast<Operation *>(stackForBracketsAndOperations.top()); // берем операцию из стека
    int numberOfOperands = castedTop->getNumberOfOperands(); // смотрим в операции сколько ей надо операндов
    std::vector<long double> operands;
    while (numberOfOperands--) { // пока не возьмем сколько надо операндов
        if (stackForNumbers.empty()) { // если не можем взять из стека операнд, значит выражение было неправильным
            std::cerr << "Incrorrext expression" << std::endl;
            std::exit(EXIT_FAILURE);
        }
        operands.push_back(stackForNumbers.top().getValue());
        stackForNumbers.pop(); // удаляем только что взятый операнд
    }

    reverse(operands.begin(), operands.end());  // из-за особенностей польской нотации мы взяли операнды в обратном порядке
                                                        // например 0-1 в польской нотации имеет вид 01-, если бы мы не сделали переворот, то
                                                        // массив операндов был 1 0 и мы бы отнимали от 1 0 а не наоборот

    if (!castedTop->checkIsAbleToMakeOperation(operands)) {
        // проверка на возможность вычисления
        std::cerr << "Incrorrext expression" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    stackForNumbers<<(Number(castedTop->makeOperation(operands)));
    stackForBracketsAndOperations.pop();
}

void Calculator::processNumberCase(Expression &expr, int curPosition, Stack<Number> &stackForNumbers) {
    if (dynamic_cast<Number *>(expr[curPosition])) {
        // встречено число - просто выгружаем его в стек для чисел
        stackForNumbers << (*dynamic_cast<Number *>(expr[curPosition]));
    }
}

void Calculator::processBracketCase(Expression &expr, const int curPosition,
                                    Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                    Stack<Number> &stackForNumbers) {
    if (dynamic_cast<Bracket *>(expr[curPosition])) {
        // встречена скобка
        char bracketType = dynamic_cast<Bracket *>(expr[curPosition])->bracketType();
        if (bracketType == '(') {
            // если скобка открывающая - то кладем её в стек и всё
            stackForBracketsAndOperations << (expr[curPosition]);
        } else {
            while (!(dynamic_cast<Bracket *>(stackForBracketsAndOperations.top()) &&
                     dynamic_cast<Bracket *>(stackForBracketsAndOperations.top())->bracketType() == '(')) {
                // выполняем верхнюю операцию
                executeOperation(stackForNumbers, stackForBracketsAndOperations);
            }
            stackForBracketsAndOperations.pop(); // удаляем только что проделанную операцию
        }
    }
}

void Calculator::processOperationsCase(Expression &expr, int curPosition,
                                       Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                       Stack<Number> &stackForNumbers) {
    if (dynamic_cast<Operation *>(expr[curPosition])) {
        // случай когда попалась операция
        int currentPriority = dynamic_cast<Operation *>(expr[curPosition])->getPriority();
        // большой страшный цикл, который по сути просто идет и смотрит на верхнюю операцию и если она приоритетнее, то выполняет ее
        while (!stackForBracketsAndOperations.empty() && dynamic_cast<Operation *>(stackForBracketsAndOperations.top())
               &&
               dynamic_cast<Operation *>(stackForBracketsAndOperations.top())->getPriority() >= currentPriority) {
            // выполняем верхнюю операцию
            executeOperation(stackForNumbers, stackForBracketsAndOperations);
        }
        stackForBracketsAndOperations << (expr[curPosition]);
    }
}

void Calculator::processRemainingOperations(Stack<Number> &stackForNumbers,
                                            Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                            long double &res) {
    while (!stackForBracketsAndOperations.empty()) {
        // досчитывает наименее приоритетные операции, которые ничем не были вытеснены
        executeOperation(stackForNumbers, stackForBracketsAndOperations);
    }

    while (!stackForNumbers.empty()) {
        // после обработки последних операций в стеке остались числа, которые надо "доесть"
        res += stackForNumbers.top().getValue();
        stackForNumbers.pop();
    }
}

long double Calculator::calculate(std::string &stringExpression) {
    Expression expr(stringExpression);
    if (!expr.isCorrect()) {
        std::cerr << "Invalid expression: " << stringExpression << std::endl;
        std::exit(EXIT_FAILURE);
    }
    long double res = 0;
    int curSize = expr.size();
    Stack<Number> stackForNumbers;
    Stack<AtomicExpression *> stackForBracketsAndOperations;

    for (int i = 0; i < curSize; i++) {
        processNumberCase(expr, i, stackForNumbers);

        processBracketCase(expr, i, stackForBracketsAndOperations, stackForNumbers);

        processOperationsCase(expr, i, stackForBracketsAndOperations, stackForNumbers);
    }

    processRemainingOperations(stackForNumbers, stackForBracketsAndOperations, res);

    return res;
}
