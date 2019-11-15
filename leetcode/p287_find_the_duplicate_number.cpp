//
// Created by 付旭炜 on 2019/9/16.
//
// TODO: finish this
#include "common_use.h"
#include <cassert>
#include <set>

using namespace std;

class Solution {
  public:
    int findDuplicate(vector<int> &nums) {
        // basic solution
        std::set<int> nums_set;
        for (int v: nums) {
            if (nums_set.find(v) == nums_set.cend()) {
                nums_set.insert(v);
            } else {
                return v;
            }
        }
        return -1;
    }
};

int main() {
    vector<int> testvec{2, 5, 9, 6, 9, 3, 8, 9, 7, 1};
    int init = 0;
    //    assert(init == 1);
    //    assert(testvec[init] == 5);
    Solution soln;

    assert(soln.findDuplicate(testvec) == 9);

    testvec = {3, 1, 3, 4, 2};
    assert(soln.findDuplicate(testvec) == 3);
}