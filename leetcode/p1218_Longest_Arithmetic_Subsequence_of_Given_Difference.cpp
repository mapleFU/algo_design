//
// Created by 付旭炜 on 2019/10/24.
//

#include "common_use.h"
#include <map>
#include <unordered_map>

using namespace std;

/// The solution using `std::set`.
class Solution {
  public:
    // 1/2 * n^2
    // dp[n] keeps (pos, val)
    int longestSubsequence(vector<int> &arr, int difference) {
        std::unordered_map<int, int> count_map;
        if (arr.empty()) {
            return 0;
        }
        // arr is not empty, must not 0
        int largest = 1;
        for (const auto &v: arr) {
            // if (v - pos) in map<val, dist>
            const auto iter_before = count_map.find(v - difference);
            int current;
            if (iter_before == count_map.cend()) {
                current = count_map[v] = 1;
            } else {
                auto iter_v = count_map.find(v);
                if (iter_v == count_map.cend()) {
                    // not exists
                    // count_map[v] = second + 1
                    current = count_map[v] = iter_before->second + 1;
                } else {
                    current = count_map[v] = max(iter_before->second + 1, iter_v->second);
                }
            }
            largest = max(current, largest);
        }

        return largest;
    }
};

// beats 99.7(speed) and 100(memory)
class DPSolution {
public:
    // 1/2 * n^2
    // dp[n] keeps (pos, val)
    // 1 <= arr.length <= 10^5
    // -10^4 <= arr[i], difference <= 10^4
    // so arr - diff should be in [-20000, 20000]
    constexpr static int MaxSize = 40002;
    constexpr static int PaddingSize = 20000;

    // change the real index to array index
    inline int pad(int v) {
        return v + PaddingSize;
    }
    // The reverse operator of `pad`
    inline int rev_pad(int pad_size) {
        return pad_size - PaddingSize;
    }

    int longestSubsequence(vector<int> &arr, int difference) {
        // zero init
        if (arr.empty()) {
            return 0;
        }
        int range_array[MaxSize]{};
        int largest = 1;
        for(const auto& v: arr) {
            int current;
            current = range_array[pad(v)] = range_array[pad(v - difference)] + 1;
            largest = std::max(largest, current);
        }
        return largest;
    }
};

int main() {
    DPSolution soln;

    vector<int> test_arr;
    int diff;

    test_arr = {1, 2, 3, 4};
    diff = 1;

    std::cout << soln.longestSubsequence(test_arr, diff) << '\n';

    test_arr = {1, 3, 5, 7};
    diff = 1;

    std::cout << soln.longestSubsequence(test_arr, diff) << '\n';

    test_arr = {1, 5, 7, 8, 5, 3, 4, 2, 1};
    diff = -2;

    std::cout << soln.longestSubsequence(test_arr, diff) << '\n';

    test_arr = {1, 1, 1, 1, 1, 1};
    diff = 0;

    std::cout << soln.longestSubsequence(test_arr, diff) << '\n';
}