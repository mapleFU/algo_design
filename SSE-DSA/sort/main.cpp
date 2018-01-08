#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdio>
#include <memory>
#include <algorithm>
#define NDEBUG
#include "sort.hpp"
#include "tests.h"

/*
 * Bug in radix sort
 */
using namespace std;


const int size = 9;
const int tests = 9;


int main(){

    random_device rd;
    vector<int> vecs;
    vector<vector<int>> testVec;
//    int test_arr[size];
    for (int i = 0; i < size; ++i) {
        int tmp = rd() % 100000;
        vecs.push_back(tmp);
//        test_arr[i] = tmp;
    }
    for (int j = 0; j < tests; ++j) {
        testVec.push_back(vecs);
    }



    // pass
//    printf("MergeSort: ");
//    sortTest(testVec[4].begin(), testVec[4].end(), MergeSort );
//

//    // pass
    printf("InsertionSort: ");
    sortTest(testVec[0].begin(), testVec[0].end(), InsertionSort );

    printf("InsertionSortWithBisect: ");
    sortTest(testVec[1].begin(), testVec[1].end(), InsertionSortWithBisect);

    printf("BubbleSort: ");
    sortTest(testVec[2].begin(), testVec[2].end(), BubbleSort);

    printf("SelectionSort: ");
    sortTest(testVec[3].begin(), testVec[3].end(), SelectionSort);
    //pass
    // TODO: fix shell prob

    printf("ShellSort: ");
    sortTest(testVec[4].begin(), testVec[4].end(), ShellSort );




    // pass
//    auto timeb = clock();
//    RadixSort2(&testVec[6][0], 10, size);
//    auto timee = clock();
//    printf("RadixSort: ");
//    std::cout<<"Used time:"<<timee - timeb<<std::endl;
//

//    printf("QuickSort: ");
//    sortTest(testVec[8].begin(), testVec[8].end(), QuickSort );

//    printf("Another MergeSort: ");
//    sortTest(testVec[4].begin(), testVec[4].end(), MergeSort_with_insert);
//
//    printf("Another QuickSort: ");
//    sortTest(testVec[3].begin(), testVec[3].end(), QuickSort_three );
//

    // pass..
//    timeb = clock();
//    sort(testVec[7].begin(), testVec[7].end());
//    timee = clock();
//    printf("Sort: ");
//    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    //pass
//    printf("Heap Sort: ");
//    timeb = clock();
//    HeapSort(&testVec[5][0], size);
//    timee = clock();
//    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    return 0;
}