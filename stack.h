//
// Created by radamir on 19.11.24.
//
#include <iostream>
#ifndef STACK_H
#define STACK_H
template<typename  T>
class Stack {
private:
    T* array;
    int curSize;
    int curCapacity;
    const int INITIAL_CAPACITY = 16;
    void reallocate();
public:
    Stack();
    void push(T data);
    T top() const;
    bool empty() const;
    void pop();
    int size()const;
    int capacity() const;
    ~Stack();
};
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
#endif //STACK_H
