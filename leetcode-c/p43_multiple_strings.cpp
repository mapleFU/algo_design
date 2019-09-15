//
// Created by 付旭炜 on 2019/9/16.
//

#include "common_use.h"
#include <string>

using namespace std;

class Solution {
    void strip_0(string& s) {
        size_t i = 0;
        for (; i < s.size(); ++i) {
            if (s[i] != '0') {
                break;
            }
        }
        s = s.substr(i);
    }

    int load_cnt(const string& s, size_t reverse_index) {
        size_t slen = static_cast<int>(s.size());
        if (slen <= reverse_index) {
            return 0;
        }
        return s[slen - reverse_index - 1] - '0';
    }


    int& set_cnt(vector<int>& s, size_t reverse_index) {
        size_t slen = static_cast<int>(s.size());
        assert (slen > reverse_index);
        return s[reverse_index];
    }

    template <typename expandable>
    void expand(expandable& s, size_t reverse_index) {
        size_t slen = static_cast<int>(s.size());
        if (slen <= reverse_index) {
            for (int i = 0; i <= reverse_index - slen; ++i) {
                // 前填充0
                s.push_back(0);
            }
        }
    }

    string multiply_long_short(string& s_long, string& s_short) {

        vector<int> result;
        for (size_t s_short_index = 0; s_short_index < s_short.size(); ++s_short_index) {
            // s-short 的值 (INT)
            int short_cnt = load_cnt(s_short, s_short_index);
            // 长度改造成 s_long 的长度
            expand(result, s_short_index + s_long.size() - 1);
            for (size_t s_long_index = 0; s_long_index < s_long.size(); ++s_long_index) {
                int current = load_cnt(s_long, s_long_index) * short_cnt;
                set_cnt(result, s_long_index + s_short_index) += current;
            }
            size_t r_size = result.size();
            int carry = 0;
            for (size_t i = 0; i < r_size; ++i) {
                int current = result[i] + carry;
                set_cnt(result, i) = current % 10;
                carry = current / 10;
            }

            while (carry != 0) {
                result.push_back(0);
                set_cnt(result, r_size) = carry % 10;
                carry /= 10;
            }
        }
        string result_s;
        for (int j = 0; j < result.size(); ++j) {
            result_s.push_back(static_cast<char>(result[result.size() - j - 1] + '0'));
        }
        return result_s;
    }
public:
    string multiply(string num1, string num2) {
        strip_0(num1);
        strip_0(num2);
        if (num1.size() == 0 || num2.size() == 0) {
            return "0";
        }
        if (num1.size() > num2.size()) {
            return multiply_long_short(num1, num2);
        }
        return multiply_long_short(num2, num1);
    }
};

int main() {
    Solution soln;
    cout << soln.multiply("123", "45") << '\n';
    cout << soln.multiply("123", "456") << '\n';
    cout << soln.multiply("2", "3") << '\n';
    cout << soln.multiply("9133", "0") << '\n';
}