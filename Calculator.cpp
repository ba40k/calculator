//
// Created by radamir on 20.11.24.
//

#include "Calculator.h"
#include "stack.h"
#include <math.h>
#include <numeric>
#include "spdlog/spdlog.h"

void Calculator::addOperation(std::string operationNotation,
                              std::function<long double(std::vector<long double>&)> operationLogic,
                              std::function<bool(std::vector<long double>&)> isAbleChecker, int priority,
                              int numberOfOperands) {
    definedOperations[operationNotation] = {operationLogic,isAbleChecker,priority,numberOfOperands};
}

void Calculator::removeOperation(std::string operationNotation) {
    definedOperations.erase(operationNotation);
}

Calculator::Calculator() {
    // добавление операций
    spdlog::set_level(spdlog::level::trace);

    spdlog::info("Function \"Calculator::Calculator\" has called ");
    addOperation("+", [](std::vector<long double>& operands) { return operands[0] + operands[1]; },
                               [](std::vector<long double> &operands) { return true; }, 0, 2);
    spdlog::trace("Operation + added");
    addOperation("-", [](std::vector<long double>& operands) { return operands[0] - operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 0, 2);
    spdlog::trace("Operation - added");
    addOperation("/", [](std::vector<long double>& operands) { return operands[0] / operands[1]; },
                               [](std::vector<long double>& operands) { return operands[1] != 0; }, 1, 2);
    spdlog::trace("Operation / added");
    addOperation("*", [](std::vector<long double>& operands) { return operands[0] * operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 1, 2);
    spdlog::trace("Operation * added");
    addOperation("^", [](std::vector<long double>& operands) { return std::pow(operands[0], operands[1]); },
                               [](std::vector<long double>& operands) { return (operands[1] > 0); }, 2, 2);
    spdlog::trace("Operation ^ added");
    addOperation("sqrt", [](std::vector<long double>& operands) { return sqrt(operands[0]); },
                               [](std::vector<long double>& operands) { return operands[0] >= 0; }, 3, 1);
    spdlog::trace("Operation sqrt added");
    addOperation("sin", [](std::vector<long double>& operands) { return sin(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
    spdlog::trace("Operation sin added");
    addOperation("cos", [](std::vector<long double>& operands) { return cos(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
    spdlog::trace("Operation cos added");
    spdlog::info("Function \"Calculator::Calculator\" has ended ");
}

void Calculator::executeOperation(Stack<Number> &stackForNumbers,
                                  Stack<AtomicExpression *> &stackForBracketsAndOperations) {
    spdlog::set_level(spdlog::level::trace);
    spdlog::info("Function \"Calculator::executeOperation\" has called ");
    auto castedTop = dynamic_cast<Operation *>(stackForBracketsAndOperations.top()); // берем операцию из стека
    int numberOfOperands = castedTop->getNumberOfOperands(); // смотрим в операции сколько ей надо операндов
    std::vector<long double> operands;
    spdlog::trace("vector<long double> operands had been created");
    while (numberOfOperands--) { // пока не возьмем сколько надо операндов
        if (stackForNumbers.empty()) { // если не можем взять из стека операнд, значит выражение было неправильным
            spdlog::error("in function \"Calculator::executeOperation\" not enough operands");
            throw std::invalid_argument("Calculator::executeOperation");
        }
        operands.push_back(stackForNumbers.top().getValue());
        spdlog::trace("Operand " + std::to_string(stackForNumbers.top().getValue()) + " has pushed into operands");
        stackForNumbers.pop(); // удаляем только что взятый операнд
    }


    reverse(operands.begin(), operands.end());  // из-за особенностей польской нотации мы взяли операнды в обратном порядке
                                                        // например 0-1 в польской нотации имеет вид 01-, если бы мы не сделали переворот, то
                                                        // массив операндов был 1 0 и мы бы отнимали от 1 0 а не наоборот
    spdlog::trace("operands had been reversed");
    spdlog::trace("trying to get operation");
    if (!castedTop->checkIsAbleToMakeOperation(operands)) {
        // проверка на возможность вычисления
        spdlog::error("in function \"Calculator::executeOperation\" detected incalculable expression");
        throw std::invalid_argument("Calculator::executeOperation");
    }
    spdlog::trace("operation getted");
    stackForNumbers<<(Number(castedTop->makeOperation(operands)));
    spdlog::trace(std::to_string(castedTop->makeOperation(operands)) + " was placed into stack");
    stackForBracketsAndOperations.pop(); //  удаляем использованную операцию
    spdlog::trace("operation popped");
    spdlog::info("Function \"Calculator::executeOperation\" has ended ");
}

void Calculator::processNumberCase(Expression &expr, int curPosition, Stack<Number> &stackForNumbers) {
    auto castedTop = dynamic_cast<Number *>(expr[curPosition]);
    if (castedTop) {
        // встречено число - просто выгружаем его в стек для чисел
        stackForNumbers << (*castedTop);
    }
}

void Calculator::processBracketCase(Expression &expr, const int curPosition,
                                    Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                    Stack<Number> &stackForNumbers) {
    auto castedTop = dynamic_cast<Bracket *>(expr[curPosition]);
    if (castedTop) {
        // встречена скобка
        char bracketType = castedTop->bracketType();
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
    auto castedTop = dynamic_cast<Operation *>(expr[curPosition]);
    if (castedTop) {
        // случай когда попалась операция
        int currentPriority = castedTop->getPriority();
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
    Expression expr(stringExpression,definedOperations);

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
bool Calculator::isBracketsBalanced(std::string &stringExpression) {
    int balance =0;
    for (int i = 0; i < stringExpression.size(); i++) {
        if (stringExpression[i]=='(') {
            ++balance;
        }
        else if (stringExpression[i]==')') {
            --balance;
            if (balance<0) {
                return false;
            }
        }
    }
    return (balance == 0);
}
bool Calculator::isAbleToCalculate(std::string &stringExpression) {
    try {
        calculate(stringExpression);
        return true;
    } catch (std::invalid_argument &e) {
        return false;
    }
}
long double Calculator::processString(std::string &stringExpression) {
    if (!isBracketsBalanced(stringExpression)) {
        throw std::invalid_argument("Calculator::processString");
    }
    if (!isAbleToCalculate(stringExpression)) {
        throw std::invalid_argument("Calculator::processString");
    }
    return calculate(stringExpression);
}
