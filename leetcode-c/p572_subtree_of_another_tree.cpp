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

//public class Solution {
//public boolean isSubtree(TreeNode s, TreeNode t) {
//        return traverse(s,t);
//    }
//public boolean equals(TreeNode x,TreeNode y)
//    {
//        if(x==null && y==null)
//            return true;
//        if(x==null || y==null)
//            return false;
//        return x.val==y.val && equals(x.left,y.left) && equals(x.right,y.right);
//    }
//public boolean traverse(TreeNode s,TreeNode t)
//    {
//        return  s!=null && ( equals(s,t) || traverse(s.left,t) || traverse(s.right,t));
//    }
//}

class Solution {
    // TODO: 学习 KMP, 不回退？
    bool subStruct(TreeNode* s, TreeNode* t) {
        if (s == nullptr || t == nullptr) {
            // both null or t is null, is already subtree
//            return s != nullptr || s == t;
            return s == t;
        }
        if (s->val != t->val) {
            return false;
        }
        return subStruct(s->left, t->left) && subStruct(s->right, t->right);
    }
public:
    bool isSubtree(TreeNode* s, TreeNode* t) {
        if (s == nullptr || t == nullptr) {
            // both null or t is null, is already subtree
//            return s != nullptr || s == t;
            return s == t;
        }
        // now s and t are not null
        // 递归不会重复
        if (s->val == t->val) {
            // match one
            return subStruct(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t);
        } else {
            return isSubtree(s->left, t) || isSubtree(s->right, t);
        }
    }
};