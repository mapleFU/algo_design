//
// Created by 付旭炜 on 2019/11/9.
//
#include "common_use.h"

using namespace std;

class FooBar {
private:
    int n;

    atomic_bool flag_foo_{true};
public:
    FooBar(int n) {
        this->n = n;
    }

    void foo(function<void()> printFoo) {

        for (int i = 0; i < n; i++) {
            while (!flag_foo_) {
                this_thread::yield();
            }
            // printFoo() outputs "foo". Do not change or remove this line.
            printFoo();
            flag_foo_ = false;
        }
    }

    void bar(function<void()> printBar) {

        for (int i = 0; i < n; i++) {
            while (flag_foo_) {
                this_thread::yield();
            }
            // printBar() outputs "bar". Do not change or remove this line.
            printBar();
            flag_foo_ = true;
        }
    }
};

int main() {
    FooBar fooBar(12);

    auto t1 = std::thread([&]() {
        fooBar.foo([]() {
            cout << "foo ";
        });
    });

    auto t2 = std::thread([&]() {
        fooBar.bar([]() {
            cout << "bar ";
        });
    });


    t1.join();
    t2.join();
}