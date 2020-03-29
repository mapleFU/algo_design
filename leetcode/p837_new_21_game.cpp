#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

/**
 * Alice starts with 0 points, and draws numbers while she has less than K points.
 * During each draw, she gains an integer number of points randomly from the range [1, W],
 * where W is an integer.
 * Each draw is independent and the outcomes have equal probabilities.
 */
class Solution {
public:
    // 0...K..N..N+W
    //     1  1   0
    // f(x) = (1/w) (f(x+1) ... + f(x+w))
    double new21Game(int N, int K, int W) {
        if (K > N) return 0;
        std::vector<double> dp(N + W, 0);
        // [K, N] means passing probability.
        for (int i = K; i <= N && i < K + W; ++i) {
            dp[i] = 1;
        }

        double prev_sum = std::min(N - K + 1, W);
        for (int j = K - 1; j >= 0; --j) {
            dp[j] = double(prev_sum) / W;
            // It's save to get j + W if it's possible K < N.
            // If k >= N, it will return 0.
            prev_sum = double(prev_sum) + dp[j] - dp[j + W];
        }
        return dp[0];
    }
};

int main() {
    Solution soln;
    assert(soln.new21Game(10, 1, 10) == 1);
    assert(soln.new21Game(6, 1, 10) == 0.6);
    std::cout << soln.new21Game(21, 17, 10) << '\n';
    assert(soln.new21Game(21, 17, 10) - 0.73278 <= 0.001);
    assert(soln.new21Game(0, 0, 1) == 1);
}