//
// Created by 付旭炜 on 2019/11/9.
//
// Some methods:
// 1. Using promise: https://leetcode.com/problems/print-in-order/discuss/333513/C%2B%2B-Using-std%3A%3Apromise
// 2. Using two mutex: https://leetcode.com/problems/print-in-order/discuss/332979/C%2B%2B-2-mutex

#include <functional>
#include <mutex>
#include <atomic>
#include <thread>
#include <iostream>

using namespace std;

void printFirst() {
    cout << "first " << endl;
}

void printSecond() {
    cout << "second " << endl;
}

void printThird() {
    cout << "third " << endl;
}

class Foo {
public:
    // represent if the first and second is done.
    atomic<bool> flag1_ {false}, flag2_ { false };

    Foo() {

    }

    void first(function<void()> printFirst) {

        // printFirst() outputs "first". Do not change or remove this line.
        printFirst();

        flag1_ = true;
    }

    void second(function<void()> printSecond) {
        while (!flag1_) {
            std::this_thread::yield();
        }
        // printSecond() outputs "second". Do not change or remove this line.
        printSecond();

        flag2_ = true;
    }

    void third(function<void()> printThird) {
        while (!flag2_) {
            std::this_thread::yield();
        }
        // printThird() outputs "third". Do not change or remove this line.
        printThird();
    }
};

int main() {
    Foo f;
    auto t1 = std::thread([&]() {
        f.first(printFirst);
    });

    auto t2 = std::thread([&]() {
        f.third(printThird);
    });

    auto t3 = std::thread([&]() {
        f.second(printSecond);
    });

    t1.join(); t2.join(); t3.join();
}