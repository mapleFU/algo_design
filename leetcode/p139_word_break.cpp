//
// Created by 付旭炜 on 2019/11/2.
//
#include "common_use.h"
#include <string_view>
#include <unordered_set>

using namespace std;

class Solution {
  public:
    bool wordBreak(string s, vector<string> &wordDict) {
        std::unordered_set<string> word_dict_set(wordDict.begin(), wordDict.end());
        typename vector<string>::size_type min_s {10000000};
        for (int k = 0; k < wordDict.size(); ++k) {
            min_s = std::min(min_s, wordDict[k].size());
        }
//        auto min_string = std::min(wordDict.cbegin(), wordDict.cend(),
//                              [](auto &s1, auto &s2) {
//
//                                  return s1->size() < s2->size();
//                              });
//       auto min_s = min_string->size();

        vector<bool> dp_ok(s.size() + 1, false);
        dp_ok[0] = true; // set start(0) true, every body can react it.

        for (auto i = min_s; i <= s.size(); ++i) {
            for (unsigned long j = 0; j < i; ++j) {
                if (dp_ok[j] && word_dict_set.find(s.substr(j, i - j)) !=
                                    word_dict_set.cend()) {
                    dp_ok[i] = true;
                    break;
                }
            }
        }
        return dp_ok[s.size()];
    }
};

int main() {
    Solution soln;
    string s;
    vector<string> vec;

    s = "leetcode", vec = {"leet", "code"};
    cout << soln.wordBreak(s, vec) << '\n';
}