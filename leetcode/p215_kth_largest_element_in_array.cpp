//
// Created by 付旭炜 on 2019/9/22.
//

#include "common_use.h"
#include <algorithm>
#include <iterator>
#include <future>
#include <array>

using namespace std;

template <typename T, typename RandomIt = typename std::vector<T>::iterator>
class ConcurrencySolution {
    constexpr static int MinInterval = 4096 / sizeof(T);

    static std::array<T, 2> linearFindKth(RandomIt beg, RandomIt end) {
        std::sort(beg, end);
        return {*beg, *(beg + 1)};
    }

    static std::array<T, 2> secondLargest(RandomIt beg, RandomIt end) {
        auto dist = std::distance(beg, end);
        if (dist < MinInterval) {
            return linearFindKth(beg, end);
        }

        auto mid = dist / 2;
        std::future<std::array<T, 2>> left = std::async(linearFindKth, beg, beg + mid);
        std::future<std::array<T, 2>> right = std::async(linearFindKth, beg + mid, end);
        auto l = left.get();
        auto r = right.get();
        for(auto &v: r) {
            if (v > l[1]) {
                std::swap(l[1], v);
                if (l[0] < l[1]) {
                    std::swap(l[0], l[1]);
                }
            }
        }
        return l;
    }
public:
    T findSecondLargest(RandomIt beg, RandomIt end) {
        return secondLargest(beg, end)[1];
    }
};

class Solution {
    int linearFindKth(vector<int> &nums, int lo, int high, int k) {
        assert(lo <= k && high >= k);
        std::sort(nums.begin() + lo, nums.begin() + high + 1);
        return nums[k];
    }

  public:
    int findKthLargest(vector<int> &nums, int k) {
        int lo = 0, high = nums.size() - 1;
        k = nums.size() - k;
        int last_lo, last_high;
        while (true) {
            if (high - lo <= 15) {
                return linearFindKth(nums, lo, high, k);
            }
            int mid = (lo + high) / 2;
            int pivot_index, pivot;

            last_high = high;
            last_lo = lo;
            while (lo < high) {

                while (high > lo && nums[high] > pivot) {
                    --high;
                }
                if (high > lo) {
                    nums[lo] = nums[high];
                }

                while (high > lo && nums[lo] <= pivot) {
                    ++lo;
                }
                if (high > lo) {
                    nums[high] = nums[lo];
                }
            }
            nums[lo] = pivot;
            // lo == high, 轴点

            if (lo == k) {
                return nums[k];
            } else if (lo > k) {
                high = lo - 1;
                lo = last_lo;
            } else {
                lo = lo + 1;
                high = last_high;
            }
        }
    }
};

class NaiveKthFind {
    // [begin, end)
    int partition(vector<int>& nums, int begin, int end) {
        assert(end > begin);
        std::swap(nums[begin], nums[rand() % (end - begin) + begin]);
        int pivot = nums[begin];
        int left(begin), right(end - 1);
        while (left < right) {
            while (left < right) {
                if (nums[right] > pivot)
                    --right;
                else {
                    nums[left++] = nums[right];
                    break;
                }
            }

            // protect range
            while (left < right) {
                if (nums[left] <= pivot)
                    ++left;
                else {
                    nums[right--] = nums[left];
                    break;
                }
            }
        }
        assert(left == right);
        nums[left] = pivot;
        return left;
    }
public:
    int findKthLargest(vector<int>& nums, int k) {
        int left(0), right(nums.size());
        k = nums.size() - k;
        while (true) {
            int pivot_pos = partition(nums, left, right);
            if (pivot_pos == k) {
                return nums[pivot_pos];
            } else if (pivot_pos > k) {
                right = pivot_pos;
            } else {
                left = pivot_pos + 1;
            }
        }
    }
};

int main() {
    Solution soln;
    NaiveKthFind soln3;

    vector<int> test_vec{3, 2, 1, 5, 6, 4};
    cout << soln.findKthLargest(test_vec, 2) << '\n';
    test_vec = {3, 2, 1, 5, 6, 4};
    cout << soln3.findKthLargest(test_vec, 2) << '\n';
    // 1 2 2 3 3 4 5 5 6
    test_vec = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << soln.findKthLargest(test_vec, 4) << '\n';
    test_vec = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << soln3.findKthLargest(test_vec, 4) << '\n';

    test_vec = {1};
    cout << soln.findKthLargest(test_vec, 1) << '\n';

    test_vec = {3, 2, 3, 1,  2,  4, 5, 5, 6, 7, 7, 8, 2, 3,
                1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6};
    //
    vector<int> v2 = test_vec;
    std::sort(v2.begin(), v2.end());
    print_perms(v2);
    cout << soln.findKthLargest(test_vec, 2) << '\n';

    test_vec = {3, 2, 3, 1,  2,  4, 5, 5, 6, 7, 7, 8, 2, 3,
                1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6};

    ConcurrencySolution<int > soln2;
    cout << soln.findKthLargest(test_vec, 2) << '\n';


}

