//
// Created by 付旭炜 on 2019/9/21.
//
// 背包问题

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
  public:
    bool canPartition(vector<int> &nums) {

        int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % 2) {
            return false;
        }
        // dp[index + 1][sum_val + 1]
        std::vector<std::vector<bool>> dp(
            nums.size() + 1,
            std::vector<bool>(static_cast<size_t>(sum + 1), false));

        // 第0个数值，里面只有1是true
        for (int i = 0; i < nums.size() + 1; ++i) {
            dp[i][0] = true;
        }

        // dp start
        // dp[index][sum_val] = dp[index - 1][sum_val - num[index]]
        // 这么多个数字
        for (int j = 1; j <= nums.size(); ++j) {
            int current_val = nums[j - 1];
            for (int k = 0; k < current_val; ++k) {
                dp[j][k] = dp[j - 1][k];
                if (dp[j][k]) {
                    cout << "dp[i] is true in loop " << j << ", index "
                         << current_val << '\n';
                }
            }
            for (int i = current_val; i <= sum; ++i) {
                dp[j][i] = dp[j - 1][i - current_val] || dp[j - 1][i];
                if (dp[j][i]) {
                    cout << "dp[i] is true in loop " << j << ", index "
                         << current_val << '\n';
                }
            }
        }
        return dp[nums.size()][sum / 2];
    }
};

class SolutionOne {
  public:
    bool canPartition(vector<int> &nums) {

        int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
        if (sum % 2) {
            return false;
        }
        // dp[index + 1]
        std::vector<bool> dp(static_cast<size_t>(sum + 1), false);

        // 可以到 0
        dp[0] = true;
        for (int j = 1; j <= nums.size(); ++j) {
            int current_val = nums[j - 1];
            for (int i = sum; i >= current_val; --i) {
                dp[i] = dp[i - current_val] || dp[i];
            }
            if (dp[sum / 2]) {
                return true;
            }
        }
        return dp[sum / 2];
    }
};

int main() {
    //    Solution soln;
    //    std::vector<int> v{0, 1, 5, 6};
    //    cout << soln.canPartition(v) << '\n';
    //    v = {1, 5, 11, 5};
    //    cout << soln.canPartition(v) << '\n';
    //    v = {1, 2, 5};
    //    cout << soln.canPartition(v) << '\n';
    //    v = {2,2,3,5};
    //    cout << soln.canPartition(v) << '\n';

    SolutionOne soln2;
    std::vector<int> v2{0, 1, 5, 6};
    cout << soln2.canPartition(v2) << '\n';
    v2 = {1, 5, 11, 5};
    cout << soln2.canPartition(v2) << '\n';
    v2 = {1, 2, 5};
    cout << soln2.canPartition(v2) << '\n';
    v2 = {2, 2, 3, 5};
    cout << soln2.canPartition(v2) << '\n';
}