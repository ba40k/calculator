//
// Created by radamir on 19.11.24.
//

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
    int capacity const;
    ~Stack();
};
#endif //STACK_H
