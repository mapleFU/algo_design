//
// Created by 付旭炜 on 2019/9/16.
//
// TODO: finish this
#include "common_use.h"
#include <cassert>

using namespace std;

inline void loop(const vector<int> &nums, int &pos) {
    // nums[pos] 表示这个位置的值
    // nums[pos] - 1 表示要移动到的下一个位置
    pos = nums[pos];
}

class Solution {
  public:
    int findDuplicate(vector<int> &nums) {
        int quick_pointer = 0, slow_pointer = 0;
        while (true) {
            loop(nums, quick_pointer);
            loop(nums, quick_pointer);
            loop(nums, slow_pointer);
            // 9 5 4 1
            if (quick_pointer == slow_pointer) {
                break;
            }
        }

        int ptr1 = nums[0];
        int ptr2 = slow_pointer;
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }

        return ptr1;
    }
};

int main() {
    vector<int> testvec{2, 5, 9, 6, 9, 3, 8, 9, 7, 1};
    int init = 0;
    loop(testvec, init);
    //    assert(init == 1);
    //    assert(testvec[init] == 5);
    Solution soln;

    assert(soln.findDuplicate(testvec) == 9);

    testvec = {3, 1, 3, 4, 2};
    assert(soln.findDuplicate(testvec) == 3);
}