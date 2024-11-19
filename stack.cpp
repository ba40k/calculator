//
// Created by radamir on 19.11.24.
//
#include "stack.h"

template<typename T>
Stack<T>::Stack() {
    head = new Node();
    head->data=0;
    head->previous=nullptr;
    curSize=0;
}

template<typename T>
void Stack<T>::push(T data) {
    if(size()==0) {
        head->data=data;
        curSize=1;
        return;
    }
    Node* newNodePtr = new Node;
    newNodePtr->data = head->data;
    newNodePtr->previous = head->previous;

    head->data = data;
    head->previous = newNodePtr;

    curSize++;
}

template<typename T>
void Stack<T>::pop () {
    if (size()==0) {
        throw "Stack is empty";
    }
    if (size()==1) {
        head->data = 0;
        head->previous = nullptr;
        curSize--;
        return;
    }
    Node* toDelete = head->previous;
    T oldData = head->previous->data;
    head->previous = head->previous->previous;
    head->data = oldData;
    delete toDelete;
}
template<typename T>
T Stack<T>::top() const {
    return head->data;
}
template<typename T>
int Stack<T>::size() const {
    return curSize;
}

template<typename T>
bool Stack<T>::empty() const {
    return (curSize==0);
}
template<typename T>
Stack<T>::~Stack() {
    while(size()!=0) {
        pop();
    }
}




