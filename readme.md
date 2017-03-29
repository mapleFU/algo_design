# 用继承写的 二叉搜索树\Avl树\伸展树

## BaseBinary

这是一个抽象基类，提供基础的借口可部分共有的功能，

可以发现，三种树的三序遍历、删除是相同的

BST的查找和avl树的类似，而伸展树要更新节点。

而这些书树插入、删除也各有不同

所以我们将这些操作定义为虚的成员函数

```c++
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
    TreeNode<T>* clear(TreeNode<T>* pt);
};
```

## TreeNode

这里还是使用组合，第一次设计这样的数据结构，把很多东西都无脑设成了成员函数...

```
template <typename T>
struct TreeNode {
    friend class BaseBinaryTree<T>;
    friend class avlTree<T>;
    //Data
    TreeNode<T> *right = nullptr;
    TreeNode<T> *left = nullptr;
    T val;
    int times = 1;
    //Data of AvlTree
    int height = 0;
    TreeNode() = delete;        //不希望外部有直接定义的
    TreeNode(const T& Ival): val(Ival) {}
    TreeNode<T>* Destroy(TreeNode<T>* iroot);
    inline TreeNode<T>* nodeFindMax(TreeNode<T>* iroot);
    TreeNode<T>* nodeFindMin(TreeNode<T>* iroot);
    void nodeInTraverse(TreeNode<T>* iroot);
    void nodePreTraverse(TreeNode<T>* iroot);
    void nodePostTraverse(TreeNode<T>* iroot);
};

```



## BinarySearchTree

二叉搜索树, 重载了Insert Delete

```c++
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
```



## avlTree

```c++
template <typename T>
class avlTree: public BaseBinaryTree<T> {
public:
    friend TreeNode<T>* _avl_Insert(TreeNode<T>* iroot, const T& Ival);
    friend TreeNode<T>* _avl_Delete(TreeNode<T>* iroot, const T& Ival);
    avlTree(): BaseBinaryTree<T>() {}
    ~avlTree();
    TreeNode<T>* Insert(const T& val) override ;
    TreeNode<T>* DeleteNode(const T& val) override ;
};
```

同样重载了 insert和delete.