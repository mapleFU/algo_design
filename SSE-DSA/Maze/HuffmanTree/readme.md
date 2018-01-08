# 电网建设造价模拟系统

##项目简介

假设一个城市有n个小区，要实现n个小区之间的电网都能够相互接通，构造这个城市n个小区之间的电网，使总工程造价最低。请设计一个能够满足要求的造价方案。

## 项目功能要求：
在每个小区之间都可以设置一条电网线路，都要付出相应的经济代价。n个小区之间最多可以有n（n-1）/2条线路，选择其中的n-1条使总的耗费最少。

## 需求分析
1. 建立哈夫曼树
2. 输出顶点数值

## 数据结构设计

### node

表示哈夫曼树的节点，可以判断是否是叶子节点

```c++
struct node {
    node* left, *right;
    int value;
    bool isLeaf() {
        return (left == nullptr && right == nullptr);
    }
    bool operator<(const node& that) { return this->value < that.value; }
    explicit node(int _value): value(_value) {
        left = right = nullptr;
    }
};
```

| 字段声明          | 字段功能       |
| ------------- | ---------- |
| node* left    | 表示树的左节点    |
| node *right   | 表示树的右节点    |
| bool isLeaf() | 表示节点是否是叶节点 |

### HuffmanTree

表示哈夫曼树

| 字段                                       | 功能                   | 是否公开    |
| ---------------------------------------- | -------------------- | ------- |
| node* root                               | 表示哈夫曼树的根             | private |
| node* buildHuffmanTree(std::vector\<int\>& nodes); | 根据vector构建哈夫曼树       | private |
| void clear_node(node* root)              | 清楚一个节点的所有子节点         | private |
| int getSumValue(node* root)              | 得到哈夫曼树的总权值(主要被以下的函数) | private |
| int getSumValue()                        | 得到哈夫曼树的总权值           | public  |

## 功能与实现

主题程序的逻辑

```c++
int main() {
    int node_times;
    cin >> node_times;
    vector<int> woods(node_times);
    for (int i = 0; i < node_times; ++i) {
        cin >> woods[i];
    }

    auto tree = HuffmanTree(woods);
    cout << tree.getSumValue();
    return 0;
}
```

1. 先把数据全部写到vector中
2. 根据vector, 建立`HuffmanTree`
3. 使用`tree.getSumValue()`

### 建立哈夫曼树

```c++
explicit HuffmanTree(std::vector<int>& lengths) { root = nullptr; buildHuffmanTree(lengths); }
```

以下逻辑建立哈夫曼树

```c++
node *HuffmanTree::buildHuffmanTree(std::vector<int> &nodes) {
    std::priority_queue<node*> pq;
    for(auto value: nodes) {
        pq.push(new node(value));
    }

    while (pq.size() != 1) {
        auto v1 = pq.top();
        pq.pop();
        auto v2 = pq.top();
        pq.pop();
        auto newnode = new node(v1->value + v2->value);
        newnode->left = v1;
        newnode->right = v2;
        pq.push(newnode);
    }

    root = pq.top();
    return root;
} 
```

1. 创建优先队列，并把所有的节点初始化成叶节点
2. 每次从优先队列中取出两个最小节点，合并成新的哈夫曼节点，加入其中
3. `pq.size == 1`时，处理完毕

## 运行

```
3
8 7 5
>>> 32
```

```
9
7 4 1 2 5 4 3 6 4
>>> 175
```

与所提供的答案相同