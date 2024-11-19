//
// Created by radamir on 19.11.24.
//
#include "stack.h"

template<typename T>
Stack<T>::Stack() {
    head.data=0;
    head.previous=nullptr;
    curSize=0;
}

template<typename T>
void Stack<T>::push(T data) {
    node* newNodePtr = new node;
    newNodePtr->data = head.data;
    newNodePtr->previous = head.previous;

    head.data = data;
    head.previous = newNodePtr;

    curSize++;
}


