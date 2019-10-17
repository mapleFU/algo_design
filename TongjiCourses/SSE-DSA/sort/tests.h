//
// Created by 付旭炜 on 2017/11/8.
//

#ifndef SORT_TESTS_H
#define SORT_TESTS_H

#include "sort.hpp"

void build_heap_test() {
    constexpr int size = 100;
    int s[size];
    for (int i = 0; i < size; ++i) {
        s[i] = rand() % 1000;
    }
    build_heap(s, size);
//    PrintAll(begin(s), end(s));
    std::cout << heap_test(s, size);
}

#endif //SORT_TESTS_H
