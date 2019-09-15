//
// Created by 付旭炜 on 2019/9/16.
//

#include "common_use.h"

using namespace std;

class Solution {
private:
    int load_cnt(const vector<int>& v, size_t reverse_index) {
        size_t slen = static_cast<int>(v.size());
        if (slen <= reverse_index) {
            return 0;
        }
        return v[slen - reverse_index - 1];
    }

public:
    vector<int> plusOne(vector<int>& digits) {
        vector<int> new_vec;
        int carry = 1;
        int current_digit = 0;
        for (size_t i = 0; i < digits.size(); ++i) {
            int current = this->load_cnt(digits, i) + carry;
            carry = current / 10;
            new_vec.push_back(current - carry * 10);
        }
        if (carry) {
            new_vec.push_back(carry);
        }
        std::reverse(new_vec.begin(), new_vec.end());
        return new_vec;
    }
};

int main() {
    vector<int> TestVec, ResultVec;
    TestVec = {1, 2, 3};
    ResultVec = {1, 2, 4};
    Solution soln;
    assert(soln.plusOne(TestVec) == ResultVec);

    TestVec = {4, 3, 2, 1};
    ResultVec = {4, 3, 2, 2};
    assert(soln.plusOne(TestVec) == ResultVec);
}