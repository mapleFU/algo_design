//
// Created by 付旭炜 on 2020/1/1.
//

#include "common_use.h"
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

using TreeNodePtr = TreeNode*;

inline static TreeNodePtr left(TreeNodePtr& n) {
    if (n == nullptr) return nullptr;
    return n->left;
}

inline static TreeNodePtr right(TreeNodePtr& n) {
    if (n == nullptr) return nullptr;
    return n->right;
}

inline static int val(const TreeNodePtr& n) {
    if (n == nullptr) return 0;
    return n->val;
}

class Solution {
    bool is_end(TreeNode* t1, TreeNode* t2) {
        return t1 == nullptr && t2 == nullptr;
    }

public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (is_end(t1, t2)) return nullptr;
        int this_sum = val(t1) + val(t2);
        auto current = new TreeNode(this_sum);
        current->left = mergeTrees(left(t1), left(t2));
        current->right = mergeTrees(right(t1), right(t2));
        return current;
    }
};