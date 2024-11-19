//
// Created by radamir on 19.11.24.
//
#include "stack.h"

#include <array>
#include <array>
#include <array>
#include <compare>

template<typename T>
Stack<T>::Stack() {
    curCapacity = INITIAL_CAPACITY;
    array = new T[curCapacity];
    curSize =0;
}

template<typename T>
void Stack<T>::reallocate() {
    curCapacity*=2;
    T* newArray = new T[curCapacity];
    for (int i =0;i<curSize;i++) {
        newArray[i] = array[i];
    }
    delete[] array;
}

template<typename T>
void Stack<T>::push(T data) {
    if (curSize < capacity) {
        array[curSize] = data;
        curSize++;
        return ;
    }
    reallocate();
    push(data);
}



template<typename T>
Stack<T>::~Stack() {
    delete[] array;
}

