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


    spdlog::info("Function \"Calculator::Calculator\" has called ");
    addOperation("+", [](std::vector<long double>& operands) { return operands[0] + operands[1]; },
                               [](std::vector<long double> &operands) { return true; }, 0, 2);
    spdlog::trace("\"Calculator::Calculator\" : Operation + added");
    addOperation("-", [](std::vector<long double>& operands) { return operands[0] - operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 0, 2);
    spdlog::trace("\"Calculator::Calculator\" : Operation - added");
    addOperation("/", [](std::vector<long double>& operands) { return operands[0] / operands[1]; },
                               [](std::vector<long double>& operands) { return operands[1] != 0; }, 1, 2);
    spdlog::trace("\"Calculator::Calculator\" : Operation / added");
    addOperation("*", [](std::vector<long double>& operands) { return operands[0] * operands[1]; },
                               [](std::vector<long double>& operands) { return true; }, 1, 2);
    spdlog::trace("\"Calculator::Calculator\" : Operation * added");
    addOperation("^", [](std::vector<long double>& operands) { return std::pow(operands[0], operands[1]); },
                               [](std::vector<long double>& operands) { return (operands[1] > 0); }, 2, 2);
    spdlog::trace("\"Calculator::Calculator\" : Operation ^ added");
    addOperation("sqrt", [](std::vector<long double>& operands) { return sqrt(operands[0]); },
                               [](std::vector<long double>& operands) { return operands[0] >= 0; }, 3, 1);
    spdlog::trace("\"Calculator::Calculator\" : Operation sqrt added");
    addOperation("sin", [](std::vector<long double>& operands) { return sin(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
    spdlog::trace("\"Calculator::Calculator\" : Operation sin added");
    addOperation("cos", [](std::vector<long double>& operands) { return cos(operands[0]); },
                               [](std::vector<long double>& operands) { return true; }, 3, 1);
    spdlog::trace("\"Calculator::Calculator\" : Operation cos added");
    spdlog::info("Function \"Calculator::Calculator\" has ended ");
}

void Calculator::executeOperation(Stack<Number> &stackForNumbers,
                                  Stack<AtomicExpression *> &stackForBracketsAndOperations) {

    spdlog::info("Function \"Calculator::executeOperation\" has called ");
    auto castedTop = dynamic_cast<Operation *>(stackForBracketsAndOperations.top()); // берем операцию из стека

    int numberOfOperands = castedTop->getNumberOfOperands(); // смотрим в операции сколько ей надо операндов
    std::vector<long double> operands;
    spdlog::trace("\"Calculator::executeOperation\" : vector<long double> operands had been created");
    while (numberOfOperands--) { // пока не возьмем сколько надо операндов
        if (stackForNumbers.empty()) { // если не можем взять из стека операнд, значит выражение было неправильным
            spdlog::error("\"Calculator::executeOperation\" : not enough operands");
            throw std::invalid_argument("Calculator::executeOperation");
        }
        operands.push_back(stackForNumbers.top().getValue());
        spdlog::trace("\"Calculator::executeOperation\" : operand " + std::to_string(stackForNumbers.top().getValue()) + " has pushed into operands");
        spdlog::trace("\"Calculator::executeOperation\" : operand " + std::to_string(stackForNumbers.top().getValue()) + " has poped from stack");
        stackForNumbers.pop(); // удаляем только что взятый операнд
    }


    reverse(operands.begin(), operands.end());  // из-за особенностей польской нотации мы взяли операнды в обратном порядке
                                                        // например 0-1 в польской нотации имеет вид 01-, если бы мы не сделали переворот, то
                                                        // массив операндов был 1 0 и мы бы отнимали от 1 0 а не наоборот

    spdlog::trace("\"Calculator::executeOperation\" : operands had been reversed");
    spdlog::trace("\"Calculator::executeOperation\" : trying to get operation");
    if (!castedTop->checkIsAbleToMakeOperation(operands)) {
        // проверка на возможность вычисления
        spdlog::error("\"Calculator::executeOperation\" : detected incalculable expression");
        throw std::invalid_argument("Calculator::executeOperation");
    }
    spdlog::trace("\"Calculator::executeOperation\" : operation getted");
    stackForNumbers<<(Number(castedTop->makeOperation(operands)));
    spdlog::trace("\"Calculator::executeOperation\" : " + std::to_string(castedTop->makeOperation(operands)) + " was placed into stack");
    stackForBracketsAndOperations.pop(); //  удаляем использованную операцию
    spdlog::trace("\"Calculator::executeOperation\" : operation popped");
    spdlog::info("Function \"Calculator::executeOperation\" has ended ");
}

void Calculator::processNumberCase(Expression &expr, int curPosition, Stack<Number> &stackForNumbers) {

    spdlog::info("Function \"Calculator::processNumberCase\" has called ");

    auto castedTop = dynamic_cast<Number *>(expr[curPosition]);

    if (castedTop) {
        spdlog::trace("\"Calculator::processNumberCase\" : number at position + " + std::to_string(curPosition));
        // встречено число - просто выгружаем его в стек для чисел
        stackForNumbers << (*castedTop);
        spdlog::trace("\"Calculator::processNumberCase\" : " + std::to_string(castedTop->getValue()) + " was pushed into stack");
    }

    spdlog::info("Function \"Calculator::processNumberCase\" has ended ");
}

void Calculator::processBracketCase(Expression &expr, const int curPosition,
                                    Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                    Stack<Number> &stackForNumbers) {

    spdlog::info("Function \"Calculator::processBracketCase\" has called ");
    auto castedTop = dynamic_cast<Bracket *>(expr[curPosition]);
    if (castedTop) {
        // встречена скобка
        char bracketType = castedTop->bracketType();
        if (bracketType == '(') {
            spdlog::trace("\"Calculator::processBracketCase\" : \"(\" at position + " + std::to_string(curPosition));
            // если скобка открывающая - то кладем её в стек и всё
            stackForBracketsAndOperations << (castedTop);

            spdlog::trace("\"Calculator::processBracketCase\" : \"(\" was placed into stack)");
        } else {
            spdlog::trace("\"Calculator::processBracketCase\" : \")\" at position + )");

            auto castedBracket = dynamic_cast<Bracket *>(stackForBracketsAndOperations.top());
            spdlog::trace("\"Calculator::processBracketCase\" : trying to find \")\" ");

            while (!castedBracket) { // идем по стеку пока не встретим открывающую скобку
                // выполняем верхнюю операцию
              //  std::cout<<"SIZE IS "<<stackForBracketsAndOperations.size()<<std::endl;
                spdlog::trace("\"Calculator::processBracketCase\" : operation found ");
                executeOperation(stackForNumbers, stackForBracketsAndOperations);
               // std::cout<<"SIZE IS "<<stackForBracketsAndOperations.size()<<std::endl;
                castedBracket = dynamic_cast<Bracket *>(stackForBracketsAndOperations.top());
            }
            spdlog::trace("\"Calculator::processBracketCase\" : \")\" found");
            stackForBracketsAndOperations.pop(); // удаляем  найденную открывающую скобку
        }
    }
    spdlog::info("Function \"Calculator::processBracketCase\" has ended ");
}

void Calculator::processOperationsCase(Expression &expr, int curPosition,
                                       Stack<AtomicExpression *> &stackForBracketsAndOperations,
                                       Stack<Number> &stackForNumbers) {

    spdlog::info("Function \"Calculator::processOperationsCase\" has called ");
    auto castedTop = dynamic_cast<Operation *>(expr[curPosition]);
    if (castedTop) {
        spdlog::info("\"Calculator::processOperationsCase\" : operation at position" + std::to_string(curPosition));
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
    spdlog::info("Function \"Calculator::processOperationsCase\" has ended ");
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
    if (!isBracketsBalanced(stringExpression) || !isAbleToCalculate(stringExpression)) {
        throw std::invalid_argument("Calculator::processString");
    }
    return calculate(stringExpression);
}
