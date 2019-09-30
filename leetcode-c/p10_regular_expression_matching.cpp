//
// Created by 付旭炜 on 2019/9/30.
//

#include "common_use.h"
#include <map>
#include <utility>

using namespace std;

// TODO: change it to std::variant
// struct RawNode {
//    bool MatchAny = false;
//    bool HasStar = false;   // Any Match
//    char origin_char;       // Char
//};
//
// enum class LinkType {
//    AnyLink,
//    CharLink,
//    EmptyLink
//};
//
// struct Link {
//    LinkType type;
//    char link_val;
//};
//
// struct NFANode {
//    std::vector<std::tuple<Link, NFANode*>> links;
//    bool is_end = false;
//};
//
// class Solution {
//    // . : any is ok for single
//    constexpr static char DOT = '.';
//    // * : match zero or n
//    constexpr static char STAR = '*';
//
// public:
//    bool isMatch(string s, string p) {
//        vector<NFANode> nfa_nodes;
//        NFANode* current = nullptr;
//        // push back a start node
//        nfa_nodes.emplace_back(NFANode());
//        current = &nfa_nodes.back();
//
//        {
//            std::vector<RawNode> nodes;
//            size_t index = 0;
//
//            while (index < p.size()) {
//                bool not_star = true;
//                RawNode current;
//                if (p[index] == DOT) {
//                    current.MatchAny = true;
//                } else if (p[index] == STAR) {
//                    assert(index != 0);
//                    nodes.back().HasStar = true;
//                    not_star = false;
//                } else {
//                    current.origin_char = p[index];
//                }
//                if (not_star) {
//                    nodes.push_back(current);
//                }
//                ++index;
//            }
//
//            for(const auto& node: nodes) {
//                if (node.HasStar) {
//
//                } else {
//                    NFANode new_node = NFANode();
//                    Link link;
//                    if (node.MatchAny) {
//                        LinkType t;
//                        t = LinkType::AnyLink;
//                        link.type = t;
//                    } else {
//                        LinkType t;
//                        t = LinkType ::CharLink;
//                        char v = node.origin_char;
//                        link.type = t;
//                        link.link_val = v;
//                    }
//                    nfa_nodes.emplace_back(NFANode());
//                    current->links.emplace_back(make_pair(link,
//                    &nfa_nodes.back())); current = &nfa_nodes.back();
//                }
//            }
//        }
//    }
//};

// . : any is ok for single
constexpr static char DOT = '.';
// * : match zero or n
constexpr static char STAR = '*';

class Solution {
    bool coreMatch(
        string::const_iterator pattern, string::const_iterator pattern_end,
        string::const_iterator current, string::const_iterator current_end,
        std::map<std::tuple<string::const_iterator, string::const_iterator>,
                 bool>& dp_map) {
        auto iter = dp_map.find(make_pair(pattern, current));
        if (iter != dp_map.end()) {
            return iter->second;
        }
        if (pattern == pattern_end) {
            bool answer = current == current_end;
            dp_map[make_pair(pattern, current)] = answer;
            return answer;
        }
        if (current == current_end) {
            if (pattern == pattern_end) {
                dp_map[make_pair(pattern, current)] = true;
                return true;
            } else {
                if (pattern + 1 != pattern_end && *(pattern + 1) == STAR) {
                    bool answer = coreMatch(pattern + 2, pattern_end, current,
                                            current_end, dp_map);
                    dp_map[make_pair(pattern, current)] = answer;
                    return answer;
                } else {
                    dp_map[make_pair(pattern, current)] = false;
                    return false;
                }
            }
        }
        // 不等于 dot 的情况一对一匹配
        assert(*pattern != '*');
        if (pattern + 1 != pattern_end && *(pattern + 1) == STAR) {
            if (*pattern == DOT || *current == *pattern) {
                // 本地 match, 可以避免 branch
                bool answer =  coreMatch(pattern + 2, pattern_end, current + 1,
                                 current_end, dp_map) ||
                       coreMatch(pattern, pattern_end, current + 1,
                                 current_end, dp_map) ||
                       coreMatch(pattern + 2, pattern_end, current,
                                 current_end, dp_map);
                dp_map[make_pair(pattern, current)] = answer;
                return answer;
            } else {
                // 不 match, 一定是跳过
                bool answer = coreMatch(pattern + 2, pattern_end, current,
                                 current_end, dp_map);
                dp_map[make_pair(pattern, current)] = answer;
                return answer;
            }
        } else {
            if (*pattern == DOT || *current == *pattern) {
                bool answer = coreMatch(pattern + 1, pattern_end, current + 1,
                                 current_end, dp_map);
                dp_map[make_pair(pattern, current)] = answer;
                return answer;
            } else {
                dp_map[make_pair(pattern, current)] = false;
                return false;
            }
        }
    }

  public:
    bool isMatch(string s, string p) {
        std::map<std::tuple<string::const_iterator, string::const_iterator>, bool> dp_map;
        return coreMatch(p.cbegin(), p.cend(), s.cbegin(), s.cend(), dp_map);
    }
};

int main() {
    Solution soln;
    string match, regex;
    match = "aa", regex = "a";
    cout << soln.isMatch(match, regex) << '\n';

    match = "aa", regex = "a*";
    cout << soln.isMatch(match, regex) << '\n';

    match = "aa", regex = ".*";
    cout << soln.isMatch(match, regex) << '\n';

    match = "aab", regex = "c*a*b";
    cout << soln.isMatch(match, regex) << '\n';

    match = "a", regex = "ab*";
    cout << soln.isMatch(match, regex) << '\n';

    match = "bbbba", regex = ".*a*a";
    cout << soln.isMatch(match, regex) << '\n';

    match = "aaaaaaaaaaaaab", regex = "a*a*a*a*a*a*a*a*a*a*c";

    cout << soln.isMatch(match, regex) << '\n';
}