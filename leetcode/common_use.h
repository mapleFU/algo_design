//
// Created by 付旭炜 on 2019/3/24.
//

#pragma "once"

#include <iostream>
#include <type_traits>
#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// TreeNode* make_list(std::initializer_list<int > val_list) {
//
//}

template <class T> struct is_vector : public std::false_type {};

template <class T> struct is_vector<std::vector<T>> : public std::true_type {};

template <typename T> void print_perms(const std::vector<T> &perms) {
    for (int i = 0; i < perms.size(); ++i) {
        std::cout << perms[i] << ' ';
    }
    std::cout << '\n';
}

template <typename VecT>
void print_perms(const std::vector<std::vector<VecT>> &perms) {
    for (int i = 0; i < perms.size(); ++i) {
        print_perms(perms[i]);
    }
}
