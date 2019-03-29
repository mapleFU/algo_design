//
// Created by 付旭炜 on 2019/3/24.
//

#ifndef LEETCODE_C_BINARY_TREE_H
#define LEETCODE_C_BINARY_TREE_H

struct TreeNode {
     int val;
     TreeNode *left;
     TreeNode *right;
     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

#endif //LEETCODE_C_BINARY_TREE_H
