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
#include <functional>
#include <stack>
/*
 * 根据类型生成swap闭包
 * 自带计数器, 每个函数调用这个SWAP
 */
template <typename Type>
std::function<int(Type&, Type&)> swaper() {

    auto lam = [](Type& val1, Type& val2)-> int {
        static int cnt(0);
        Type tmp = std::move(val1);
        val1 = std::move(val2);
        val2 = std::move(tmp);
        return ++cnt;
    };
    return lam;
}



template <typename iterT>
void PrintAll(iterT beg, iterT end){
    while(beg != end) {
        std::cout << *beg << ' ';
        ++beg;
    }
    putchar('\n');
}

/*
 * WARNING:it should be RandomAccess
 */
template <typename iterT, typename T>
inline iterT bisect(iterT beg, iterT end, const T& value) {
    auto left = beg, right = end;
    //[1, 2, 3, 4, 5] 2.5, end - beg == 5
    iterT mid = (end - beg) / 2 + beg;
    while (right - left > 0) {
        if (*mid < value)
            left = mid + 1;
        else
            right = mid;
        mid = (right - left) / 2 + left;
    }
    return left;
}

/*
 * WARNING:it should be RandomAccess
 */
template <typename iterT>
int InsertionSortWithBisect(iterT beg, iterT end) {
    int cnt(0);
    if (end - beg <= 0)
        return 0;
    for (auto iter1 = beg + 1; iter1 != end; ++iter1) {
        // 在允许范围内最后一个交换的数 [1, 2, 3, 4, 5] 3.5 => 4; 6->END;4.5->5;0.5 ->1
        auto iter_end = bisect(beg, iter1, *iter1);
        if (iter_end == iter1) continue;
        auto cur_iter = iter1;
        while (iter_end != cur_iter) {
            std::swap(*cur_iter, *(cur_iter-1));
            ++cnt;
            --cur_iter;
        }
        std::swap(*cur_iter, *iter_end);
        ++cnt;
    }
    return cnt;
}

template <typename iterT>
int BubbleSort(iterT beg, iterT end) {
    int ret(0);
    int size = end - beg;
    for (int i = size; i > 0; --i) {
        for (int j = 1; j < i; ++j) {
            if (*(beg + j) < *(beg + j - 1)) {
                std::iter_swap(beg + j, beg + j - 1);
                ++ret;
            }
        }
    }
    return ret;
}


template <typename iterT>
int InsertionSort(iterT beg, iterT end) {
    int swap_times(0);
    if (end - beg <= 0)
        return 0;
    for (auto it1 = beg + 1; it1 != end; ++it1) {
        auto it2 = it1 - 1,ittmp(it1);
        auto val = *it1;
        for (; it2 != beg - 1; --it2) {
            if (*it2 > val) {
                std::swap(*it2, *ittmp--);
                ++swap_times;
                continue;
            }
            else{
                break;
            }
        }
    }
    return swap_times;
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
int ShellSort(iterT beg, iterT end){   //sedgewick增量序列
    int swap_times = 0;
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
                    ++swap_times;
                }
                else
                    break;
            }
        }
    }
    return swap_times;
}



template <typename iterT>
int SelectionSort(iterT beg, iterT end){
    int swap_times(0);
    for (auto it1 = beg; it1 != end; it1++) {
        for (auto it2 = it1 + 1; it2 != end; ++it2) {
            if(*it2 < *it1) {
                std::swap(*it1, *it2);
                ++swap_times;
            }

        }
    }
    return swap_times;
}

template <typename iterT>
int Merge(iterT beg1, iterT end1, iterT beg2, iterT end2) {
    using namespace std;
    int cmp_times(0);       //比较的次数
    typedef typename remove_reference<decltype(*beg1)>::type T;
    int val1 = end1 - beg1, val2 = end2 - beg2;     //TODO
    int pos = 0;
    iterT it1 = beg1, it2 = beg2;
//    unique_ptr<T[]> TmpContainer(new T(end2 - beg1));
    shared_ptr<T> TmpContainer(new T[end2 - beg1], [](T *p) {delete[] p;});
    while (val1 || val2) {
        ++cmp_times;
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
    return cmp_times;
};

template <typename iterT>
int MergeSort(iterT beg, iterT end){
    int cmp_times(0);
    if(end - beg <= 0)
        return 0;
    else if(end - beg == 1)
    {
        if(*end > *beg) {
            ++cmp_times;
            std::swap(*end, *beg);
        }

        return cmp_times;
    }
    auto mid = (end - beg) / 2 + beg;
    cmp_times += MergeSort(beg, mid);
    cmp_times += MergeSort(mid, end);    //两段开始地点应该相同
    cmp_times += Merge(beg, mid, mid, end);
    return cmp_times;
}


//template <typename iterT, typename T>
//int Merge_with_insert(iterT beg1, iterT end1, iterT beg2, iterT end2, std::shared_ptr<T> aux) {
//    int beg2p = beg2 - beg1;
//    int cmp_times = 0;
//    for (int i = 0; i < end2 - beg1; ++i) {
//        *(aux.get() + i) = *(beg1 + i);
//    }
//    int i1 = 0, i2 = beg2p;
//
//    for (int j = 0; j < end2 - beg1; ++j) {
//        if (i1 == end1 - beg1) *(beg1 + j) = *(aux.get() + i2++);
//        else if (i2 == end2 - beg1) *(beg1 + j) = *(aux.get() + i1++);
//        else {
//            ++cmp_times;
//            if (*(aux.get() + i1) > *(aux.get() + i2)) *(beg1 + j) = *(aux.get() + i2++);
//            else *(beg1 + j) = *(aux.get() + i1++);
//
//        }
//    }
//
//    return cmp_times;
//}

template <typename iterT>
int MergeSort_with_insert(iterT beg, iterT end) {
    typedef typename std::remove_reference<decltype(*beg)>::type T;
//    static std::shared_ptr<T> aux(new T(end - beg), [](T *ptr){delete [] ptr;});
    int cmp_times(0);
    if (end - beg <= 15) {
        cmp_times = InsertionSort(beg, end);        //小于15的用InsertionSort
        return cmp_times;
    }
    auto mid = (end - beg) / 2 + beg;
    cmp_times += MergeSort_with_insert(beg, mid);
    cmp_times += MergeSort_with_insert(mid, end);
//    cmp_times += Merge_with_insert(beg, mid, mid, end, aux);
    cmp_times += Merge(beg, mid, mid, end);
    return cmp_times;
}

inline int to_virtual(int size) { return size + 1;}

template <typename T>
void per_down(T* arr, const int size, int vi) {
    // 对VI进行下滤
    while (vi <= size / 2) {
        // 对应的左右子节点
        int son_l = vi * 2;
        int son_r = vi * 2 + 1;

        if (son_r > size) {
            if (arr[son_l - 1] > arr[vi - 1]) {
                std::swap(arr[son_l - 1], arr[vi - 1]);
            }
            break;
        } else {
            int bigger_son = arr[son_l - 1] > arr[son_r - 1]? son_l : son_r;

            if (arr[bigger_son - 1] > arr[vi - 1]) {
                std::swap(arr[bigger_son - 1], arr[vi - 1]);
                vi = bigger_son;
            } else {
                break;
            }
        }
    }
}

template <typename T>
void build_heap(T* arr, const int size) {
    // 不停将新元素上滤
    for (int i = size / 2; i >= 1; --i) {
        int vi = i;     //虚拟的坐标
        per_down(arr, size, vi);
    }
}

template <typename T>
bool heap_test(T* arr, const int size) {
    bool judge(false);

    for (int i = 0; i < size / 2; ++i) {
        int vi = i + 1;
        if (vi * 2 <= size) {
            if (arr[vi - 1] < arr[vi * 2 - 1]) {
                return false;
            }
        }
        if (vi * 2 + 1 <= size) {
            if (arr[vi - 1] < arr[vi * 2]) {
                return false;
            }
        }
    }
    return true;
}

template <typename T>
void HeapSort(T* arr, const int size) {
    //  需要动态更改SIZE
    int cur_size = size;
    build_heap(arr, size);
//    PrintAll(arr, arr + size);
    for (int i = 0; i < size; ++i) {

        std::swap(arr[0], arr[cur_size -1]);
        --cur_size;
        per_down(arr, cur_size, 1);
    }
}

template <typename iterT>
static inline void _division(iterT beg, iterT mid, iterT end) {
    if (*beg > *mid) std::iter_swap(beg, mid);
    if (*beg > *end) std::iter_swap(beg, end);
    if (*mid > *end) std::iter_swap(mid, end);
    std::iter_swap(mid, end - 1);
}

template <typename iterT>
int QuickSort(iterT beg, iterT end){
    typedef typename std::remove_reference<decltype(*beg)>::type T;
    auto quick_sort_swap = swaper<T>();

    int cmp_times = 0;
    if (end - beg <= 15) {
        return InsertionSort(beg, end);

    }
    iterT left = beg, right = end - 1;
    iterT mid = beg + (end - beg) / 2;
    _division(left, mid, right);        // 三数分割
    right--;
    auto pivot = *right;                // 枢纽元在end左侧
    while (left != right) {
        while (left != right && *left <= pivot)
             left++;
        quick_sort_swap(*left, *right);
        while (left != right && *right >= pivot)
            right--;
        quick_sort_swap(*left, *right);
        if (left == right)
            break;
    }
    cmp_times += QuickSort(beg, left);
    cmp_times += QuickSort(left + 1, end);
    // 三数分割切分三次
    return cmp_times + 3;
}

template <typename iterT>
extern void sortTest(iterT beg, iterT end, int(*sort)(iterT, iterT)) {
    clock_t timeb,timee;
    timeb = clock();
    int cmp = sort(beg,end);
    timee = clock();
    std::cout<<"Used time:"<<timee - timeb<<" and compared " << cmp << " times.\n";
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

template <typename T>
void RadixSort2(T* arr, int base, int size) {
    // 用最大值求趟数
    T max_value = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max_value) max_value = arr[i];
    }
    // 需要运行的趟数
    int rounds(0);
    while (max_value) {
        max_value /= base;
        ++rounds;
    }

    auto aux = new T[size];
    int * counts = new int[base + 1];
    int cur_base = 1;
    for (int j = 0; j < rounds; ++j) {
        memset(counts, 0, sizeof(int) * base);

        for (int j = 0; j < size; ++j) {
            ++counts[(arr[j] / cur_base) % base + 1];
        }
        for (int k = 1; k <= base; ++k) {
            counts[k] += counts[k - 1];
        }
        for (int l = 0; l < size; ++l) {
            aux[counts[(arr[l] / cur_base) % base]++] = arr[l];
        }
        // write back
        for (int m = 0; m < size; ++m) {
            arr[m] = aux[m];
        }
        cur_base *= base;
    }


    delete[] aux;
    delete[] counts;
}

template <typename iterT>
int QuickSort_three(iterT beg, iterT end) {
    int swaps = 0;
    if (end - beg <= 15) {
        swaps = InsertionSort(beg, end);
        return swaps;
    }
    iterT left = beg, right = end - 1;
    iterT mid = beg + (end - beg) / 2;
    _division(left, mid, right);        // 三数分割
    iterT lt = left + 1, rt = end - 1;
    auto pivot = *(rt - 1);
    while (left < rt) {
        if (*left > pivot) {
            std::iter_swap(left, rt--);
            ++swaps;
        } else if (*left == pivot) {
            ++left;
        } else if (*left < pivot) {
            ++left, ++lt;
        }
    }
    swaps += QuickSort_three(beg, lt);
    swaps += QuickSort_three(rt, end);
    return swaps;
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
