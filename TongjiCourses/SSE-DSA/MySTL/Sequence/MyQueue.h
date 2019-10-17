//
// Created by 付旭炜 on 2017/10/19.
//

#ifndef SEQUENCE_MYQUEUE_H
#define SEQUENCE_MYQUEUE_H

#include "Queue.h"
#include "MyVector.h"

template <typename Type>
struct node {
    Type value;
    node* next;
    explicit node(const Type &_value): value(_value), next(nullptr) {}
};

template <typename Type>
class MyQueue: public Queue<Type> {
public:
    size_type size() override { return _size; }

    MyQueue(): head(nullptr), tail(nullptr), _size(0) {}
    Type pop() override ;
    void push(const Type& value) override {
        node<Type>* newnode = nullptr;
        newnode = new node<Type>(value);
        if (newnode == nullptr) { std::cerr << "Queue was full" << '\n'; }

        if (head == tail && head == nullptr) {
            head = newnode;
            tail = newnode;
        } else {
            newnode->next = head;
            head = newnode;
        }
        ++_size;
    }

    Type& front() override ;

private:
    // head是物理的头部，每次向head**之前**插入
    node<Type>* head;
    node<Type>* tail;
    size_type _size;

};

template <typename Type>
Type MyQueue<Type>::pop() {
    if (head == nullptr) {
        std::cerr << "MyQueue is empty!\n";
//        return Type();
        exit(1);
    }
    auto nexthead = head->next;
    auto ret_value = std::move(head->value);
    delete head;
    head = nexthead;
    if (head == nullptr) {
        tail = nullptr;
    }
    --_size;
    return ret_value;

}

template <typename Type>
Type &MyQueue<Type>::front() {
    return head->value;
}


#endif //SEQUENCE_MYQUEUE_H
