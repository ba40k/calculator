cmake_minimum_required(VERSION 3.29)
project(calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp
        stack.h
        Calculator.cpp
        Calculator.h
        Expression.cpp
        Expression.h
        AtomicExpression.cpp
        AtomicExpression.h)
enable_testing()
add_subdirectory(Google_tests)

