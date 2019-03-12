//
// Created by 付旭炜 on 2019/3/6.
//

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

class Solution {
public:
    virtual string longestPalindrome(string s) = 0;
};

class ExpandAroundCenter: public Solution {
public:
    string longestPalindrome(string s) override {
        int longest = 1;
        int mid = 0;
        for (int i = 0; i < s.size(); ++i) {
            int currentLength = checkPalindromeLength(s, i);
            if (currentLength >= longest) {
                longest = currentLength;
                mid = i;
            }
        }

        int doubleLongest = 0;
        int mid2 = 0;
//        errors: s.size -1 is stupid
        for (int i = 0; i + 1 < s.size(); ++i) {
            int currentLength = checkDouble(s, i);
            if (currentLength >= doubleLongest) {
                doubleLongest = currentLength;
                mid2 = i;
            }
        }

        try {
            int beg_pos, end_pos;
            if (longest == 0 && doubleLongest == 0) {
                return "";
            }

            if (longest > doubleLongest) {
                beg_pos = mid - int(longest-1)/2;
                end_pos = mid + int(longest-1)/2 + 1;

            } else {
                beg_pos = mid2 - doubleLongest / 2+ 1;
                end_pos = mid2 + doubleLongest / 2 + 1;
            }

            return s.substr(beg_pos, end_pos - beg_pos);

        } catch (std::out_of_range of_range) {
            cerr << longest << doubleLongest << mid << mid2 << endl;
            exit(EXIT_FAILURE);
        }



    }

private:
    // these two can be compact as one expand around center

    int checkPalindromeLength(const string& s, int pos) {
        if (pos < 0 || pos >= s.size()) {
            // invalid input
            return -1;
        }
        int rb = s.size() - pos;
        int lb = pos - 0;
        int mb = min(rb, lb);

        int bios = 1;
        for (; bios <= mb; ++bios) {
            if (s[pos - bios] != s[pos + bios]) {
//                --bios;
                break;
            }
        }
        return (bios - 1) * 2 + 1;
    }

    int checkDouble(const string& s, int pos) {
        if (pos < 0 || pos + 1 >= s.size()) {
            return -1;
        }
        if (s[pos] != s[pos + 1]) {
            return -1;
        }
        int mb = min(pos - 0, int(s.size())- pos - 1);
        int l = pos, r = pos + 1;
        int bios = 0;
        for (; bios <= mb; ++bios) {
            if (s[l - bios] != s[r + bios]) {
//                --bios;
                break;
            }
        }
        return bios * 2;
    }
};

string Manacher(string s) {
    // Insert '#'
    string t = "$#";
    for (int i = 0; i < s.size(); ++i) {
        t += s[i];
        t += "#";
    }
    // Process t
    vector<int> p(t.size(), 0);
    int mx = 0, id = 0, resLen = 0, resCenter = 0;
    for (int i = 1; i < t.size(); ++i) {
        p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
        while (t[i + p[i]] == t[i - p[i]]) ++p[i];
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
        if (resLen < p[i]) {
            resLen = p[i];
            resCenter = i;
        }
    }
    return s.substr((resCenter - resLen) / 2, resLen - 1);
}

class CopyManachar: public Solution {
    string longestPalindrome(string s) override {
        string t = "$#";
        for (int i = 0; i < s.size(); ++i) {
            t += s[i];
            t += "#";
        }
        // Process t
        vector<int> p(t.size(), 0);
        int mx = 0, id = 0, resLen = 0, resCenter = 0;
        for (int i = 1; i < t.size(); ++i) {
            p[i] = mx > i ? min(p[2 * id - i], mx - i) : 1;
            while (t[i + p[i]] == t[i - p[i]]) ++p[i];
            if (mx < i + p[i]) {
                mx = i + p[i];
                id = i;
            }
            if (resLen < p[i]) {
                resLen = p[i];
                resCenter = i;
            }
        }
        return s.substr((resCenter - resLen) / 2, resLen - 1);
    }
};
class Manachar: public Solution {
public:
    string longestPalindrome(string s) override {
        if (s.size() <= 1) {
            return s;
        }

        // build new string
//        long str_size = s.size() * 2 + 1;
        int str_size = s.size() * 2 + 1;

        std::string manachar(str_size, '#');
        std::vector<int> manacharCnt(str_size);

        for (int i = 0; i < str_size; ++i) {
            manachar[i * 2 + 1] = s[i];
        }

        // manachar center
        int center = 0;
        int maxLength = 0;
        int midLength = 0;
        int midCenter = 0;
        // loop
        for (int j = 1; j < str_size; ++j) {
            int minBios;      // min bios with mirror
            if (manacharCnt[midCenter] + midCenter < j) {
                minBios = 0;
            } else {
                minBios = min(manacharCnt[2 * midCenter - j], j - midCenter);
            }
            int currentLength = checkPalindromeBios(manachar, j, minBios) - 1;
//            cout << "j=" << j << ' ' << "length=" << currentLength << endl;
            if (currentLength >= maxLength) {
                maxLength = currentLength;
                center = j;
            }
            if (j + currentLength >= midLength) {
                midLength = j + currentLength;
                midCenter = j;
            }
            manacharCnt[j] = currentLength;

        }
        // [beg, end] == [beg, end + 1)
        return s.substr(midCenter / 2, maxLength);
    }

private:
    int checkPalindromeBios(const string& s, int pos, int currentBios) {
        if (pos < 0 || pos >= s.size()) {
            // invalid input
            return -1;
        }
        int rb = s.size() - pos;
        int lb = pos - 0;
        int mb = min(rb, lb);

        for (; currentBios <= mb; ++currentBios) {
            if (s[pos - currentBios] != s[pos + currentBios]) {
                break;
            }
        }
        return currentBios;
    }
};


int main() {
//  string data;
//  cin >> data;
    Manachar solution;
    cout << solution.longestPalindrome("abbac") << endl;
    cout << "\n\n";
    cout << solution.longestPalindrome("babbad") << endl;
    cout << "\n\n";
    cout << solution.longestPalindrome("abbbac") << endl;
    cout << "\n\n";
    cout << solution.longestPalindrome("babad") << endl;
    cout << "\n\n";

    cout << solution.longestPalindrome("") << endl;
}
