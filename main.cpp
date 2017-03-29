#include <iostream>
#include <random>
//#include "BaseBinaryTree.h"
#include "BinarySearchTree.h"
#include "avlTree.h"

using namespace std;

constexpr int TESTCASE = 30;
int main() {
    random_device rd;
    vector<int> data1;

    BinarySearchTree<int> bst1;
    avlTree<int> avlt;

    for (int i = 0; i < TESTCASE; ++i) {
        data1.push_back(rd() % 30);
    }
    puts("TESTDATA:");
    for (int j = 0; j < TESTCASE; ++j) {
        printf("%d ", data1[j]);
    }
//    data1.push_back(1);data1.push_back(2);data1.push_back(3);
    putchar('\n');
    for (int k = 0; k < TESTCASE; ++k) {
//        bst1.Insert(data1[k]);
        avlt.Insert(data1[k]);
//        avlt.InTraverse();
    }
//    bst1.InTraverse();
    avlt.InTraverse();
    putchar('\n');
    for (int j = 0; j < 10; ++j) {
        avlt.DeleteNode(rd() % 30);
    }
    puts("After :");
    avlt.InTraverse();

    return 0;
}