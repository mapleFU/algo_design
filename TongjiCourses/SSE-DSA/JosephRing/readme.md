# 约瑟夫生死游戏模拟
## 背景分析
模拟约瑟夫环的游戏，可以直接用链表模拟环，进行模拟操作；也可以用数学方法模拟约瑟夫环，进行排错。
## 设计
### 输入
我们要构造约瑟夫环需要四个整数信息
1. 总人数N
2. 开始位置S
3. 死亡数字M
4. 剩余人数R

### 基础类设计如下
以下是指向节点的字段
```doxygen
node* curnode;
node*prenode;
node* min;
```
删除一个节点需要知道它之前的节点的信息，这里构造环的时候准备了 curnode prenode 用来构造目前指向的指针和它在环中的前驱元

MIN是指向最小元素的指针，一开始指向第一个人，随着删除它会慢慢向后移动到下一个元素。由于本身是有序的，这样能够保证每次移动都保持最小。

### 获取输入和构造功能实现如下

首先需要得到这四个数据的输入并且排错，这里为了高度抽象，编写了一个模版函数
```doxygen
template <typename ValueType>
void get_input(ValueType& inputed, function<bool(const ValueType& value)> judge_func,
               const std::string& hint, const std::string& error);
```
input是输入对象的引用，judge_func是判断输入是否合理的函数，hint是提示语，error是如果不满足函数要求的报错。函数使用如下。

```doxygen
get_input<int>(tourists,
              [](const int&value)->bool { return value > 0;},
              "请输入生死游戏的总人数N：",
              "人数过少，游戏无法进行");
```
即：输入旅客数量，且希望旅客数量满足大于0，并打印提示。

以下针对边界输入测试：
```doxygen
请输入生死游戏的总人数N：
-3
人数过少，游戏无法进行
请输入生死游戏的总人数N：
30
请输入游戏的开始位置S：
35
开始的位置应该不小于0且大于旅客数
请输入游戏的开始位置S：
-5
开始的位置应该不小于0且大于旅客数
请输入游戏的开始位置S：
1
请输入死亡数字M：
9
请输入剩余人数R：
-5
剩余人数应当大于0
```

### 约瑟夫环构建与运行
根据前提，构建与运行时约瑟夫环的输入已经正确。

```doxygen
class JosephRing {
public:
    JosephRing(int tourist, int start, int mod, int remains) {
        dead = 0;
        min = prenode = curnode = nullptr;
        this->remains = remains;
        this->tourist = tourist;
        this->start = start;
        this->mod = mod;
        makeList();
    }
    
    // 整体运行
    void run();
    // 现实剩余者
    void show_remains();
    ~JosephRing();
private:
    int tourist, start, mod, remains;
    int dead;   //死亡数目
    // 根据信息构造环状链表
    // 只应该在构造函数使用
    void makeList();
    // 杀一个人
    int die_one();
    node* curnode, *prenode;
    node* min;
};
```
用环状链表储存环，并且有MAKELIST()等创建，使用的接口。

#### 死人模拟具体实现如下
```doxygen
int JosephRing::die_one() {
    int count = 1;
    while (count < mod) {
        ++count;
        prenode = prenode->next;
        curnode = curnode->next;
    }
    if (prenode == curnode) {
        // pass
    }
    if (curnode == min) {
        min = min->next;
    }
    std::cout << "第" << ++dead << "个死者的位置是\t" << curnode->index << '\n';
    auto tmp = curnode->next;
    delete curnode;
    curnode = tmp;
    prenode->next = curnode;
//    ++dead;
}
```
模拟前进计数并且删除，同时更改MIN指针(即指向最小序号)。

总模拟只要不停模拟DIE_ONE即可

### 整体模拟实现如下
```doxygen
void JosephRing::run() {
    while (dead < tourist - remains) {
        die_one();
    }
}
```
在人数小于需要死亡的人数时，不停模拟'死亡一个人'