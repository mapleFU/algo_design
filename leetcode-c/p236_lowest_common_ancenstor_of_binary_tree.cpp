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
#include <set>
#include <utility>
#include <variant>

using namespace std;

//class Solution {
//    // TODO: finish this method to find lcs
//    // bool 表达 is essential point
//    // TreeNode* 表达结果
//    std::variant<bool, TreeNode*> lowestCommonAncestorImpl(TreeNode* root, std::set<TreeNode*>& search_set) {
//        if (root == nullptr) {
//            return false;
//        }
//        auto iter = search_set.find(root);
//        bool is_essential_point = false;
//
//        if (iter != search_set.cend()) {
//            // found it
//            search_set.erase(iter);
//            is_essential_point = true;
//            // judging if search_set is zero
//            if (search_set.empty()) {
//                // 终止点：发现都是 true
//                // 返回 is_essential_point
//                // 最后一个点肯定不是
//                return true;
//            }
//        }
//        bool left_contains_essential, right_contains_essential;
//        auto left = lowestCommonAncestorImpl(root->left, search_set);
//        if (std::holds_alternative<TreeNode*>(left)) {
//            // is tree node
//            return left;
//        } else {
//            left_contains_essential = *std::get_if<bool>(&left);
//        }
//
//        auto right = lowestCommonAncestorImpl(root->right, search_set);
//        if (std::holds_alternative<TreeNode*>(right)) {
//            // is tree node
//            return right;
//        } else {
//            right_contains_essential = *std::get_if<bool>(&right);
//        }
//
//        if (left_contains_essential && right_contains_essential) {
//            return root;
//        } else if (is_essential_point && right_contains_essential) {
//            return root;
//        } else if (is_essential_point && left_contains_essential) {
//            return root;
//        }
//        return is_essential_point;
//    }
//public:
//    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
//        if (p == nullptr || q == nullptr) {
//            return nullptr;
//        }
//        if (root == nullptr) {
//            return nullptr;
//        }
//        std::set<TreeNode*> to_set {p, q};
//        auto v = lowestCommonAncestorImpl(root, to_set);
//        return *std::get_if<TreeNode*>(&v);
//    }
//};


class Solution {
    bool lowestCommonAncestorImpl(TreeNode* root, const std::set<int>& search_set, TreeNode*& target) {
        bool self = false, left = false, right = false;
        // 熔断
        if (target != nullptr) return false;
        if (root == nullptr) return false;
        if (search_set.find(root->val) != search_set.cend()) {
            self = true;
        }
        left = lowestCommonAncestorImpl(root->left, search_set, target);
        right = lowestCommonAncestorImpl(root->right, search_set, target);
        // 熔断
        if (target != nullptr) return false;
        // If the source type is bool,
        // the value false is converted to zero and the value true is converted to one.
        if (self + right + left >= 2) {
            target = root;
        }
        return self || left || right;
    }
public:
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (p == nullptr || q == nullptr) {
            return nullptr;
        }
        if (root == nullptr) {
            return nullptr;
        }

        std::set<int> to_set {p->val, q->val};
        TreeNode* target = nullptr;
        lowestCommonAncestorImpl(root, to_set, target);
        return target;
    }
};


int main() {

}