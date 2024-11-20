//
// Created by radamir on 19.11.24.
//
#ifndef STACK_H
#define STACK_H
#include <iostream>
template<typename  T>
class Stack {
private:
    T* array;
    int curSize;
    int curCapacity;
    const int INITIAL_CAPACITY = 16;
    void push(T data);
    void pop();
    void reallocate();
public:
    Stack();
    void operator<<(T data);
    void operator>>(int count);
    Stack<T>& operator=(const Stack<T>& other);
    bool operator==(const Stack &other) const;
    bool operator!=(const Stack &other) const;
    bool operator<(const Stack &other) const;
    bool operator>(const Stack &other) const;
    T& operator[](int index);
    T top() const;
    [[nodiscard]]bool empty() const;
    [[nodiscard]]int size()const;
    [[nodiscard]]int capacity() const;
    ~Stack();
};
template<typename T>
void Stack<T>::operator>>(int count) {
    if (count > size()) {
        std::cerr << "Stack size is too small" << std::endl;
        exit(EXIT_FAILURE);
    }
    while (count--) {
        pop();
    }
}

template<typename T>
T& Stack<T>::operator[](int index) {
    if (index >= curSize) {
        std::cerr << "Stack index out of bounds" << std::endl;
        std::exit(EXIT_FAILURE);
    }
    return array[index];
}

template<typename T>
void Stack<T>::operator<<(T data) {
    push(data);
}

template<typename T>
bool Stack<T>::operator==(const Stack &other) const {
    if (other.size() != curSize) {
        return false;
    }

    for (int i = 0; i < curSize; i++) {
        if (array[i] != other.array[i]) {
            return false;
        }
    }

    return true;
}

template<typename T>
bool Stack<T>::operator!=(const Stack &other) const {
    return !(*this == other);
}

template<typename T>
Stack<T> &Stack<T>::operator=(const Stack<T> &other) {
        if (this == &other) {
            return *this;
        }
        int* newArray = new int[other.curCapacity];
        for (int i = 0; i < other.curSize; i++) {
            newArray[i] = other.array[i];
        }
        curSize = other.curSize;
        curCapacity = other.curCapacity;
        delete[] array;
        array = newArray;
        return *this;

}

template<typename T>
bool Stack<T>::operator<(const Stack &other) const {
    for (int i = 0;i<curSize;i++) {
        if (i>=other.curSize) {
            return false;
        }
        if (array[i] < other.array[i]) {
            return true;
        }
        if (array[i] > other.array[i]) {
            return false;
        }
    }
    return false;
}

template<typename T>
bool Stack<T>::operator>(const Stack &other) const {
    for (int i = 0;i<curSize;i++) {
        if (i>=other.curSize) {
            return true;
        }
        if (array[i] < other.array[i]) {
            return false;
        }
        if (array[i] > other.array[i]) {
            return true;
        }
    }
    return false;
}


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
