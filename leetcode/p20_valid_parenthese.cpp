//
// Created by 付旭炜 on 2019/11/9.
//

#include "common_use.h"
#include <optional>
#include <stack>
#include <unordered_set>

using namespace std;

inline bool match_char(char ch) {
    switch (ch) {
    case '[':
    case '{':
    case '(':
        return true;
    default:
        return false;
    }
}

inline bool match_lr(char left, char right) {
    return (left == '[' && right == ']') || (left == '(' && right == ')') ||
           (left == '{' && right == '}');
}

class Solution {
  public:
    bool isValid(string s) {
        std::stack<char> matches;
        for (const char c : s) {
            if (match_char(c)) {
                matches.push(c);
            } else {
                auto v = stack_load(matches);
                if (v.has_value() && match_lr(*v, c)) {
                    matches.pop();
                } else {
                    return false;
                }
            }
        }
        return matches.empty();
    }

  private:
    // 熔断 get
    std::optional<char> stack_load(std::stack<char> &chars) {
        if (chars.empty()) {
            return std::nullopt;
        } else {
            return chars.top();
        }
    }
};

int main() {
    Solution soln;
    std::cout << std::boolalpha <<  soln.isValid("()") << '\n';
    std::cout << std::boolalpha <<  soln.isValid("()[]{}") << '\n';
    std::cout << std::boolalpha <<  soln.isValid("(]") << '\n';
    std::cout << std::boolalpha <<  soln.isValid("([)]") << '\n';
    std::cout << std::boolalpha <<  soln.isValid("{[]}") << '\n';
}