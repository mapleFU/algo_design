//
// Created by 付旭炜 on 2019/10/1.
//

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include "common_use.h"

class Solution {
    bool twoIsSymmetic(TreeNode* node1, TreeNode* node2) {
        if(node1 == nullptr || node2 == nullptr) {
            return node1 == node2;
        }
        // now node1 and node2 is not nullptr
        if (node1->val != node2->val) {
            return false;
        }
        // now node1->val == node2->val
        return twoIsSymmetic(node1->left, node2->right) && twoIsSymmetic(node1->right, node2->left);
    }
public:
    bool isSymmetric(TreeNode* root) {
        if (root == nullptr) {
            return true;
        }
        // 比较左右子树
        // 比较左节点，右节点：判断 nullptr, 是否相等/都是 null -> 返回 true, 不相等返回 false
        // 如果相等，递归的 node1 left 和 node2 的 right; node1 right 和 node2 left
        return twoIsSymmetic(root->left, root->right);
    }
};