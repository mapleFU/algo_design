//
// Created by 付旭炜 on 2017/10/19.
//

#ifndef SEQUENCE_QUEUE_H
#define SEQUENCE_QUEUE_H

#include "Sequence.h"


template <typename Type>
class Queue {
public:
    virtual Type pop() = 0;
    virtual void push(const Type& value)= 0;
    virtual Type& front()= 0;
    virtual size_type size() = 0;
};

#endif //SEQUENCE_QUEUE_H
