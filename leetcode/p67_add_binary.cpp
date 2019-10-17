//
// Created by 付旭炜 on 2019/9/16.
//
#include "common_use.h"
#include <string>

using namespace std;

class Solution {
  public:
    int load_cnt(const string &s, size_t reverse_index) {
        size_t slen = static_cast<int>(s.size());
        if (slen <= reverse_index) {
            return 0;
        }
        return s[slen - reverse_index - 1] - '0';
    }

  public:
    string addBinary(string a, string b) {
        int carry = 0;
        string s;
        size_t loop_cnt = std::max(a.size(), b.size());
        for (size_t i = 0; i < loop_cnt; ++i) {
            // 第 i 位
            int current = this->load_cnt(a, i) + this->load_cnt(b, i) + carry;
            s.push_back(static_cast<char>(current % 2 + '0'));
            carry = current / 2;
        }
        if (carry) {
            s.push_back(static_cast<char>(carry + '0'));
        }
        std::reverse(s.begin(), s.end());
        return s;
    }
};

int main() {
    Solution soln;
    assert(soln.load_cnt("1", 0) == 1);
    assert(soln.load_cnt("1", 2) == 0);

    cout << soln.addBinary("11", "1") << '\n';
    cout << soln.addBinary("1010", "1011") << '\n';
}