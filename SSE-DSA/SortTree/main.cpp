#include <iostream>
#include "BinaryTree/BaseTree.h"
#include <random>

int main() {
    BaseTree<int> baseTree;
    for (int i = 0; i < 10; ++i) {
        int rd = rand() % 100000;
        baseTree.insert(rd);
    }

    baseTree.travelse();
    return 0;
}