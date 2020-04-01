#include "common_use.h"

class Solution {
public:
    int numSquares(int n) {
        if (n == 0) return 0;

        std::vector<int> dp(n + 1);
        // fill when case 1.
        for (int i = 0; i < dp.size(); ++i) {
            dp[i] = i;
        }
        int max_n = int(std::sqrt(n + 1));
        for (int j = 2; j <= max_n; ++j) {
            auto base = j * j;
            for (int i = base; i <= n; i ++) {
                dp[i] = std::min(dp[i - base] + 1, dp[i]);
            }
        }

        return dp.back();
    }
};

int main() {
    Solution soln;
    println(soln.numSquares(13));
    println(soln.numSquares(12));
}