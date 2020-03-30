//
// Created by 付旭炜 on 2019/3/24.
//

#ifndef LEETCODE_C_BINARY_TREE_H
#define LEETCODE_C_BINARY_TREE_H

#include <vector>

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

TreeNode* build_root(const std::vector<int>& tree) {
    auto root = new TreeNode(tree[0]);
    int root_idx = 0;
}

#endif //LEETCODE_C_BINARY_TREE_H
