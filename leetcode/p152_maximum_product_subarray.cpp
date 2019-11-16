#include "common_use.h"

using namespace std;

class Solution {
  public:
    int maxProduct(vector<int> &nums) {
        // 1..n 的最大值：
        // 1..n-1 最大值，最小值，乘上 a[n] 对比
        assert(!nums.empty());

        int dpMax = nums[0];
        int dpMin = nums[0];
        int maximum = dpMax;

        for (int i = 1; i < nums.size(); ++i) {
            int oldDpMax = dpMax, oldDpMin = dpMin;
            dpMax = std::max({oldDpMax * nums[i], oldDpMin * nums[i], nums[i]});
            dpMin = std::min({oldDpMax * nums[i], oldDpMin * nums[i], nums[i]});
            maximum = std::max(dpMax, maximum);
        }

        return maximum;
    }
};

int main() {
    vector<int> test_data;

    test_data = {2, 3, -2, 4};
    int ans = 6;
    Solution soln;
    cout << soln.maxProduct(test_data) << '\n';

    test_data = {-4, -3, -2};

    cout << soln.maxProduct(test_data) << '\n';
}