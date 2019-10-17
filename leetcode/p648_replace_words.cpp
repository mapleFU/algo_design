//
// Created by 付旭炜 on 2019/9/21.
//

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    //    using TrieTree = std::unique_ptr<std::unordered_map<char, TrieTree>>;
    struct TrieTree {
        std::unique_ptr<std::unordered_map<char, TrieTree>> childs = nullptr;
        bool finished = false;
    };

    void walk(const TrieTree &tree, int depth = 0) {
        if (tree.childs == nullptr) {
            return;
        }
        for (const auto &[name, tree] : *tree.childs) {
            for (int i = 0; i < depth; ++i) {
                cout << "\t";
            }
            cout << name << '\n';
            walk(tree, depth + 1);
        }
    }

  public:
    string replaceWords(vector<string> &dict, string sentence) {
        if (dict.size() == 0) {
            return sentence;
        }
        auto trie_tree = build_trie(dict);

        string ret_s;
        {
            int old_pos = 0;
            while (old_pos < sentence.size()) {
                auto [find, delta_pos] =
                    is_in_tree(sentence, trie_tree, old_pos);
                // copy from
                for (; old_pos < delta_pos; ++old_pos) {
                    ret_s.push_back(sentence[old_pos]);
                }
                while (sentence[old_pos] != ' ' && old_pos < sentence.size()) {
                    if (!find) {
                        ret_s.push_back(sentence[old_pos]);
                    }
                    old_pos++;
                }

                if (sentence[old_pos] == ' ') {
                    ++old_pos;
                    ret_s.push_back(' ');
                }
            }
        }

        return ret_s;
    }

  private:
    std::pair<bool, int> is_in_tree(const string &s, const TrieTree &trieTree,
                                    int seek_pos) {

        if (trieTree.childs == nullptr) {
            return make_pair(true, seek_pos);
        }
        if (s.size() <= seek_pos) {
            return make_pair(false, seek_pos - 1);
        }
        if (s[seek_pos] == ' ') {
            // TODO: add extra checkings here
            bool is_ok = trieTree.childs == nullptr;
            return make_pair(is_ok, seek_pos - 1);
        }
        if (trieTree.finished) {
            return make_pair(true, seek_pos);
        }
        if (trieTree.childs->find(s[seek_pos]) != trieTree.childs->cend()) {

            // find it
            return is_in_tree(s, (*trieTree.childs)[s[seek_pos]], seek_pos + 1);
        } else {
            return make_pair(false, seek_pos);
        }
    }

    TrieTree build_trie(vector<string> &dict) {
        TrieTree base{};
        for (const auto &c : dict) {
            build_with_substr(c, base);
        }
        return base;
    }

    void build_with_substr(const std::string &sub, TrieTree &tree) {
        if (sub.empty()) {
            tree.finished = true;
            return;
        }
        if (tree.childs == nullptr) {
            tree.childs =
                std::make_unique<std::unordered_map<char, TrieTree>>();
        }
        if (tree.childs->find(sub[0]) == tree.childs->cend()) {
            tree.childs->insert(make_pair(sub[0], TrieTree{}));
        }
        build_with_substr(sub.substr(1), (*tree.childs)[sub[0]]);
    }
};

inline std::string_view sub_string(std::string_view s, std::size_t p,
                                   std::size_t n = std::string_view::npos) {
    return s.substr(p, n);
}

std::vector<std::string_view> splitSV(std::string_view strv,
                                      std::string_view delims = " ") {
    std::vector<std::string_view> output;
    size_t first = 0;

    while (first < strv.size()) {
        const auto second = strv.find_first_of(delims, first);

        if (first != second)
            output.emplace_back(strv.substr(first, second - first));

        if (second == std::string_view::npos)
            break;

        first = second + 1;
    }

    return output;
}

class Solution2 {

    struct TrieNode {
        std::unordered_map<char, std::unique_ptr<TrieNode>> node_map;
        bool is_endpoint = false;
    };

  private:
    std::pair<bool, int> find(const TrieNode &root,
                              const std::string_view &sub_s) {
        // current 指向头
        const TrieNode *current = &root;
        int pos = 0;
        while (current != nullptr) {
            auto node_iter = current->node_map.find(sub_s.at(pos));
            // 没有找到
            if (node_iter == current->node_map.cend()) {
                return make_pair(false, 0);
            }

            // 找到了，前进一个
            current = node_iter->second.get();
            pos += 1;

            if (current->is_endpoint) {
                return make_pair(true, pos);
            }
            // not endpoint
            // 没到头，字符串却到头了
            if (sub_s.size() <= pos) {
                return make_pair(false, 0);
            }
        }
        return make_pair(false, 0);
    }

    void build_with_node(std::string_view sub_s, TrieNode &trie_node) {
        if (sub_s.size() == 0) {
            trie_node.is_endpoint = true;
            return;
        }

        // TODO: make clear whats this
        // TODO: trie_node.node_map.try_emplace(sub_s[0]); throw a runtime
        // error.
        trie_node.node_map.try_emplace(sub_s[0], make_unique<TrieNode>());
        build_with_node(sub_string(sub_s, 1), *trie_node.node_map[sub_s[0]]);
    }

    TrieNode build_trie_root(const vector<string> &dict) {
        //        std::unique_ptr<TrieNode> root_node = make_unique<TrieNode>();
        TrieNode root_node{};
        for (const auto &c : dict) {
            build_with_node(c, root_node);
        }
        return root_node;
    }

  public:
    string replaceWords(vector<string> &dict, string sentence) {
        auto root = build_trie_root(dict);
        int last_space = 0;
        string ret;
        for (int i = 0; i <= sentence.size(); ++i) {
            if (sentence[i] == ' ' || i == sentence.size()) {
                auto [is_s, length] = find(
                    root, sub_string(sentence, last_space, i - last_space));
                if (!is_s) {
                    length = i - last_space;
                }

                for (int j = 0; j < length; ++j) {
                    ret.push_back(sentence[last_space + j]);
                }

                last_space = i + 1;
                if (i != sentence.size()) {
                    ret.push_back(' ');
                }
            }
        }
        return ret;
    }
};

int main() {

    //    Solution soln;
    vector<string> dict = {"cat", "bat", "rat"};
    //    cout << soln.replaceWords(dict, "the cattle was rattled by the
    //    battery") << '\n';
    //
    //    dict = {"a", "aa", "aaa", "aaaa"};
    //    cout << soln.replaceWords(dict, "a aa a aaaa aaa aaa aaa aaaaaa bbb
    //    baba ababa") << '\n';

    Solution2 soln2;

    dict = {"cat", "bat", "rat"};
    cout << soln2.replaceWords(dict, "the cattle was rattled by the battery")
         << '\n';

    dict = {"a", "aa", "aaa", "aaaa"};
    cout << soln2.replaceWords(dict,
                               "a aa a aaaa aaa aaa aaa aaaaaa bbb baba ababa")
         << '\n';
}