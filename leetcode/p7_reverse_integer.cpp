//
// Created by 付旭炜 on 2019/10/24.
//

#include <limits>
#include "common_use.h"

using namespace std;

class Solution {
public:
    // If overflow, then return 0.
    int reverse(int x) {
        // check overflow
        long long v{};
        // [ 2 ^ 31 - 1, - 2 ^ 31 + 1]
        while (x) {
            v *= 10;
            v += x % 10;
            x /= 10;
        }
        if (v > std::numeric_limits<int>::max() || v < std::numeric_limits<int>::min()) {
            return 0;
        }
        return v;
    }
};

class SolutionStandard {
public:
    int reverse(int x) {
        int rev = 0;
        while (x != 0) {
            int pop = x % 10;
            x /= 10;
            if (rev > INT_MAX/10 || (rev == INT_MAX / 10 && pop > 7)) return 0;
            if (rev < INT_MIN/10 || (rev == INT_MIN / 10 && pop < -8)) return 0;
            rev = rev * 10 + pop;
        }
        return rev;
    }
};

int main() {
    Solution soln;
    std::cout << std::numeric_limits<int>::max() << std::endl;
    std::cout << std::numeric_limits<int>::min() << std::endl;
    // should be 0
    std::cout << soln.reverse(std::numeric_limits<int>::max()) << std::endl;
    // 2147483647 -> 7463847412
    std::cout << soln.reverse(std::numeric_limits<int>::max() - 1) << std::endl;
    // -2147483647 ->
    std::cout << soln.reverse(std::numeric_limits<int>::min() + 1) << std::endl;
    std::cout << soln.reverse(std::numeric_limits<int>::min()) << std::endl;
    std::cout << soln.reverse(123) << std::endl;
    std::cout << soln.reverse(-123) << std::endl;
    std::cout << soln.reverse(0) << std::endl;
    std::cout << soln.reverse(321) << std::endl;
}