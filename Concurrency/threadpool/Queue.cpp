//
// Created by 付旭炜 on 2020/1/30.
//

#include "Queue.h"
#include "third_party/concurrentqueue/concurrentqueue.h"
#include <future>
#include <atomic>

/// 作为 packaged_task 的一个 wrapper
class function_wrapper {
    struct impl_base {
        virtual void call() = 0;
        virtual ~impl_base() {}
    };

    std::unique_ptr<impl_base> impl;
    template <typename F> struct impl_type : impl_base {
        F f;
        impl_type(F &&f_) : f(std::move(f_)) {}
        void call() { f(); }
    };

  public:
    template <typename F>
    function_wrapper(F &&f) : impl(new impl_type<F>(std::move(f))) {}

    void operator()() { impl->call(); }

    function_wrapper() = default;

    function_wrapper(function_wrapper &&other) : impl(std::move(other.impl)) {}

    function_wrapper &operator=(function_wrapper &&other) {
        impl = std::move(other.impl);
        return *this;
    }

    function_wrapper(const function_wrapper &) = delete;
    function_wrapper(function_wrapper &) = delete;
    function_wrapper &operator=(const function_wrapper &) = delete;
};

class thread_pool {
    std::atomic_bool done = false;
    moodycamel::ConcurrentQueue<function_wrapper>
        work_queue; // 使用function_wrapper，而非使用std::function

    void worker_thread() {
        while (!done) {
            function_wrapper task;
            if (work_queue.try_dequeue(task)) {
                task();
            } else {
                std::this_thread::yield();
            }
        }
    }

  public:
    template <typename FunctionType>
    std::future<typename std::result_of<FunctionType()>::type> // 1
    submit(FunctionType f) {
        typedef typename std::result_of<FunctionType()>::type result_type; // 2
        // packaged_task 解藕一个 task, 能够 get_future
        std::packaged_task<result_type()> task(std::move(f)); // 3
        std::future<result_type> res(task.get_future());      // 4
        work_queue.enqueue(std::move(task));                  // 5
        return res;                                           // 6
    }
    // 休息一下
};