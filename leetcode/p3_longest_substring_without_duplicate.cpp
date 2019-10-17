//
// Created by 付旭炜 on 2019/7/6.
//
#include <iostream>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
  public:
    // 做 max_delta 前保证 [beg, end] 是满足要求的串
    // end 是末尾游标
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> position_map;
        // [beg, end]
        int beg = 0, end = 0;
        // Warn: if s = "", it will return max_delta
        int max_delta = 0;
        while (end < s.length()) {
            auto pos = position_map.find(s[end]);
            if (pos != position_map.end()) {
                // if beg >= pos->second, do nothing
                // max_delta max before beg
                // >= 等于
                if (pos->second >= beg) {
                    beg = pos->second + 1;
                }
            }
            //            cout << beg << ' ' << end << '\n';
            max_delta = max(max_delta, end - beg + 1);
            position_map[s[end]] = end;
            ++end;
        }

        return max_delta;
    }
};

int main() {
    Solution solution;
    string s("aaaaa");
    std::cout << solution.lengthOfLongestSubstring(s) << std::endl;
    s = "abcabcbb";

    std::cout << solution.lengthOfLongestSubstring(s) << std::endl;

    s = " ";
    std::cout << solution.lengthOfLongestSubstring(s) << std::endl;

    s = "abcde";
    std::cout << solution.lengthOfLongestSubstring(s) << std::endl;
}