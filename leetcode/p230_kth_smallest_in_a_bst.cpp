#include "common_use.h"
#include <optional>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

//bool is_leaf(TreeNode* node) {
//    if (node == nullptr) return false;
//    return node->left == nullptr && node->right == nullptr;
//}

std::optional<int> traverse(TreeNode* node, int& pre) {
    if (node == nullptr) {
        return std::nullopt;
    }
    // handle left
    auto v = traverse(node->left, pre);
    if (v.has_value()) return v;

    // handle self
    --pre;
    if (pre == 0) {
        return node->val;
    }

    // handle right
    v = traverse(node->right, pre);
    if (v.has_value()) return v;
    return std::nullopt;
}
class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        return traverse(root, k).value();
    }
};

int main() {
    auto root = new TreeNode(3);
    root->left = new TreeNode(1);
    root->right = new TreeNode(4);
    root->left->right = new TreeNode(2);
    Solution soln;
    std::cout << soln.kthSmallest(root, 1) << std::endl;
}