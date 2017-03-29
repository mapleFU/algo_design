//
// Created by 付旭炜 on 2017/3/28.
//

#ifndef BINARYSEARCHTREE_BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_BINARYSEARCHTREE_H

#include "BaseBinaryTree.h"

template <typename T>
TreeNode<T> *_Value_Insert(const T &Ival, TreeNode<T>* iroot) {  //BinarySearchTree的
    if (iroot == nullptr) {
        TreeNode<T>* p = new TreeNode<T>(Ival);
        return p;
    }
    if (iroot->val == Ival)
        iroot->times++;
    else if (iroot->val < Ival)
        iroot->right = _Value_Insert(Ival, iroot->right);
    else
        iroot->left = _Value_Insert(Ival, iroot->left);
    return iroot;
}

template <typename T>
TreeNode<T> *_Value_DeleteNode(const T &Ival, TreeNode<T>* iroot) {  //BinarySearchTree的
    if (iroot == nullptr) {
        std::cerr<< Ival<<" not been found."<<std::endl;
        return nullptr;
    }
    if (iroot->val == Ival) {
        iroot->times--;
        if (iroot->times == 0) {    //应当被删除了
            if (iroot->left && iroot->right) {      //左右都存在
                auto delp = iroot->nodeFindMax(iroot->right);       //右子数最大值
                iroot->val = delp->val, iroot->times = delp->times;
                delp->times = 1;
                _Value_DeleteNode(iroot->val, iroot->right);        //删除这个节点
            }
            else if (iroot->right) {    //右节点存在
                auto delp = iroot->right;
                *iroot = *delp;
                delete delp;
            }
            else if (iroot->left) {     //左节点存在
                auto delp = iroot->left;
                *iroot = *delp;
                delete delp;
            }
        }
    }
    else if (iroot->val < Ival)
        _Value_DeleteNode(Ival, iroot->right);
    else
        _Value_DeleteNode(Ival, iroot->left);
    return iroot;
}

template <typename T>
class BinarySearchTree: public BaseBinaryTree<T> {
public:
    friend TreeNode<T> *_Value_Insert(const T &Ival, TreeNode<T>* iroot);
    virtual TreeNode<T>* Insert(const T& val) override ;
    virtual TreeNode<T>* DeleteNode(const T& val) override {
        _Value_DeleteNode(val, this->root);
    }
    BinarySearchTree(): BaseBinaryTree<T>() {}
    ~BinarySearchTree() override {
        this->DestroyTree();
    }
};


template <typename T>         //TODO:为啥这样就能运行
TreeNode<T> *BinarySearchTree<T>::Insert(const T &val) {
    this->root = _Value_Insert(val, this->root);
    return this->root;
}

#endif //BINARYSEARCHTREE_BINARYSEARCHTREE_H
