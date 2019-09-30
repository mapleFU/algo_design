//
// Created by 付旭炜 on 2019/9/22.
//

#include "common_use.h"
#include <optional>

using namespace std;

class Solution {
  public:
    int majorityElement(const vector<int> &nums) {
        int current_counter = 0;
        std::optional<int> current = std::nullopt;
        for (const int v : nums) {
            if (current_counter == 0) {
                // 丢掉前面的
                current = v;
                current_counter = 1;
                continue;
            }
            if (current != v) {
                --current_counter;
            } else {
                ++current_counter;
            }
        }
        return *current;
    }
};

int main() {
    Solution soln;
    cout << soln.majorityElement({6, 5, 5}) << '\n';
}