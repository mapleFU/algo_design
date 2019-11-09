//
// Created by 付旭炜 on 2019/11/10.
//

#include "common_use.h"
#include <cmath>

using namespace std;

class ZeroEvenOdd {
private:
    const int n_;
    int current_ { 1 };

    // 0 means first 0
    // 1 means even
    // 2 means 0
    // 3 means odd
    atomic_int8_t fsm_ {0};
    
    void next_fsm() {
        fsm_ += 1;
    }

public:
    ZeroEvenOdd(int n): n_(n) {
    }

    // zero -> even -> zero -> odd
    //

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for (int i = 0; i < n_; ++i) {
            while (fsm_ % 2) this_thread::yield();
            printNumber(0);
            ++fsm_;
        }
    }

    void even(function<void(int)> printNumber) {
        int upper = n_ / 2;
        if (n_ % 2) upper += 1;
        for (int i = 0; i < upper; ++i) {
            while (fsm_ % 4 != 1) this_thread::yield();
            printNumber(current_++);
            ++fsm_;
        }

    }

    void odd(function<void(int)> printNumber) {
//        std::cout << endl <<  upper << endl;/
        for (int i = 0; i < n_ / 2; ++i) {
            while (fsm_ % 4 != 3) this_thread::yield();
            printNumber(current_++);
            ++fsm_;
        }
    }
};

int main() {
    ZeroEvenOdd fooBar(2);

    auto printNumber = [](int v) {
        cout << v << ' ' << flush;
    };

    auto t1 = std::thread([&]() {
        fooBar.zero(printNumber);
    });

    auto t2 = std::thread([&]() {
        fooBar.even(printNumber);
    });

    auto t3 = std::thread([&]() {
        fooBar.odd(printNumber);
    });


    t1.join();
    t2.join();
    t3.join();
}