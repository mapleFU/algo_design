#include "common_use.h"

using namespace std;

class Solution {
public:
    // F[i, v] = min(F[i - 1, v], min(F[i - 1, v- C]))
    int coinChange(vector<int>& coins, int amount) {
        std::vector<int> vec(amount + 1, -1);
        vec[0] = 0;
        // n log n
        std::sort(coins.begin(), coins.end());
        for(int v: coins) {

        }
    }
};

// [1, 2, 5]
// [amounts..]
// 11 = n
// -> min(current, exists f(n))
//