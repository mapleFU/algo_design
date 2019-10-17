//
// Created by 付旭炜 on 2019/3/11.
//
#include <array>
#include <iostream>
#include <string>

using namespace std;

class Solution {
  public:
    constexpr static size_t ArrSize = 122 - 65 + 1;

    int longestPalindrome(string s) {
        std::array<int, ArrSize> charCntArr = {};

        //        for (auto& v: charCntArr) {
        //            v = 0;
        //        }
        for (auto ch : s) {
            //            cout << "ch " << ch << " and ch - 65 is " <<
            //            static_cast<int>(ch - 65) << endl;
            charCntArr[ch - 65]++;
        }

        //        bool hasCenter = false;
        int hasCenter = 0;
        int longestLength = 0;
        for (int v : charCntArr) {

            if (v % 2 == 0) {
                longestLength += v;
            } else {
                longestLength += (v - 1);
                hasCenter = 1;
            }
        }

        return hasCenter + longestLength;
    }
};

int main() {
    Solution solution;
    cout << solution.longestPalindrome("abbccdddd") << endl;
}