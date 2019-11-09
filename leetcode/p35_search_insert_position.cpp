//
// Created by 付旭炜 on 2019/11/9.
//

#include "common_use.h"
#include <algorithm>

using namespace std;
class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return std::lower_bound(nums.begin(), nums.end(), target) - nums.begin();
    }
};

int main() {
    Solution soln;
    vector<int > t_vec;

    t_vec = {1,3,5,6};
    std::cout << soln.searchInsert(t_vec, 5) << '\n';

    std::cout << soln.searchInsert(t_vec, 2) << '\n';
    std::cout << soln.searchInsert(t_vec, 7) << '\n';
    std::cout << soln.searchInsert(t_vec, 0) << '\n';
}