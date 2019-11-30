#include "common_use.h"


using namespace std;

static constexpr char LEFT = '(';
static constexpr char RIGHT = ')';

bool is_valid(const std::string &s, size_t beg, size_t end) {
    int left{0}, right{0};
    for (size_t i = beg; i < end; ++i) {
        if (s[i] == LEFT) {
            ++left;
        } else if (s[i] == RIGHT) {
            if (left > 0) {
                --left;
            } else {
                ++right;
            }
        }
    }
    return left == right && right == 0;
}

class Solution {
  public:
    // brutal force
    // len(s) = n
    // so it can be n * (n / 2) to check.
    // Time complexity is O(N^2).
    int longestValidParentheses(string s) {
        int longest{0};
        // is_valid(s, left, right) checks [left, right)
        // left is i, right is i + dist
        // so i + dist can be equal to  s.size(), and i can be 0
        // so dist can be same as s.size.
        for (int dist = 2; dist <= s.size(); dist += 2) {
            for (int i = 0; i + dist <= s.size(); ++i) {
                if (is_valid(s, i, i + dist)) {
                    longest = dist;
                    break;
                }
            }
        }
        return longest;
    }
};

namespace DP {
    class Solution {
    public:
        // We make use of a \text{dp}dp array where iith element of
        // \text{dp}dp represents the length of the longest valid substring ending at iith index.
        // dp[s] means: longestValidParentheses in [last_valid, s]
        // dp[i] is:
        // 1. if s[i] is LEFT, dp[i] == 0. it doesn't construct valid string.
        // 2. if s[i] is RIGHT, dp[i] depends.
        //     2.1 if s[i - 1] is LEFT, dp[i] is 2 + dp[i - 2]
        //     2.2 if s[i - 1] is RIGHT, may ((())), if s[i - dp[i - 1] - 1] is '(', dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2]
        //         else it's 0
        int longestValidParentheses(string s) {
            std::vector<int> dp(s.size());
            for (size_t i = 1; i < s.size(); ++i) {
                if (s[i] == LEFT) {
                    dp[i] = 0;
                } else if (s[i] == RIGHT) {
                    if (s[i - 1] == LEFT) {
                        // handle corner case if i == 1
                        if (i == 1) {
                            dp[i] = 2;
                        } else {
                            dp[i] = dp[i - 2] + 2;
                        }
                    } else if (s[i - 1] == RIGHT) {
                        // maybe < 0
                        int last_index = i - dp[i - 1] - 1;
                        if (last_index >= 0 && s[last_index] == LEFT) {

                            dp[i] = dp[i - 1] + 2;
                            if (last_index - 1 >= 0) {
                                dp[i] += dp[last_index - 1];
                            }
                        }  else {
                            dp[i] = 0;
                        }
                    }
                }
            }

            // it doesn't handle the case with dp is None(s is "")
//            return *std::max_element(dp.cbegin(), dp.cend());
            if (dp.size() == 0) {
                return 0;
            } else {
                return *std::max_element(dp.cbegin(), dp.cend());
            }
        }
    };
}

namespace Stack {
    class Solution {
    public:
        // 每个右括号有能匹配的左括号的时候即可
        // 计算过程：右括号 - 最远起始
        int longestValidParentheses(string s) {
            int max_ans{0};
            stack<int> index_stack;
            index_stack.push(-1);       // () --> 1 - (-1) --> 2
            for (int i = 0; i < s.size(); ++i) {
                if (s[i] == LEFT) {
                    index_stack.push(i);
                } else {
                    index_stack.pop();
                    // 没有能够匹配的左括号
                    if (index_stack.empty()) {
                        // ()) --> 底下垫着 i
                        // (()())
                        index_stack.push(i);
                    } else {
                        max_ans = std::max(max_ans, i - index_stack.top());
                    }
                }
            }
            return max_ans;
        }
    };
}

/// This solution is a bad solution, please not use it.
namespace FalseCounter {
    class Solution {
    public:

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
}

template <typename Soln>
void cout_solutions() {
    Soln soln;
    string s;

    s = "(()"; // 2
    cout << soln.longestValidParentheses(s) << '\n';

    s = "()"; // 2
    cout << soln.longestValidParentheses(s) << '\n';

    s = ")()())"; // 4
    cout << soln.longestValidParentheses(s) << '\n';

    s = "()(()"; // 2
    cout << soln.longestValidParentheses(s) << '\n';

    s = "))((("; // 0
    cout << soln.longestValidParentheses(s) << '\n';

    s = "))()(()("; // 2
    cout << soln.longestValidParentheses(s) << '\n';

    s = "))())(()))()(((()())(()(((()))))((()(())()((((()))())))())))()(()(()))))())(((())(()()))((())()())((()))(()(())(())((())((((()())()))((()(())()))()(()))))))()))(()))))()())()())()()()()()()()))()(((()()((()(())((()())))(()())))))))(()()(())())(()))))))()()())((((()()()())))))((())(())()()(()((()()))()()())(()())()))()(()(()())))))())()(())(()))(())()(())()((())()((((()()))())(((((())))())())(()((())((()()((((((())))(((())))))))(()()((((((()(((())()(()))(()())((()(((()((()(())())()())(((()))()(((()))))(())))(())()())()(((()))))((())())))())()()))((((()))(())()())()(((())(())(()()((())()())()()())())))((()())(()((()()()(()())(()))(()())((((()(()(((()(((())()((()(()))())()())))))))))))()())()(()(((())()))(((()))((((()())())(()())((()())(()()((()((((()())))()(())(())()))))(())())))))(((((((())(((((()))()))(()()()()))))))(()(()(()(()()(((()()))((()))())((())())()())()))()()(((())))()(())()()(())))(((()))))))))(())((()((()((()))))()()()((())((((((((((()(())))(())((()(()())())(((((((()()()()))())(((()())()(()()))))(()()))))(((()()((()()()(((()))))(()()())()()()(()))))()(())))))))()((((((((()((())))))))(()))()((()())())(";
    cout << soln.longestValidParentheses(s) << '\n';

    s = "";
    cout << soln.longestValidParentheses(s) << '\n';

    // 0 2 0 0 2 6
    s = "()(())";
    cout << soln.longestValidParentheses(s) << '\n';
}

int main() {
    // 2 2 4 2 0 2 490 0 6
//    cout_solutions<Solution>();
//    cout_solutions<DP::Solution>();
//    cout_solutions<Stack::Solution>();
    cout_solutions<FalseCounter::Solution>();
}