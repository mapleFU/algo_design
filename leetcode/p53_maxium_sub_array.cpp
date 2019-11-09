//
// Created by 付旭炜 on 2019/11/9.
//

#include "common_use.h"
#include <numeric>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        // if s[i..j] is max Sub Array, s[i - 1] < 0, s[j + 1] < 0
        //
//        int sub_val = std::numeric_limits<int>::min();
        int sub_val = 0;
        int max_sub_val = std::numeric_limits<int>::min();
        for(int v: nums) {
            sub_val += v;
            max_sub_val = std::max(sub_val, max_sub_val);
            if (sub_val < 0)
                sub_val = 0;
        }
        return max_sub_val;
    }
};

int main() {
    Solution soln;
    std::vector<int> v= {-1};
    std::cout << soln.maxSubArray(v) << std::endl;
}