#include <iostream>
#include "MyArray.h"
#include "MyVector.h"

#include "MyQueue.h"
#include "MyPriorityQueue.h"

struct cmp {
    bool operator ()(const int i, const int j) const {
        return i > j;
    }
};
int main() {
    auto array = MyArray<int>(5);
    array[2] = 1;
    array[1] = 2;
    printf("%d %d\n", array[1], array[2]);

    auto vec = MyVector<int>(13);
    for (int i = 0; i < 13; ++i) {
        vec[i] = i;
    }
    for (int j = 13; j < 16; ++j) {
        vec.push_back(j);
    }
    for (int k = 0; k < 16; ++k) {
        printf("%d ", vec[k]);
    }

    MyQueue<int> q;
    for (int l = 0; l < 16; ++l) {
        q.push(l * 2 + 1);
    }

    std::cout << "\nqueue test\n";
    while (q.size()) {
        std::cout << q.pop() << ' ';
    }
    std::cout.put('\n');

    std::cout << "priority queue test\n";
    MyPriorityQueue<int> pq;
    srand(static_cast<unsigned >(time(nullptr)));
    for (int m = 0; m < 20; ++m) {
        pq.push(rand() % 10);
    }
    while (pq.size()) {
        std::cout << pq.pop() << ' ';
    }
    std::cout << "\npq compare test\n";
    MyPriorityQueue<int, cmp> pq2;
    for (int m = 0; m < 20; ++m) {
        pq2.push(rand() % 10);
    }
    while (pq2.size()) {
        std::cout << pq2.pop() << ' ';
    }
    return 0;
}