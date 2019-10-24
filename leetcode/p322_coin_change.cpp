//
// Created by 付旭炜 on 2019/10/25.
//

#include "common_use.h"

using namespace std;

/// TODO: make it correct.
class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // amount, 0
        std::vector<int> vec(amount + 1, std::numeric_limits<int>::max() - 1);

        for(const auto&v: coins) {
            for (int i = 0; i <= amount; ++i) {
                // 1 step
                if( v <= amount && i == v) {
                    vec[v] = 1;
                }
                if (vec[i] != std::numeric_limits<int>::max() && i + v <= amount) {
                    vec[v + i] = min(vec[v + i], vec[v] + 1);
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

    coins = {1, 2, 5}, amount = 11;
    cout << soln.coinChange(coins, amount) << '\n';
}