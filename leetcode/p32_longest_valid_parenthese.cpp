#include "common_use.h"

using namespace std;

class Solution {
  public:
    static constexpr char LEFT = '(';
    static constexpr char RIGHT = ')';
    int longestValidParentheses(string s) {
        int current_beg {0}, longest {0};
        int left = 0, right = 0;

        int current {0};
        for (const char &ch : s) {
            if (ch == RIGHT) {
                if (left > 0) {
                    --left;
                } else {
                    // before here the state was valid.
                    longest = current - current_beg;
                    current_beg = current + 1;  // beg set to next
                }
            } else if (ch == LEFT) {
                ++left;
            }

            ++current;
        }

        return std::max(longest, current - current_beg - left);
    }
};

int main() {
    string s = "(()";

    Solution soln;
    cout << soln.longestValidParentheses(s) << '\n';

    s = ")()())";
    cout << soln.longestValidParentheses(s) << '\n';

    s = "()(()";
    cout << soln.longestValidParentheses(s) << '\n';

    s = "))(((";
    cout << soln.longestValidParentheses(s) << '\n';

    s = "))()(()(";
    cout << soln.longestValidParentheses(s) << '\n';
}