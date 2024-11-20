cmake_minimum_required(VERSION 3.29)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp
        stack.h
        calculator.cpp
        calculator.h
        expression.cpp
        expression.h
        AtomicExpression.cpp
        AtomicExpression.h
)
