#include "common_use.h"
#include <utility>

using namespace std;

class Solution {
    static std::tuple<int, int> count_valid_string(const string &s) {
        int l{}, r{};
        for (auto c : s) {
            if (c == '(') {
                ++l;
            } else if (c == ')') {
                if (l != 0) {
                    --l;
                } else {
                    // r is increasing only
                    ++r;
                }
            }
        }
        return std::make_pair(l, r);
    }

    static bool is_valid(const string &s) {
        int l, r;
        std::tie(l, r) = count_valid_string(s);
        return l == r && l == 0;
    }

    static void dfs(vector<string> &ans, const string &s, int beg_pos, int l,
                    int r) {
        // Nothing to remove.
        if (l == 0 && r == 0) {
            if (is_valid(s))
                ans.push_back(s);
            return;
        }

        for (int i = beg_pos; i < s.length(); ++i) {
            // We only remove the first parentheses if there are consecutive
            // ones to avoid duplications.
            if (i != beg_pos && s[i] == s[i - 1])
                continue;

            if (s[i] == '(' || s[i] == ')') {
                auto load_curr = [&]() {
                    string curr = s;
                    curr.erase(i, 1);
                    return curr;
                };
                if (r > 0 && s[i] == ')')
                    dfs(ans, load_curr(), i, l, r - 1);
                else if (l > 0 && s[i] == '(')
                    dfs(ans, load_curr(), i, l - 1, r);
            }
        }
    }

  public:
    vector<string> removeInvalidParentheses(string s) {
        vector<string> to_return;
        int l, r;
        std::tie(l, r) = count_valid_string(s);
        if (l == 0 && r == 0) {
            to_return.push_back(s);
            return to_return;
        }

        dfs(to_return, s, 0, l, r);
        return to_return;
    }
};

int main() { Solution soln;
    string s1 = "()())()";

    print_perms(soln.removeInvalidParentheses(s1));

    s1 = "(a)())()";
    print_perms(soln.removeInvalidParentheses(s1));

    s1 = "()";
    print_perms(soln.removeInvalidParentheses(s1));

    s1 = "())";
    print_perms(soln.removeInvalidParentheses(s1));

    s1 = "(()";
    print_perms(soln.removeInvalidParentheses(s1));

    s1 = ")(";
    print_perms(soln.removeInvalidParentheses(s1));
}