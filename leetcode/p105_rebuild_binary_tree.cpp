//
// Created by 付旭炜 on 2019/9/22.
//

#include "common_use.h"
#include "link_list.h"
#include <utility>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

using namespace std;

class Solution {
  private:
    TreeNode *buildTreeImpl(const vector<int> &preorder,
                            std::pair<size_t, size_t> interval_preorder,
                            const vector<int> &inorder,
                            std::pair<size_t, size_t> interval_inorder) {
        auto [pre_l, pre_r] = interval_preorder;
        auto [in_l, in_r] = interval_inorder;
        // 拿到 left 的 val
        if (pre_r - pre_l == 1) {
            int mid_val = preorder[pre_l];
            return new TreeNode(mid_val);
        }
        if (pre_r - pre_l == 0) {
            return nullptr;
        }

        int mid_val = preorder[pre_l];
        TreeNode *current = new TreeNode(mid_val);
        size_t split_point;

        // split point 找到 inorder[split_point] == mid_val 的情况
        for (split_point = in_l; split_point < in_r; ++split_point) {
            if (inorder[split_point] == mid_val) {
                break;
            }
        }

        size_t left_length = split_point - in_l;
        // pre_l + 1 (第一个点之外)，pre_l + 1
        TreeNode *left = buildTreeImpl(
            preorder, make_pair(pre_l + 1, pre_l + 1 + left_length), inorder,
            make_pair(in_l, split_point));

        TreeNode *right =
            buildTreeImpl(preorder, make_pair(pre_l + 1 + left_length, pre_r),
                          inorder, make_pair(split_point + 1, in_r));

        current->left = left;
        current->right = right;
        return current;
    }

  public:
    TreeNode *buildTree(vector<int> &preorder, vector<int> &inorder) {
        if (preorder.size() == 0) {
            return nullptr;
        }
        // s1: preorder mid | left | right
        // s2: inorder left | mid | right
        // rebuild: recursive
        // 1. find me in s1, and find in s2
        // 2. find length of it.
        // 3. recursive
        // The condition when recursive stop:
        // length == 1, build node and just return.
        return buildTreeImpl(preorder, make_pair(0, preorder.size()), inorder,
                             make_pair(0, preorder.size()));
    }
};

int main() {
    Solution soln;

    vector<int> v1{3, 9, 20, 15, 7};
    vector<int> v2{3, 9, 20, 15, 7};
    soln.buildTree(v1, v2);
}