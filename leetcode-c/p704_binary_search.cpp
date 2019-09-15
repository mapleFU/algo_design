//
// Created by 付旭炜 on 2019/9/15.
//
#import "common_use.h"

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        size_t left = 0, right = nums.size();
        while (right - left > 1) {
            size_t mid = (right - left) / 2 + left;
            // [ left, mid)
            if (target < nums[mid]) {
                right = mid;
            } else {
                // [mid, right)
                left = mid;
            }
        }
        return nums[left] == target ? static_cast<int>(left) : -1;
    }
};

int main() {
    vector<int> test_vec{-1,0,3,5,9,12};
    int search_index = 9;
    Solution soln;
    cout << soln.search(test_vec, search_index) << '\n';
}