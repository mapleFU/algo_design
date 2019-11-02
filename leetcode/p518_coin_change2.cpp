
#include "common_use.h"

using namespace std;

/// TODO: make it correct.
class Solution {
public:
    // F[i,v] = sum{F[i − 1,v],F[i,v − C[i]]}
    // 之前是 max, 现在这表示状态性叠加
    // 0-1 背包问题
    // 完全背包问题：F[i,v]=max{F[i−1,v−kCi]+kWi |0≤kCi ≤v}
    int change(int amount, vector<int>& coins) {
        // amount, 0
        // F[i, v] 第 i 轮为 v 的
        //
        std::vector<int> vec(amount + 1, 0);
        vec[0] = 1; // initialize 0 as 1
        for (int v: coins) {
            for (int i = amount; i >= v; --i) {
                for (int j = 1; j * v <= i; ++j) {
                    if (i - v * j < 0) break;
                    vec[i] += vec[i - v * j];
                }
            }
        }
        return vec[amount];
    }
};

int main() {
    Solution soln;
    vector<int> coins;
    int amount;

    coins = {1, 2, 5}, amount = 5;
    cout << soln.change(coins, amount) << '\n';
}