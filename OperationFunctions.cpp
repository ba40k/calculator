//
// Created by radamir on 20.11.24.
//

#include "OperationFunctions.h"
long double OperationFunctions::sum(long double a, long double b) {
    return a + b;
}
long double OperationFunctions::sub(long double a, long double b) {
    return a - b;
}
long double OperationFunctions::multiply(long double a, long double b) {
    return a * b;
}
long double OperationFunctions::divide(long double a, long double b) {
    return a / b;
}
long double OperationFunctions::power(long double base, long double exponent) {
    return std::pow(base, exponent);
}


