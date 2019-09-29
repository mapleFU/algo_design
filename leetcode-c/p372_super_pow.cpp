//
// Created by 付旭炜 on 2019/9/29.
//

#include "common_use.h"

using namespace std;

class Solution {
public:
    static constexpr int EXP = 1337;
    // base^exp
    // to_ret = (base * base, exp / 2) *  (base * base, exp / 2)
    // if exp % 2 == 1:
    //     to_ret *= base
    // return to_ret;
    // 自底向上的时候
    static long long superPowHelper(long long base, long long pos) {
        long long sum = 1;
        base = base % EXP;
        pos = pos % EXP;
        while (pos) {
            if (pos % 2) {
                sum = (sum * base) % EXP;
            }
            base = (base * base) % EXP;
            pos /= 2;
        }
        return sum;
    }
public:
    // a^1234567 % k = (a^1234560 % k) * (a^7 % k) % k = (a^123456 % k)^10 % k * (a^7 % k) % k
    // Suppose f(a, b) calculates a^b % k; Then translate above formula to using f :
    // f(a,1234567) = f(a, 1234560) * f(a, 7) % k = f(f(a, 123456),10) * f(a,7)%k;
    // f(a, 10) = f(1)^10
    int superPow(int a, vector<int>& b) {
        if (a == 0) return 0;
        if (b.empty()) return 1;
        int back_val = b.back();
        b.pop_back();
        return (superPowHelper(superPow(a, b), 10) * superPowHelper(a, back_val)) % EXP;
    }
};

int main() {
    Solution soln;
    cout << soln.superPowHelper(2, 10) << '\n';
    cout << soln.superPowHelper(2, 3) << '\n';
    vector<int> v;
    v = {3};
    cout << soln.superPow(2, v) << '\n';
    v = {1, 0};
    cout << soln.superPow(2, v) << '\n';
    v = {2, 0, 0};
    cout << soln.superPow(2, v) << '\n';
}