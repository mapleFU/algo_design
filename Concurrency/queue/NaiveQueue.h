//
// Created by 付旭炜 on 2019/12/9.
//

#ifndef CONCURRENCY_NAIVEQUEUE_H
#define CONCURRENCY_NAIVEQUEUE_H

#include "queue.h"
#include <queue>

template <typename T>
class NaiveQueue:  ThreadSafeQueue<T> {
private:
    mutable std::mutex mut;
    std::queue<T> data_queue;
    std::condition_variable data_cond;

public:
    NaiveQueue()
    {}

    void push(T data)
    {
        std::lock_guard<std::mutex> lk(mut);
        data_queue.push(std::move(data));
        data_cond.notify_one();  // 1
    }

    void wait_and_pop(T& value)  // 2
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});
        value=std::move(data_queue.front());
        data_queue.pop();
    }

    std::shared_ptr<T> wait_and_pop()  // 3
    {
        std::unique_lock<std::mutex> lk(mut);
        data_cond.wait(lk,[this]{return !data_queue.empty();});  // 4
        std::shared_ptr<T> res(
                std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }

    bool try_pop(T& value)
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return false;
        value=std::move(data_queue.front());
        data_queue.pop();
        return true;
    }

    std::shared_ptr<T> try_pop()
    {
        std::lock_guard<std::mutex> lk(mut);
        if(data_queue.empty())
            return std::shared_ptr<T>();  // 5
        std::shared_ptr<T> res(
                std::make_shared<T>(std::move(data_queue.front())));
        data_queue.pop();
        return res;
    }

    bool empty() const
    {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.empty();
    }

    size_t size() const {
        std::lock_guard<std::mutex> lk(mut);
        return data_queue.size();
    }
};


#endif //CONCURRENCY_NAIVEQUEUE_H
