#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <cstdio>
#include <memory>
#include <algorithm>
#define NDEBUG
#include "sort.hpp"

using namespace std;


const int size = 100000;
const int tests = 9;


int main(){

    random_device rd;
    vector<int> vecs;
    vector<vector<int>> testVec;
    for (int i = 0; i < size; ++i) {
        vecs.push_back(rd() % 100000);
    }
    for (int j = 0; j < tests; ++j) {
        testVec.push_back(vecs);
    }

    printf("MergeSort: ");
    sortTest(testVec[4].begin(), testVec[4].end(), MergeSort );

//    printf("InsertionSort: ");
//    sortTest(testVec[0].begin(), testVec[0].end(), InsertionSort );

//    printf("SelectionSort: ");
//    sortTest(testVec[1].begin(), testVec[1].end(), SelectionSort );

//    printf("ShellSort: ");
//    sortTest(testVec[5].begin(), testVec[5].end(), ShellSort );

    auto timeb = clock();
    RadixSort(testVec[2], 10);
    auto timee = clock();
    printf("RadixSort: ");
    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    printf("QuickSort: ");
    sortTest(testVec[6].begin(), testVec[6].end(), QuickSort );

//    printf("Another MergeSort: ");
//    sortTest(testVec[7].begin(), testVec[7].end(), MergeSort_with_insert);

    printf("Another QuickSort: ");
    sortTest(testVec[8].begin(), testVec[8].end(), QuickSort_three );

    timeb = clock();
    sort(testVec[3].begin(), testVec[3].end());
    timee = clock();
    printf("Sort: ");
    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    return 0;
}