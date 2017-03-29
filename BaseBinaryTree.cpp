//
// Created by 付旭炜 on 2017/3/28.
//

#include "BaseBinaryTree.h"
//funtion of TreeNode


// function of class BaseBinaryTree
template <typename T>
TreeNode<T> *BaseBinaryTree<T>::FindMin(TreeNode<T> *iroot) {
    return iroot->nodeFindMin(iroot);
}

template <typename T>
TreeNode<T> *BaseBinaryTree<T>::FindMax(TreeNode<T> *iroot) {
    return iroot->nodeFindMax(iroot);
}

template <typename T>
TreeNode<T> *BaseBinaryTree<T>::Find(TreeNode<T> *iroot, const T &to_find) {
    if (iroot == nullptr || to_find == iroot->val)
        return iroot;
    else if (iroot->val < to_find)
        return Find(iroot->right, to_find);
    else
        return Find(iroot->left, to_find);
}