# 二叉排序树

## 分析

### 需求分析

二叉排序树就是指将原来已有的数据根据大小构成一棵二叉树，二叉树中的所有结点数据满足一定的大小关系，所有的左子树中的结点均比根结点小，所有的右子树的结点均比根结点大。

二叉排序树查找是指按照二叉排序树中结点的关系进行查找，查找关键自首先同根结点进行比较，如果相等则查找成功；如果比根节点小，则在左子树中查找；如果比根结点大，则在右子树中进行查找。这种查找方法可以快速缩小查找范围，大大减少查找关键的比较次数，从而提高查找的效率。

### 功能分析

需要以下功能

1. 支持插入
2. 支持查找

## 设计

数据结构设计

```c++
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
```

以下介绍字段

| 字段声明                                     | 功能                  | 公开性       |
| ---------------------------------------- | ------------------- | --------- |
| PtrToNode root;                          | 根节点                 | protected |
| void travelse();                         | 遍历各个节点并打印           | public    |
| PtrToNode find(const T &value);          | 根据值查找节点             | public    |
| void insert(const T& value);             | 向树中插入节点             | public    |
| PtrToNode node_insert(PtrToNode sroot, const T& value); | 在一个节点中插入对应的节点(递归式的) | public    |
| void node_travelse(PtrToNode sroot, std::function\<void(TreeNode\<T\> *root)\> func); | 遍历树中的节点             | protected |
| PtrToNode node_find(PtrToNode sroot, const T& value); | 递归的从树中查找节点          | protected |
| void clear();                            | 清空整棵树               | public    |

## 功能与实现

### 插入功能的实现

插入功能递归的调用了 `node_insert`函数

```c++
template <typename T>
void BaseTree<T>::insert(const T &value) {
    root = node_insert(root, value);
}
```

函数显示如下

```c++
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
        std::cout << "value " << value << " is already in the tree.";
    }
    return sroot;
}
```

如果节点为空，则创建节点并返回；

如果值小于节点值，插入左节点；

大于节点值，递归插入右节点；

等于节点值则打印信息并返回节点

###遍历功能的实现

遍历功能主要依靠的是`void node_travelse(PtrToNode sroot, std::function<void(TreeNode<T> *root)> func);`

该函数功能实现如下

```c++
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
```

 对书进行中序遍历，并在中序遍历时用func作用于遍历中的节点。

### 查找功能的实现

查找时递归的调用`node_find`函数，查找出适合的节点

```c++
template <typename T>
TreeNode<T>* BaseTree<T>::find(const T &value) {
    return node_find(root, value);
}
```

查找功能实现如下

```c++
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
```

同样递归的在二叉函数中进行查找。

## 功能与测试

#### 建立功能的测试

```
------------------------------
**		 家谱管理系统 		**
**		1.建立二叉排序树		**
**		2.插入元素			**
**		3.查询元素			**
**		4.退出程序			**
Please select: 1
Please input the value to insert in bsort tree.
12 37 67 48 19 44 21 30 19 7 4 24 9 88 100 100 0
value 19 is already in the tree.
value 100 is already in the tree.
4 7 9 12 19 21 24 30 37 44 48 67 88 100 
```

以上建立了二叉树并成功以中序遍历的形式显示出来

#### 插入功能的测试

```
Please input the key to insert: 90
4 7 9 12 19 21 24 30 37 44 48 67 88 90 100 Please select: 3
```

在上述树中插入90，成功的插入了

#### 查找功能的测试

```
Please input the key to search: 90
Search success.
Please select: 3
Please input the key to search: 110
Value 110 is not in the tree
```

成功找到了存在与不存在的数

