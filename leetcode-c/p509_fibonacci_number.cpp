//
// Created by 付旭炜 on 2019/9/29.
//
#include <cassert>

class Solution {
public:
    int fib(int N) {
        if (N == 0) {
            return 0;
        } else if (N == 1) {
            return 1;
        }
        int pre = 0, cur = 1;
        int cnt = 1;
        while (cnt < N) {
            int last_cur = cur;
            cur = cur + pre;
            pre = last_cur;
            ++cnt;
        }
        return cur;
    }
};

int main() {
    Solution solution;

    assert(solution.fib(0) == 0);
    assert(solution.fib(1) == 1);
    assert(solution.fib(2) == 1);
    assert(solution.fib(3) == 2);
    assert(solution.fib(4) == 3);
    assert(solution.fib(5) == 5);
    assert(solution.fib(6) == 8);
    assert(solution.fib(7) == 13);
}