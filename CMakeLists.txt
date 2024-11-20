cmake_minimum_required(VERSION 3.29)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp
        stack.h
        calculator.cpp
        calculator.h
        expression.cpp
        expression.h
        cmake-build-debug/AtomicExpression.cpp
        cmake-build-debug/AtomicExpression.h
        OperationFunctions.cpp
        OperationFunctions.h
)
