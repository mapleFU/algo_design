//
// Created by 付旭炜 on 2019/9/22.
//

#include "common_use.h"
using namespace std;

class Solution {

public:

    int findMin(vector<int>& nums) {
        // [left, right]
        // left 可能在左侧排序，right 在右侧排序
        size_t left = 0, right = nums.size() - 1;

        if (right == 0) {
            return nums[0];
        }
        if (nums[left] < nums[right]) {
            return nums[0];
        }
        // 循环条件：right/left 没贴着
        while (nums[left] >= nums[right]) {
            if( right - left == 1) {
                return nums[right];
            }

            size_t mid = (right + left) / 2;
            if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
                // 都相等
                return *std::min(nums.cbegin(), nums.cend());
            }
            if (nums[mid] > nums[left]) {
                left = mid;
            } else {
                right = mid;
            }
        }
        return nums[left + 1];
    }
};

int main() {
    std::vector<int> nmsl{3, 4, 5, 1, 2};
    Solution soln;
    cout << soln.findMin(nmsl) << '\n';
    nmsl = {2, 1};
    cout << soln.findMin(nmsl) << '\n';
}