//
// Created by 付旭炜 on 2017/2/20.
//

#ifndef SORT_SORT_H
#define SORT_SORT_H

#include <thread>
#include <iostream>
#include <vector>
#include <memory>
#include <ctime>
#include <cmath>
#include <vector>
#include <type_traits>
#include <array>

template <typename iterT>
void PrintAll(iterT beg, iterT end){
    while(beg != end) {
        std::cout << *beg << ' ';
        ++beg;
    }
    putchar('\n');
}

template <typename iterT>
void InsertionSort(iterT beg, iterT end) {
    if (end - beg <= 0)
        return;
    for (auto it1 = beg + 1; it1 != end; ++it1) {
        auto it2 = it1 - 1,ittmp(it1);
        auto val = *it1;
        for (; it2 != beg - 1; --it2) {
            if (*it2 > val) {
                std::swap(*it2, *ittmp--);
                continue;
            }
            else{
                break;
            }
        }
    }
}

inline int fun1(int val){
    return static_cast<int>(9 * pow(4,val) - 9 * pow(2, val) + 1);
}
inline int fun2(int val){
    return static_cast<int>(pow(4,val) - 3 * pow(2, val) + 1);
}
inline int getVal(int &pos, int (*fun)(int)){
    int val = fun1(pos);
    while (val <= 0){
        pos++;
        val = fun1(pos);
    }
    return val;
}

int arr(){
    using namespace std;
    static int pos1(0),pos2(0);
    int val1, val2;
    val1 = getVal(pos1, fun1);
    val2 = getVal(pos2, fun2);
    int ret;
    if(val1 > val2) {
        ret = val2;
        pos2++;
    }
    else{
        ret = val1;
        pos1++;
    }
    return ret;
}
std::shared_ptr<std::vector<int> >  Increments(const int datasize){    //.h中,需要std::
    using namespace std;
    shared_ptr<vector<int> > pv = make_shared<vector<int> >();  //必须指向区域
    for (int i = 1; (*pv).empty() || (*pv).back() < datasize; ++i) {
        (*pv).push_back(arr());
    }
    (*pv).pop_back();
    return pv;
}
template <typename iterT>
void ShellSort(iterT beg, iterT end){   //sedgewick增量序列
    const int datasize = end - beg;
    auto pVec = Increments(datasize);
    for (int i = (*pVec).size() - 1; i >= 0; --i) {
        for (auto j = (*pVec)[i]; j < datasize; ++j) {  //用unsigned／auto作<=0有风险!!!
            auto val = *(beg + j);      //val为元素值
            auto it = beg + j;
            for (int k = j - (*pVec)[i]; k >= 0; k -= (*pVec)[i]) {
                if(*(beg + k) > val)
                {
                    std::swap(*(beg + k), *it);
                    it -= (*pVec)[i];
                }
                else
                    break;
            }
        }
    }
}



template <typename iterT>
void SelectionSort(iterT beg, iterT end){
    for (auto it1 = beg; it1 != end; it1++) {
        for (auto it2 = it1 + 1; it2 != end; ++it2) {
            if(*it2 < *it1)
                std::swap(*it1, *it2);
        }
    }
}

template <typename iterT>
void Merge(iterT beg1, iterT end1, iterT beg2, iterT end2) {
    using namespace std;
    typedef typename remove_reference<decltype(*beg1)>::type T;
    int val1 = end1 - beg1, val2 = end2 - beg2;     //TODO
    int pos = 0;
    iterT it1 = beg1, it2 = beg2;
//    unique_ptr<T[]> TmpContainer(new T(end2 - beg1));
    shared_ptr<T> TmpContainer(new T[end2 - beg1], [](T *p) {delete[] p;});
    while (val1 || val2) {
        if ((!val2 || *it1 >= *it2) && val1) {  //不能==
            val1--;
//            TmpContainer[pos++] = *it1++;
            *(TmpContainer.get() + pos++) = *it1++;
        }
        if ((!val1 || *it2 >= *it1) && val2) {
            val2--;
            *(TmpContainer.get() + pos++) = *it2++;
//            TmpContainer[pos++] = *it2++;
        }
    }
    iterT it = beg1;
    for (int i = 0; i < end2 - beg1; ++i) {
        *it++ = *(TmpContainer.get() + i);
    }
    TmpContainer.reset();
};
template <typename iterT>
void MergeSort(iterT beg, iterT end){
    if(end - beg <= 0)
        return;
    else if(end - beg == 1)
    {
        if(*end > *beg)
            std::swap(*end, *beg);
        return;
    }
    auto mid = (end - beg) / 2 + beg;
    MergeSort(beg, mid);
    MergeSort(mid, end);    //两段开始地点应该相同
    Merge(beg, mid, mid, end);
}

template <typename iterT, typename T>
void Merge_with_insert(iterT beg1, iterT end1, iterT beg2, iterT end2, std::shared_ptr<T> aux) {
    int beg2p = beg2 - beg1;
    for (int i = 0; i < end2 - beg1; ++i) {
        *(aux.get() + i) = *(beg1 + i);
    }
    int i1 = 0, i2 = beg2p;

    for (int j = 0; j < end2 - beg1; ++j) {
        if (i1 == end1 - beg1) *(beg1 + j) = *(aux.get() + i2++);
        else if (i2 == end2 - beg1) *(beg1 + j) = *(aux.get() + i1++);
        else if (*(aux.get() + i1) > *(aux.get() + i2)) *(beg1 + j) = *(aux.get() + i2++);
        else *(beg1 + j) = *(aux.get() + i1++);
    }
}
template <typename iterT>
void MergeSort_with_insert(iterT beg, iterT end) {
    typedef typename std::remove_reference<decltype(*beg)>::type T;
    static std::shared_ptr<T> aux(new T(end - beg), [](T *ptr){delete [] ptr;});
    if (end - beg <= 15) {
        InsertionSort(beg, end);        //小于15的用InsertionSort
        return;
    }
    auto mid = (end - beg) / 2 + beg;
    MergeSort_with_insert(beg, mid);
    MergeSort_with_insert(mid, end);
    Merge_with_insert(beg, mid, mid, end, aux);
}

template <typename iterT>
void HeapSort(iterT beg, iterT end){

}

template <typename iterT>
static inline void _division(iterT beg, iterT mid, iterT end) {
    if (*beg > *mid) std::iter_swap(beg, mid);
    if (*beg > *end) std::iter_swap(beg, end);
    if (*mid > *end) std::iter_swap(mid, end);
    std::iter_swap(mid, end - 1);
}

template <typename iterT>
void QuickSort(iterT beg, iterT end){
    if (end - beg <= 15) {
        InsertionSort(beg, end);
        return;
    }
    iterT left = beg, right = end - 1;
    iterT mid = beg + (end - beg) / 2;
    _division(left, mid, right);        // 三数分割
    right--;
    auto pivot = *right;                // 枢纽元在end左侧
    while (left != right) {
        while (left != right && *left <= pivot)
             left++;
        std::swap(*left, *right);
        while (left != right && *right >= pivot)
            right--;
        std::iter_swap(left, right);
        if (left == right)
            break;
    }
    QuickSort(beg, left);
    QuickSort(left + 1, end);
}

template <typename iterT>
extern void sortTest(iterT beg, iterT end, void(*sort)(iterT, iterT)) {
    clock_t timeb,timee;
    timeb = clock();
    sort(beg,end);
    timee = clock();
    std::cout<<"Used time:"<<timee - timeb<<std::endl;
}

template <typename iterT, typename T>
void RadixSort(iterT beg, iterT end, int base = 10) {
    int times;      //需要的趟数
//    decltype(*beg) Max = *beg;
    T Max = *beg;
    for (auto it = beg; it != end; it++)
        if(Max < *it)
            Max = *it;
    auto test = Max;
    while(test){
        test /= base;
        times++;        //求出需要的最大次数
    }
    std::vector<std::vector<T> > radix(base);
    std::vector<T> output(beg, end);        //复制原iter
    while (times--){
        for (auto it = beg; it != end; it++){
            auto pos = *it / base;
            radix[pos].push_back(*it);
        }
    }

}

void RadixSort(std::vector<int> &vec, int base){
    int max = 0, times = 0, val = 1;
    int runtime_base = 1;
    std::vector<int> backet(base, 0);
    std::vector<int> aux(vec.size());           //  tmp vector
    for (int i = 0; i < vec.size(); ++i) {
        if (vec[i] > max)   max = vec[i];
    }
    while (max) {
        // count
        for (int i = 0; i < vec.size(); ++i) {
            ++backet[(vec[i]/runtime_base) % base + 1];
        }
        // find the correct position
        for (int j = 2; j < base; ++j) {
            backet[j] += backet[j - 1];
        }
        for (int k = 0; k < vec.size(); ++k) {
            aux[backet[(vec[k]/runtime_base) % base]++] = vec[k];
        }
        for (int l = 0; l < vec.size(); ++l) {
            vec[l] = std::move(aux[l]);
            backet[l] = 0;
        }
        max /= base;
        runtime_base *= base;
    }
}

template <typename iterT>
void QuickSort_three(iterT beg, iterT end) {
    if (end - beg <= 15) {
        InsertionSort(beg, end);
        return;
    }
    iterT left = beg, right = end - 1;
    iterT mid = beg + (end - beg) / 2;
    _division(left, mid, right);        // 三数分割
    iterT lt = left + 1, rt = end - 1;
    auto pivot = *(rt - 1);
    while (left < rt) {
        if (*left > pivot) {
            std::iter_swap(left, rt--);
        } else if (*left == pivot) {
            ++left;
        } else if (*left < pivot) {
            ++left, ++lt;
        }
    }
    QuickSort_three(beg, lt);
    QuickSort_three(rt, end);
}

template <typename iterT>
void QuickSort_three_thread(iterT beg, iterT end) {
    static int time = 0;
    ++time;
    if (end - beg <= 15) {
        InsertionSort(beg, end);
        return;
    }
    iterT left = beg, right = end - 1;
    iterT mid = beg + (end - beg) / 2;
    _division(left, mid, right);        // 三数分割
    iterT lt = left + 1, rt = end - 1;
    auto pivot = *(rt - 1);
    while (left < rt) {
        if (*left > pivot) {
            std::iter_swap(left, rt--);
        } else if (*left == pivot) {
            ++left;
        } else if (*left < pivot) {
            ++left, ++lt;
        }
    }
    if (time == 1) {
        std::thread t1(QuickSort_three_thread<iterT>, beg, lt);
        std::thread t2(QuickSort_three_thread<iterT>, rt, end);
        t1.join();t2.join();
        printf("\ntwo thread\n");
        time = 0;
    }
    else {
        QuickSort_three(beg, lt);
        QuickSort_three(rt, end);
    }
}
#endif //SORT_SORT_H
