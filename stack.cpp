//
// Created by radamir on 19.11.24.
//
#include "stack.h"
#include <iostream>
#include <array>
#include <array>
#include <array>
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
    array = newArray;
}

template<typename T>
void Stack<T>::push(T data) {
    if (curSize < curCapacity) {
        array[curSize] = data;
        curSize++;
        return ;
    }
    reallocate();
    push(data);
}

template<typename T>
void Stack<T>::pop() {
    if (curSize ==0) {
        std::cerr<<"Stack is empty"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    curSize--;
}
template<typename T>
bool Stack<T>::empty() const {
    return (curSize == 0);
}

template<typename T>
int Stack<T>::capacity() const {
    return curCapacity;
}

template<typename T>
int Stack<T>::size() const {
    return curSize;
}

template<typename T>
T Stack<T>::top() const {
    if (curSize == 0) {
        std::cerr<<"Stack is empty"<<std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[curSize-1];
}
template<typename T>
Stack<T>::~Stack() {
    delete[] array;
}