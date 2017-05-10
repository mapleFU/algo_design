//
// Created by 付旭炜 on 2017/3/28.
//

#ifndef BINARYSEARCHTREE_AVLTREE_H
#define BINARYSEARCHTREE_AVLTREE_H


#include "BaseBinaryTree.h"
#include <algorithm>

template <typename T>
class avlTree: public BaseBinaryTree<T> {
public:
    friend TreeNode<T>* _avl_Insert(TreeNode<T>* iroot, const T& Ival);
    friend TreeNode<T>* _avl_Delete(TreeNode<T>* iroot, const T& Ival);
    avlTree(): BaseBinaryTree<T>() {}
    ~avlTree() {
        this->clear(this->root);
    }
    TreeNode<T>* Insert(const T& val) override {
        this->root = _avl_Insert(this->root, val);
        return this->root;
    }
    TreeNode<T>* DeleteNode(const T& val) override ;
};

template <typename T>
inline int Height(TreeNode<T>* iroot) {
    if (iroot == nullptr)
        return -1;
    else
        return iroot->height;
}

template <typename T>
TreeNode<T>* RightSingleRotate(TreeNode<T>* iroot) {
    TreeNode<T>* rnode = iroot->right;
    iroot->right = rnode->left;
    rnode->left = iroot;
    //更新高度
    iroot->height = std::max(Height(iroot->left), Height(iroot->right)) + 1;
    rnode->height = std::max(Height(rnode->left), Height(rnode->right)) + 1;
    return rnode;
}

template <typename T>
TreeNode<T>* LeftSingleRotate(TreeNode<T>* iroot) {
    TreeNode<T>* lnode = iroot->left;
    iroot->left = lnode->right;
    lnode->right = iroot;
    //更新高度
    iroot->height = std::max(Height(iroot->left), Height(iroot->right)) + 1;
    lnode->height = std::max(Height(lnode->left), Height(lnode->right)) + 1;
    return lnode;
}

template <typename T>
TreeNode<T>* RightDoubleRotate(TreeNode<T>* iroot) {
    iroot->right = LeftSingleRotate(iroot->right);
    iroot = RightSingleRotate(iroot);
    return iroot;
}

template <typename T>
TreeNode<T>* LeftDoubleRotate(TreeNode<T>* iroot) {
    iroot->left = RightSingleRotate(iroot->left);
    //切换了iroot;
    iroot = LeftSingleRotate(iroot);
    return iroot;
}

template <typename T>
TreeNode<T>* _avl_Insert(TreeNode<T>* iroot, const T& Ival) {
    if (iroot == nullptr) {
        TreeNode<T>* newnode = new TreeNode<T>(Ival);
        return iroot = newnode;
    }
    if (iroot->val == Ival) {       //找到节点
        ++iroot->times;
    }
    else if (iroot->val < Ival) {
        //执行插入
        iroot->right = _avl_Insert(iroot->right, Ival);
        //进行旋转
        if (Height(iroot->right) - Height(iroot->left) == 2) {
            //和下侧不同，此处应该为< !!!
            if (iroot->right->val < Ival) {     //rr单旋
                iroot = RightSingleRotate(iroot);
            } else {                //rl双旋转
                iroot = RightDoubleRotate(iroot);
            }
        }
    }
    else {      // 大于Ival
        //执行插入
        iroot->left = _avl_Insert(iroot->left, Ival);
        //进行旋转
        if (Height(iroot->left) - Height(iroot->right) == 2) {
            if (iroot->left->val > Ival) {     //ll单旋
                iroot = LeftSingleRotate(iroot);
            } else {                //rl双旋转
                iroot = LeftDoubleRotate(iroot);
            }
        }
    }
    iroot->height = std::max(Height(iroot->left), Height(iroot->right)) + 1;
    return iroot;
}

template <typename T>
TreeNode<T> *avlTree<T>::DeleteNode(const T &val) {
    return this->root = _avl_Delete(this->root, val);
}

template <typename T>
TreeNode<T> *_avl_Delete(TreeNode<T> *iroot, const T &Ival) {
    if (iroot == nullptr) {
        std::cerr<<"Node "<< Ival<< " can't be fount"<<std::endl;
        return nullptr;
    }
    if (iroot->val == Ival) {
        if (iroot->times == 0) {
            std::cerr<<" node "<<Ival<<" can't be find."<<std::endl;
        } else {
            --iroot->times;
        }
    }
    else if (iroot->val < Ival) {
        iroot->right = _avl_Delete(iroot->right, Ival);
    } else {
        iroot->left = _avl_Delete(iroot->left, Ival);
    }
    return iroot;
}

#endif //BINARYSEARCHTREE_AVLTREE_H
