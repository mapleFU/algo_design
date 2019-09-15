//
// Created by 付旭炜 on 2019/9/16.
//

#include "common_use.h"

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        if (nums.size() == 0) {
            return 0;
        }
        int prev{0}, cur{0};
        while (cur < nums.size()) {
            if (cur != 0 && nums[cur - 1] == nums[cur]) {
                ++cur;
                continue;
            }
            nums[prev++] = nums[cur++];
        }
//        nums.resize(prev);
        return prev;
    }
};

int main() {
   Solution soln;
   vector<int> TestVec{1, 1, 2};
   assert(soln.removeDuplicates(TestVec) == 2);
   vector<int> ResVec{1, 2};
    print_perms(TestVec);
    assert(TestVec == ResVec);

    TestVec = {0,0,1,1,1,2,2,3,3,4};
    ResVec = {0, 1, 2, 3, 4};
    soln.removeDuplicates(TestVec);
    print_perms(TestVec);
    assert(TestVec == ResVec);
}