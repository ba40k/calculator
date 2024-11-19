//
// Created by radamir on 19.11.24.
//

#ifndef STACK_H
#define STACK_H
template<typename  T>
class Stack {
private:
    struct Node {
        T data;
        Node* previous;
    };
    int curSize;
    Node head;
public:
    Stack();
    void push(T data);
    T top() const;
    bool empty() const;
    void pop();
    int size()const;


};
#endif //STACK_H
