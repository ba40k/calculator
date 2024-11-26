cmake_minimum_required(VERSION 3.29)
project(my_calculator)

set(CMAKE_CXX_STANDARD 20)

add_executable(calculator main.cpp)
add_library(calculator_lib STATIC AtomicExpression.cpp Calculator.cpp Expression.cpp)

target_link_libraries(calculator calculator_lib)

enable_testing()
add_subdirectory(Google_tests)

