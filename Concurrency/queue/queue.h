//
// Created by 付旭炜 on 2019/12/9.
//

#pragma once

#include <mutex>
#include <memory>

/**
 * queue is a virtual base class for thread safe queue
 */
template <typename T>
class ThreadSafeQueue {
public:
    virtual void push(T) = 0;
    virtual void wait_and_pop(T&) = 0;
    virtual std::shared_ptr<T> wait_and_pop() = 0;
    virtual bool try_pop(T& value) = 0;
    virtual std::shared_ptr<T> try_pop() = 0;

    virtual bool empty() const = 0;
    virtual size_t size() const  = 0;
};