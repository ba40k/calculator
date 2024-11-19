//
// Created by radamir on 19.11.24.
//
#include "stack.h"

#include <compare>

template<typename T>
Stack<T>::Stack() {
    curCapacity = INITIAL_CAPACITY;
    array = new T[curCapacity];
    curSize =0;
}



template<typename T>
Stack<T>::~Stack() {
    delete[] array;
}

