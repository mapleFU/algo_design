//
// Created by 付旭炜 on 2019/3/24.
//
#include <vector>
#include <algorithm>

#include "common_use.h"

using namespace std;

class Solution {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> vec;
        int handling_index = 0;
        while (handling_index < nums.size()) {
//            int handling = nums[handling_index];
            int abs_handling = abs(nums[handling_index]);
            if (abs_handling == handling_index + 1) {
                ++handling_index;
                continue;
            }
            // abs(cur) != cur + 1
            std::swap(nums[nums[handling_index] - 1], nums[handling_index]);

            if (nums[handling_index] == abs_handling) {
                vec.push_back(abs_handling);
                nums[handling_index] = - (handling_index + 1);
            } else if (nums[handling_index] < 0) {
                nums[handling_index] = - (handling_index + 1);
            }
        }
//        sort(vec.begin(), vec.end());
        return vec;
    }
};

class SolutionOne {
public:
    vector<int> findDuplicates(vector<int>& nums) {
        vector<int> ret;
        for (auto n: nums) {
            int an = abs(n);
            if (nums[an - 1] < 0) {
                ret.push_back(an);
            }
            nums[an - 1] = -abs(nums[an - 1]);
        }
        return ret;
    }
};

int main() {
    SolutionOne solution;
    vector<int> dup{4,3,2,7,8,2,3,1};

    print_perms(solution.findDuplicates(dup));
}