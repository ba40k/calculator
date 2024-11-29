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
    Operation::defineOperation(operationNotation, operationLogic, isAbleChecker, priority, numberOfOperands);
}

void Calculator::removeOperation(std::string operationNotation) {
    Operation::removeOperation(operationNotation);
}

Calculator::Calculator() {
    // добавление операций
    Operation::defineOperation("+", [](long double a, long double b) { return a + b; },
                               [](long double a, long double b) { return true; }, 0, 2);

    Operation::defineOperation("-", [](long double a, long double b) { return a - b; },
                               [](long double a, long double b) { return true; }, 0, 2);

    Operation::defineOperation("/", [](long double a, long double b) { return a / b; },
                               [](long double a, long double b) { return b != 0; }, 1, 2);

    Operation::defineOperation("*", [](long double a, long double b) { return a * b; },
                               [](long double a, long double b) { return true; }, 1, 2);

    Operation::defineOperation("^", [](long double a, long double b) { return std::pow(a, b); },
                               [](long double a, long double b) { return (b > 0); }, 2, 2);
    Operation::defineOperation("sqrt", [](long double a, long double b) { return sqrt(a); },
                               [](long double a, long double b) { return a >= 0; }, 3, 1);
    Operation::defineOperation("sin", [](long double a, long double b) { return sin(a); },
                               [](long double a, long double b) { return true; }, 3, 1);
    Operation::defineOperation("cos", [](long double a, long double b) { return cos(a); },
                               [](long double a, long double b) { return true; }, 3, 1);
}

void Calculator::executeOperation(Stack<Number> &stackForNumbers,
                                  Stack<AtomicExpression *> &stackForBracketsAndOperations) {
    if (stackForNumbers.empty()) {
        std::cerr << "Incrorrext expression" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const long double r = stackForNumbers.top().getValue();
    stackForNumbers.pop();
    auto castedTop = dynamic_cast<Operation *>(stackForBracketsAndOperations.top());

    if (castedTop->getNumberOfOperands() == 1) {
        // если операция унарная то мы извлекаем только одно число из стека
        if (!castedTop->checkIsAbleToMakeOperation(r, 0)) {
            // проверка на возможность вычисления
            std::cerr << "Incrorrext expression" << std::endl;
            std::exit(EXIT_FAILURE);
        }

        stackForNumbers << Number(castedTop->makeOperation(r, 0));
        stackForBracketsAndOperations.pop();
        return; // сделали операцию и идем дальше
    }
    // повторяем все ранее сделаное но уже для второго операнда
    if (stackForNumbers.empty()) {
        std::cerr << "Incrorrext expression" << std::endl;
        std::exit(EXIT_FAILURE);
    }

    const long double l = stackForNumbers.top().getValue();
    stackForNumbers.pop();
    if (!castedTop->checkIsAbleToMakeOperation(l, r)) {
        std::cerr << "Incrorrext expression" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    stackForNumbers << Number(castedTop->makeOperation(l, r));
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
