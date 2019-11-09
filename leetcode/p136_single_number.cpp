//
// Created by 付旭炜 on 2019/11/9.
//

#include "common_use.h"

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int number {};
        for (int num: nums) {
            number = (num ^ number);
        }
        return number;
    }
};

int main() {
    Solution soln;
    vector<int> vec;

    vec = {2,2,1};
    std::cout << soln.singleNumber(vec) << std::endl;

    vec = {4,1,2,1,2};
    std::cout << soln.singleNumber(vec) << std::endl;
}