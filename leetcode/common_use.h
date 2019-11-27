//
// Created by 付旭炜 on 2019/3/24.
//

#pragma "once"

#include <iostream>
#include <type_traits>
#include <vector>

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

template <typename T>
void print_perms(
        const std::vector<T> &perms,
        typename std::enable_if<!is_vector<T>::value>::type * = nullptr) {
    for (int i = 0; i < perms.size(); ++i) {
        std::cout << perms[i] << ' ';
    }
    std::cout << '\n';
}

template <typename VecT>
void print_perms(
    const std::vector<VecT> &perms,
    typename std::enable_if<is_vector<VecT>::value>::type * = nullptr) {
    for (int i = 0; i < perms.size(); ++i) {
        print_perms<typename VecT::value_type>(perms[i]);
    }
}


