//
// Created by 付旭炜 on 2019/12/9.
//

#pragma once

#include <thread>
#include <atomic>

class thread_pool {
private:
    std::atomic_flag stop_;
public:
    unsigned const thread_cnt = std::thread::hardware_concurrency();



};

