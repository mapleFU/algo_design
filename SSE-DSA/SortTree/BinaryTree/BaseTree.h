//
// Created by 付旭炜 on 2017/10/5.
//

#ifndef SORTTREE_BASETREE_H
#define SORTTREE_BASETREE_H

#include "TreeNode.h"
#include <functional>
#include <iostream>

template <typename T>
void delete_node(TreeNode<T>* node) {
    delete node;
    node = nullptr;
}

template <typename T>
void output_node(TreeNode<T>* node) {
    std::cout << node->value << ' ';
}

/*
 * 考虑次数不只一个
 */
template <typename T>
class BaseTree {
public:
    using PtrToNode = TreeNode<T> *;
    explicit BaseTree() {
        root = nullptr;
    }

    void travelse();
    PtrToNode find(const T &value);
    void insert(const T& value);
    ~BaseTree() {clear();}

protected:
    PtrToNode root;
    void clear() {
        node_travelse(root, delete_node<T>);
    }
    PtrToNode node_insert(PtrToNode sroot, const T& value);
    PtrToNode node_find(PtrToNode sroot, const T& value);
    void node_travelse(PtrToNode sroot, std::function<void(TreeNode<T> *root)> func);

private:
    std::function<void(TreeNode<T> *root)> del;
};

template <typename T>
void BaseTree<T>::insert(const T &value) {
    root = node_insert(root, value);
}

template <typename T>
TreeNode<T>* BaseTree<T>::find(const T &value) {
    return node_find(root, value);
}

template <typename T>
void BaseTree<T>::travelse() {
    node_travelse(root, output_node<T>);
}

template <typename T>
TreeNode<T>* BaseTree<T>::node_insert(TreeNode<T>* sroot, const T &value) {
    if (sroot == nullptr) {
        sroot = new TreeNode<T>();
        sroot->right = sroot->left = 0;
        sroot->value = value;
        return sroot;
    } else if (sroot->value < value) {
        // 插入右节点
        sroot->right = node_insert(sroot->right, value);
    } else if (value < sroot->value){
        sroot->left = node_insert(sroot->left, value);
    } else {
        // value equal
        std::cout << "value " << value << " is already in the tree.\n";
    }
    return sroot;
}

template <typename T>
TreeNode<T>* BaseTree<T>::node_find(TreeNode<T>* sroot, const T &value) {
    if (sroot == nullptr) {
        return nullptr;
    } else if (sroot->value == value) {
        return sroot;
    } else if (sroot->value < value) {
        return node_find(sroot->right, value);
    } else {
        return node_find(sroot->left, value);
    }
}


template <typename T>
void BaseTree<T>::node_travelse(PtrToNode sroot, std::function<void(TreeNode<T> *root)> func) {
    if (sroot == nullptr) {
        return;
    }
    auto right = sroot->right;
    node_travelse(sroot->left, func);
    func(sroot);
    node_travelse(right, func);
}



#endif //SORTTREE_BASETREE_H
