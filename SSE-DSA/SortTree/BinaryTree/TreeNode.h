//
// Created by 付旭炜 on 2017/10/5.
//

#ifndef SORTTREE_TREENODE_H
#define SORTTREE_TREENODE_H

template <typename T>
struct TreeNode {
    TreeNode*left, *right;
    T value;
    TreeNode() {
        left = right = nullptr;
    }
};




#endif //SORTTREE_TREENODE_H
