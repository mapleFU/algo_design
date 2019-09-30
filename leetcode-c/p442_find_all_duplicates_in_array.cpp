//
// Created by 付旭炜 on 2019/3/24.
//
#include <algorithm>
#include <vector>

#include "common_use.h"

using namespace std;

class Solution {
  public:
    vector<int> findDuplicates(vector<int> &nums) {
        vector<int> vec;
        int handling_index = 0;
        while (handling_index < nums.size()) {
            int handling_number = nums[handling_index];

            // 真好放在应该放的位置上, 或者没有东西在这
            if (handling_number == -1 ||
                handling_number == handling_index + 1) {
                // ++index
                ++handling_index;
                continue;
            }
            // handling_number 位置上有元素了
            if (nums[handling_number - 1] == handling_number) {
                // 那么显然，handling_number 是个重复数据
                vec.push_back(handling_number);
                // 设置成 -1
                nums[handling_index] = -1;
                ++handling_index;
                continue;
            }

            std::swap(nums[handling_number - 1], nums[handling_index]);
        }
        return vec;
    }
};

class SolutionOne {
  public:
    vector<int> findDuplicates(vector<int> &nums) {
        vector<int> ret;
        // 在 nums 中的 n
        for (auto n : nums) {
            // an 是对应的绝对位置
            int an = abs(n);
            // 如果对应的小于0，那么显然是重复的
            if (nums[an - 1] < 0) {
                ret.push_back(an);
            }
            // 设置应有的位置对应的为 -绝对值大小
            // 位置为 -1: 已经使用过
            // 位置上的数值则是正常的数值。
            nums[an - 1] = -abs(nums[an - 1]);
        }
        return ret;
    }
};

int main() {
    SolutionOne solution;
    vector<int> dup{4, 3, 2, 7, 8, 2, 3, 1};

    print_perms(solution.findDuplicates(dup));

    Solution soln;

    vector<int> dup2{4, 3, 2, 7, 8, 2, 3, 1};
    print_perms(soln.findDuplicates(dup2));
}