//
// Created by 付旭炜 on 2019/3/24.
//

#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>

using namespace std;

/**
1,2,3 → 1,3,2
3,2,1 → 1,2,3
1,1,5 → 1,5,1
 */

/**
 * @param ref: ref of int array
 * @param begin: [begin, end)
 * @param end : [begin, end)
 * @return : index of target
 */
int binary_search(const std::vector<int>& ref, int search_val, int begin, int end, function<bool(int, int)> comp) {
    if (begin + 1 == end) {
        return begin;
    }
    // to stupid...
//    int mid = (end - begin) / 2 + end;
    int mid = (end - begin) / 2 + begin;
    // split them into [beg, mid), [mid, end)
    if (comp(ref[mid], search_val)) {
        return binary_search(ref, search_val, begin, mid, comp);
    } else {
        return binary_search(ref, search_val, mid, end, comp);
    }
}


class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        // next permutation
        // return if size is too small
        if (nums.size() <= 1) {
            return;
        }
        // notice - 1, is the direction
        int cur = nums.size() - 1;
        // handle pre and cur
        while (cur > 0 && nums[cur] <= nums[cur - 1]) {
            --cur;
        }
        //   4 3 2 1
        // p c
        if (cur != 0) {
            // 1 3 4 2
            //   p c
            int swap_index = binary_search(nums, nums[cur - 1], cur, nums.size(), [](int a, int b) { return b >= a;});;
//            cout << swap_index << ' ' << pre << '\n';
            // 1 3 4 2
            //   p   s
            swap(nums[cur - 1], nums[swap_index]);
        }

        reverse(nums.begin() + cur, nums.end());
        return;
    }
};

class SolutionOptimized {
public:
    void nextPermutation(vector<int>& nums) {
        // next permutation
        // return if size is too small
        if (nums.size() <= 1) {
            return;
        }
        // notice - 1, is the direction
        int cur = nums.size() - 1;
        int pre = cur - 1;

        // handle pre and cur
        while (pre > -1) {
            if (nums[cur] > nums[pre]) {
                break;
            }
            --pre;
            --cur;
        }
        //   4 3 2 1
        // p c
        if (pre == -1) {
            reverse(nums.begin(), nums.end());
            return;
        }
        // 1 3 4 2
        //   p c
        int swap_index = cur;
        swap_index = binary_search(nums, nums[pre], cur, nums.size(), [](int a, int b) { return b <= a;});
        cout << "index: " << swap_index << endl;
//        for (; swap_index < nums.size(); ++swap_index) {
//            if (nums[pre] >= nums[swap_index]) {
//                break;
//            }
//        }
        // 1 3 4 2
        //   p   s
        swap(nums[pre], nums[swap_index - 1]);
        reverse(nums.begin() + pre + 1, nums.end());
        return;
    }
};

class SolutionOther {
public:
    // find the weakly decreasing right-sequence, e.g. [4 2 2 1] in original array [3 4 2 2 1]
    // if entire vector is weakly decreasing, simply reverse entire vector
    // otherwise, some right-aligned sub-array is weakly-decreasing
    // get the number to the left of this array, then find number inside the right-sequence
    // that is the smallest possible strictly-higher number than the number to the left
    // e.g. in right-sequence [4 2 2 1], '4' is strictly greater than '3'.
    // swap those two numbers. then reverse the right-sequence
    // e.g. result is [4 1 2 2 3]
    void swapAtIndexes(vector<int>& nums, int left, int right)
    {
        int temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;
    }
    void reverseRightSequence(vector<int>& nums, int start)
    {
        std::reverse(nums.begin() + start, nums.end());
    }
    void nextPermutation(vector<int>& nums) {
        int len = nums.size();
        if (len == 0) return;
        int i = len - 1;
        while (i > 0)
        {
            if (nums[i - 1] < nums[i])
                break;
            --i;
        }
        if (i > 0)
        {
            int j = len - 1;
            while (nums[j] <= nums[i - 1]) --j;
            swapAtIndexes(nums, i-1, j);
        }
        reverseRightSequence(nums, i);
    }
};

class SolutionSlower {
public:
    void nextPermutation(vector<int>& nums) {
        // next permutation
        // return if size is too small
        if (nums.size() <= 1) {
            return;
        }
        // notice - 1, is the direction
        int cur = nums.size() - 1;
        int pre = cur - 1;

        // handle pre and cur
        while (pre > -1) {
            if (nums[cur] > nums[pre]) {
                break;
            }
            --pre;
            --cur;
        }
        //   4 3 2 1
        // p c
        if (pre != -1) {
            // 1 3 4 2
            //   p c
            int swap_index = binary_search(nums, nums[pre], cur, nums.size(), [](int a, int b) { return b >= a;});;
//            cout << swap_index << ' ' << pre << '\n';
            // 1 3 4 2
            //   p   s
            swap(nums[pre], nums[swap_index]);
        }

        reverse(nums.begin() + pre + 1, nums.end());
        return;
    }
};

void print_perms(const std::vector<int>& perms) {
    for (int i = 0; i < perms.size(); ++i) {
        cout << perms[i] << ' ';
    }
    cout << '\n';
}

int main() {
    Solution solution;
    std::vector<int> perms{1, 2, 3};

    solution.nextPermutation(perms);
    print_perms(perms);

    std::vector<int> perms2{1, 3, 4, 2};

    solution.nextPermutation(perms2);
    print_perms(perms2);

    // handle duplicate
    std::vector<int> perms_duplicate{1, 5, 1};
    solution.nextPermutation(perms_duplicate);
    print_perms(perms_duplicate);

    // handle totally reverse
    std::vector<int> perms_totally_rev{5, 1, 1};
    solution.nextPermutation(perms_totally_rev);
    print_perms(perms_totally_rev);
}