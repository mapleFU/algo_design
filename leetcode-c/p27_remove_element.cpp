//
// Created by 付旭炜 on 2019/3/29.
//

#include "common_use.h"
#include <iostream>
#include <vector>
using namespace std;

class Solution {
  public:
    int removeElement(vector<int> &nums, int val) {
        int pl = 0; // left pointer
        int pr = 0;
        // if nums[i] == val
        //      continue
        // else
        //    nums[pl++] = nums[i]

        // then resize the array to pl

        for (int i = 0; i < nums.size(); ++i) {
            if (nums[i] == val) {
                continue;
            } else {
                nums[pl++] = nums[i];
            }
        }

        // https://stackoverflow.com/questions/21493414/keeping-the-first-n-elements-of-a-stdvector-and-removing-the-rest
        nums.resize(pl);
        return pl;
    }
};

int main() {
    Solution solution;
    vector<int> nums1{2, 3, 3, 2};
    int cnt;
    cnt = solution.removeElement(nums1, 2);
    print_perms(nums1);

    vector<int> nums2{0, 1, 2, 2, 3, 0, 4, 2};
    cnt = solution.removeElement(nums2, 2);
    print_perms(nums2);
}