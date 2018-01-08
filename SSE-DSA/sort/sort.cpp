#ifndef _SORT_SORT_HPP_
#define _SORT_SORT_HPP_

#include <iostream>
#include <algorithm>
#include <cstdio>
template <typename iterT>
void PrintAll(iterT beg, iterT end) {
    while(beg != end) {
        std::cout << *beg << ' ';
        ++beg;
    }
    putchar('\n');
}

template <typename iterT>// 1 7 3 2->1 3 7 2->
void InsertionSort(iterT beg, iterT end) {
    for (auto it1 = beg + 1; it1 != end; ++it1) {
        decltype(it1) it2,ittmp(it1);
        auto val = *it1;
        for (it2 = beg; it2 != it1; ++it2) {
            if (*it2 > val) {
                std::swap(*it2, *ittmp--);
                continue;
            }
            else
                break;
        }
    }
}

#endif
