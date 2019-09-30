//
// Created by 付旭炜 on 2019/9/22.
//

#include "common_use.h"
#include <algorithm>

using namespace std;

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

int main() {
    Solution soln;
    vector<int> test_vec{3, 2, 1, 5, 6, 4};
    cout << soln.findKthLargest(test_vec, 2) << '\n';

    // 1 2 2 3 3 4 5 5 6
    test_vec = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << soln.findKthLargest(test_vec, 4) << '\n';

    test_vec = {1};
    cout << soln.findKthLargest(test_vec, 1) << '\n';

    test_vec = {3, 2, 3, 1,  2,  4, 5, 5, 6, 7, 7, 8, 2, 3,
                1, 1, 1, 10, 11, 5, 6, 2, 4, 7, 8, 5, 6};
    //
    vector<int> v2 = test_vec;
    std::sort(v2.begin(), v2.end());
    print_perms(v2);
    cout << soln.findKthLargest(test_vec, 2) << '\n';
}