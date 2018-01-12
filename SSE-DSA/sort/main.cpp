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

using namespace std;

void test_all(const vector<int>& test_vec) {
    vector<vector<int>> testVec(12);
    for (int i = 0; i < testVec.size(); ++i) {
        testVec[i] = test_vec;
    }
    int size = test_vec.size();
    clock_t timee, timeb;

    if (size <= 50000) {
        printf("BubbleSort: ");
        sortTest(testVec[2].begin(), testVec[2].end(), BubbleSort);

        // pass
        printf("InsertionSort: ");
        sortTest(testVec[0].begin(), testVec[0].end(), InsertionSort );

        printf("InsertionSortWithBisect: ");
        sortTest(testVec[1].begin(), testVec[1].end(), InsertionSortWithBisect);

        printf("SelectionSort: ");
        sortTest(testVec[5].begin(), testVec[5].end(), SelectionSort);
    }

    // pass
    printf("MergeSort: ");
    sortTest(testVec[4].begin(), testVec[4].end(), MergeSort );
    //pass
    // TODO: fix shell prob

    printf("ShellSort: ");
    sortTest(testVec[3].begin(), testVec[3].end(), ShellSort );

    // pass
//    auto timeb = clock();
    timeb = clock();
    RadixSort2(&testVec[6][0], 20, size);
    timee = clock();
    printf("RadixSort: ");
    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    printf("QuickSort: ");
    sortTest(testVec[8].begin(), testVec[8].end(), QuickSort );

    printf("Another MergeSort: ");
    sortTest(testVec[9].begin(), testVec[9].end(), MergeSort_with_insert);

    printf("Another QuickSort: ");
    sortTest(testVec[10].begin(), testVec[10].end(), QuickSort_three );

    // pass..
    timeb = clock();
    sort(testVec[7].begin(), testVec[7].end());
    timee = clock();
    printf("Sort: ");
    std::cout<<"Used time:"<<timee - timeb<<std::endl;

    //pass
    printf("HeapSort: ");
    timeb = clock();
    HeapSort(&testVec[11][0], size);
    timee = clock();
    std::cout<<"Used time:"<<timee - timeb<<std::endl;

}

int main(){
    int size = -1;
    while (size < 0) {
        std::cout << "请选择生成的数字数目: ";
        std::cin >> size;
    }
    int upper_bound = -1;
    while (upper_bound < 0) {
        std::cout << "请选择你的数字上限";
        std::cin >> upper_bound;
    }


    random_device rd;
    vector<int> vecs;
    vector<vector<int>> testVec;

    //生成测试数据
    for (int i = 0; i < size; ++i) {
        int tmp = rd() % upper_bound;
        vecs.push_back(tmp);
    }

    std::cout << "**\t\t排序算法比较\t\t**\n"
            "**\t\t1.冒泡排序\t\t**\n"
            "**\t\t2.选择排序\t\t**\n"
            "**\t\t3.直接插入排序\t\t**\n"
              "**\t\t4.希尔排序\t\t**\n"
              "**\t\t5.快速排序\t\t**\n"
              "**\t\t6.堆排序\t\t**\n"
              "**\t\t7.归并排序\t\t**\n"
              "**\t\t8.基数排序\t\t**\n"
              "**\t\t9.三向切分快速排序排序\t\t**\n"
            "**\t\t10.插入排序优化的归并排序\t\t**\n"
              "**\t\t11.全部测试\t\t**\n"
            "**\t\t12.二分查找优化的插入排序\t\t**\n"
            "**\t\t13.退出程序\t\t**\n";

    int select;
    clock_t timeb, timee;
    while (cin >> select && select != 13) {
        vector<int> cp_vec(vecs);
        int cmp;
        switch (select) {
            case 1:
                if (size > 50000) {
                    std::cout << "数据规模大于50000，不便于用本排序\n";
                    break;
                }
                printf("BubbleSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), BubbleSort);
                break;
            case 2:
                if (size > 50000) {
                    std::cout << "数据规模大于50000，不便于用本排序\n";
                    break;
                }
                printf("SelectionSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), SelectionSort);
                break;
            case 3:
                if (size > 50000) {
                    std::cout << "数据规模大于50000，不便于用本排序\n";
                    break;
                }
                printf("InsertionSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), InsertionSort );
                break;
            case 4:
                printf("ShellSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), ShellSort );
                break;
            case 5:
                printf("QuickSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), QuickSort );
                break;
            case 6:
                printf("HeapSort: ");
                timeb = clock();
                cmp = HeapSort(&cp_vec[0], size);
                timee = clock();
                std::cout<<"Used time:"<<timee - timeb<< "and swap " << cmp << " times"<<std::endl;
                break;
            case 7:
                printf("MergeSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), MergeSort );
                break;
            case 8:

                printf("RadixSort: ");
                timeb = clock();
                RadixSort2(&cp_vec[0], 20, size);
                timee = clock();
                std::cout<<"Used time:"<<timee - timeb << '\n';

                break;
            case 9:
                printf("Another QuickSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), QuickSort_three );
                break;
            case 10:
                printf("Another MergeSort: ");
                sortTest(cp_vec.begin(), cp_vec.end(), MergeSort_with_insert);
                break;
            case 11:

                test_all(cp_vec);
                break;
            case 12:
                if (size > 50000) {
                    std::cout << "数据规模大于50000，不便于用本排序\n";
                    break;
                }
                printf("InsertionSortWithBisect: ");
                sortTest(testVec[1].begin(), testVec[1].end(), InsertionSortWithBisect);
                break;
            default:
                std::cout << "请输入1-12的操作码\n";
        }
    }

    return 0;
}