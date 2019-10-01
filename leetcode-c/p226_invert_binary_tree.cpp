//
// Created by 付旭炜 on 2019/10/1.
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
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        TreeNode* new_right = invertTree(root->left);
        TreeNode* new_left = invertTree(root->right);
        root->left = new_left;
        root->right = new_right;
        return root;
    }
};