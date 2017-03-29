//
// Created by 付旭炜 on 2017/3/28.
//

#ifndef BINARYSEARCHTREE_BASEBINARYTREE_H
#define BINARYSEARCHTREE_BASEBINARYTREE_H

#include <iostream>

template <typename T>
class BaseBinaryTree;

template <typename T>
class TreeNode;

template <typename T>
TreeNode<T>* _Value_Insert(const T& Ival, TreeNode<T>* iroot);

template <typename T>
struct TreeNode {
    friend class BaseBinaryTree<T>;

    //Data
    TreeNode<T> *right = nullptr;
    TreeNode<T> *left = nullptr;
    T val;
    int times = 1;
    //Data of AvlTree
    int height = 0;

    TreeNode() = delete;        //不希望外部有直接定义的
    TreeNode(const T& Ival): val(Ival) {}
    TreeNode<T>* Destroy(TreeNode<T>* iroot) {
        if (iroot == nullptr)
            return iroot;
        Destroy(iroot->right);
        Destroy(iroot->left);
        delete iroot;           //注意要删除iroot, 而不是this
        return nullptr;
    }
    TreeNode<T>* nodeFindMax(TreeNode<T>* iroot) {
        if (iroot == nullptr)
            return nullptr;
        while (iroot->right)
            iroot = iroot->right;
        return iroot;
    }

    TreeNode<T>* nodeFindMin(TreeNode<T>* iroot) {
        if (iroot == nullptr)
            return nullptr;
        while (iroot->left)
            iroot = iroot->left;
        return iroot;
    }
    void nodeInTraverse(TreeNode<T>* iroot) {
        if (!iroot)
            return;
        nodeInTraverse(iroot->left);
        for (int i = 0; i < iroot->times; ++i)
            std::cout<<iroot->val<<' ';
        nodeInTraverse(iroot->right);
    }
    void nodePreTraverse(TreeNode<T>* iroot) {
        if (!iroot)
            return;
        for (int i = 0; i < iroot->times; ++i)
            std::cout<<iroot->val<<' ';
        nodePreTraverse(iroot->left);
        nodePreTraverse(iroot->right);
    }
    void nodePostTraverse(TreeNode<T>* iroot) {
        if (!iroot)
            return;
        for (int i = 0; i < iroot->times; ++i)
            std::cout<<iroot->val<<' ';
        nodePostTraverse(iroot->left);
        nodePostTraverse(iroot->right);
    }
};


template <typename T>
class BaseBinaryTree {
public:
    BaseBinaryTree() = default;
    virtual ~BaseBinaryTree() = default;
    virtual TreeNode<T>* Insert(const T& val) = 0;
    //    virtual TreeNode<T>* Find(const T& val) = 0;
    virtual TreeNode<T>* DeleteNode(const T& val) = 0;
    void DestroyTree() {
        this->root->Destroy(this->root);
    }
    TreeNode<T>* Find(TreeNode<T>* iroot, const T& to_find);
    void InTraverse() {
        root->nodeInTraverse(root);
    }
    void PreTraverse() {
        root->nodePreTraverse(root);
    }
    void PostTraverse() {
        root->nodePostTraverse(root);
    }
protected:
    TreeNode<T>* root;          //根节点
    TreeNode<T>* FindMin(TreeNode<T>* iroot);
    TreeNode<T>* FindMax(TreeNode<T>* iroot);
    TreeNode<T>* clear(TreeNode<T>* pt) {
        if (pt) {
            clear(pt->left);
            clear(pt->right);
            delete pt;
        }
        return nullptr;
    }
};

#endif //BINARYSEARCHTREE_BASEBINARYTREE_H
