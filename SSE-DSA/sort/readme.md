# 排序算法及其比较

下列按摊还时间比较各种排序算法。

## O(N^2) 级别算法

### 插入排序(正常)

```c++
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
```

逐个向前，完成插入操作，算法的摊还开销是 N^2 级别的

| 算法复杂度  | 算法稳定性 | 适合情况                           |
| ------ | ----- | ------------------------------ |
| O(n^2) | 稳定    | 小规模局部有序数据的排序, 可以用来处理高级排序的小规模情况 |

### 选择排序

```c++ 
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
```

每次选择一个元素排序

| 算法复杂度  | 算法稳定性 | 适合情况               |
| ------ | ----- | ------------------ |
| O(n^2) | 不稳定   | 交换次数最少，适合交换代价极高的情况 |

### 冒泡排序

```c++
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
```

| 算法复杂度  | 算法稳定性 | 适合情况                       |
| ------ | ----- | -------------------------- |
| O(n^2) | 稳定    | 我真不知道这个适合啥，适合新手入门？交换的次数过多了 |



### 带二分查找的插入排序

```c++
/*
 * WARNING:it should be RandomAccess
 */
template <typename iterT>
int InsertionSortWithBisect(iterT beg, iterT end) {
    if (end - beg <= 0)
        return 0;
    for (auto iter1 = beg + 1; iter1 != end; ++iter1) {
        // 在允许范围内最后一个交换的数 [1, 2, 3, 4, 5] 3.5 => 4; 6->END;4.5->5;0.5 ->1
        auto iter_end = bisect(beg, iter1, *iter1);
        if (iter_end == iter1) continue;
        auto cur_iter = iter1;
        while (iter_end != cur_iter) {
            std::swap(*cur_iter, *(cur_iter-1));
            --cur_iter;
        }
        std::swap(*cur_iter, *iter_end);
    }
    return 10;
}
```
| 算法复杂度  | 算法稳定性 | 适合情况                         |
| ------ | ----- | ---------------------------- |
| O(n^2) | 稳定    | 插入排序优化，不过本人实际使用中发现效果其实一般啊... |

## 以上几种排序的测试

| 数据规模 | 数据范围       |
| ---- | ---------- |
| 5000 | 0 — 100000 |

测试结果

| 排序          | 耗时(时间戳) | 比较次数    |
| ----------- | ------- | ------- |
| 插入排序        | 116664  | 6151052 |
| 二分查找优化的快速排序 | 97430   | 6156168 |
| 冒泡排序        | 326539  | 6151052 |
| 选择排序        | 124272  | 6052614 |

## O(nlgn)算法和希尔排序

### 希尔排序

```c++
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
```

`Increments`函数生成Sedgewick增量序列，根据这个序列，利用希尔排序。



| 算法复杂度 | 算法稳定性 | 适合情况   |
| ----- | ----- | ------ |
| 未知    | 不稳定   | 结果发人深省 |

### 归并排序

```c++
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
```

归并排序把序列分成两段，并分别排序-整体排序

| 算法复杂度   | 算法稳定性 | 适合情况          |
| ------- | ----- | ------------- |
| O(nlgn) | 不稳定   | 内存足够，数据规模大排序。 |

### 堆排序

```c++
emplate <typename T>
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
```

用下滤处理堆排序。
| 算法复杂度   | 算法稳定性 | 适合情况       |
| ------- | ----- | ---------- |
| O(nlgn) | 不稳定   | 内存需要额外内存小。 |

### 快速排序

```c++
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
```

