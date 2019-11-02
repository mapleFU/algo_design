//
// Created by 付旭炜 on 2019/11/2.
//

#include "common_use.h"
#include <iostream>

using namespace std;

class Solution {
public:
    //
    // f(x) = max(f(x - k) + (v[x - k])) for k < x
    // O(N ^ 2) algorithm
    //
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty())
            return 0;
        vector<int> sz(nums.size(), 1);
        sz[0] = 1;  // initialize
        int max_sum = 1;
        for (int i = 1; i < nums.size(); ++i) {
            int current = nums[i];
            int &current_sum = sz[i];
            for (int j = 0; j < i; ++j) {
                if (nums[j] < current) {
                    current_sum = std::max(current_sum, sz[j] + 1);
                }
            }
            max_sum = std::max(max_sum, current_sum);
        }

        return max_sum;
    }
};

class SolutionBSDP {
public:
    int lengthOfLIS(vector<int>& nums) {
        if (nums.empty())
            return 0;
        // allocate memory
        vector<int> dp; dp.reserve(nums.size());
        for(int v: nums) {
            // TODO: make clear why not use upper_bound
            auto lower = std::lower_bound(dp.begin(), dp.end(), v);
            if (lower == dp.cend()) {
                dp.push_back(v);
            } else {
                // replace lower with it
                *lower = v;
            }
        }
        return dp.size();
    }
};

template <typename Soln>
void lengthOfLIS(vector<int>& nums) {
    Soln soln;
    cout << soln.lengthOfLIS(nums) << '\n';
}

int main() {
    vector<int> lis;
    Solution soln;
    lis = {10, 9, 2, 5, 3, 7, 101, 18};

    lengthOfLIS<Solution>(lis);
    lengthOfLIS<SolutionBSDP>(lis);

    lis = {2, 2};
    lengthOfLIS<SolutionBSDP>(lis);
}