# 家谱管理系统
## 分析
### 背景分析
家谱是一种以表谱形式，记载一个以血缘关系为主体的家族世袭繁衍和重要任务事迹的特殊图书体裁。家谱是中国特有的文化遗产，是中华民族的三大文献（国史，地志，族谱）之一，属于珍贵的人文资料，对于历史学，民俗学，人口学，社会学和经济学的深入研究，均有其不可替代的独特功能。本项目兑对家谱管理进行简单的模拟，以实现查看祖先和子孙个人信息，插入家族成员，删除家族成员的功能。

### 项目功能要求
1. 完成对于家谱的基本的创建操作
2. 对家谱支持正常的增查删改
3. 对用户进行提示，支持在正常和异常状态下进行提示

## 设计
### 数据结构设计
数据结构设计整体采用，带兄弟、子节点的二叉树
#### Member
表示成员的类，维护着子节点指针

| 类型            |    字段名     |    功能    |
| ------------- | :--------: | :------: |
| const Member* | FmailyTree | 保存自己的父节点 |
| std::string   |    name    | 保存成员的姓名  |
| Member*       |  siblings  |  保存兄弟指针  |
| Member*       |   childs   | 保存儿子的指针  |

| 函数声明                                     |      功能       | 是否公开(PUBLIC) |
| ---------------------------------------- | :-----------: | :----------: |
| inline bool isLeaf()                     | 显示一个成员是否是父节点  |      非       |
| void change_name(const std::string& new_name) |    给一个成员更名    |      是       |
| Member* add_child(const std::string&name) | 给一个成员添加第一个子节点 |      是       |
| void clear_childs_recursive()            | 递归删除一个节点的子节点  |      是       |

#### FamilyTree
表示整个家谱的类，拥有增查删改的功能

| 类型      |   字段名    |    功能    |
| ------- | :------: | :------: |
| Member* | ancestor | 保存整棵树的祖先 |

| 函数声明                                     |                功能                | 是否公开(PUBLIC) |
| ---------------------------------------- | :------------------------------: | :----------: |
| Member* find(Member* member_ptr, const std::string&name) | 根据给出的根节点和姓名，查找目标节点，不存在则返回nullptr |      否       |
| void add_child(Member* father, const std::string& name) |       给出父节点和姓名，然后在父节点添加子节点       |      否       |
| void show_family(Member* father)         |          根据给出的父节点，展示整棵树          |      否       |
| void clear_children_recursively(Member* father) |            递归删除所有子节点             |      否       |
| void create_family()                     |            直接创建整个家庭树             |      是       |
| void add_children()                      |             调动添加子节点              |      是       |
| void modify_name()                       |             修改节点的姓名              |      是       |
| void break_family()                      |              解散单个家庭              |      是       |
| static FmailyTree* build_family_tree()   |          STATIC的对象建立家庭树          |      是       |

## 功能与实现
### 初始化族谱
创建功能调用`FmailyTree::build_family_tree()`来实现

```doxygen
cout << WELCOME;
auto tree = FmailyTree::build_family_tree();
```

```doxygen
FmailyTree *FmailyTree::build_family_tree() {
    std::string ances_name;
    std::cout << "请输入祖先的姓名\n";
    std::cin >> ances_name;
    auto family_tree = new FmailyTree(ances_name);
    std::cout << "此家谱的祖先是" << family_tree->ancestor->name << '\n';
    return family_tree;
}
```
提示用户输入祖先姓名，并根据祖先的名称来创建族谱。

### 创建家庭
```C++
void FmailyTree::create_family() {
    std::string father_name; // 祖先的名称
    std::cout << "选择要建立家族的人的姓名\n";
    std::cin >> father_name;

//    auto father_ptr = ancestor->find(father_name);
    auto father_ptr = find(ancestor, father_name);
    // father_ptr情况分支处理
    if (father_ptr == nullptr) {
        std::cout << "要创建家庭的成员不存在" << std::endl;
        return;
    } else if (father_ptr->childs) {
        // 已经存在家庭
        std::cout << father_ptr->name << "已经存在家庭\n";
    }

    std::cout << "请输入" <<  father_name << "的子女人数";
    int family_members;
    std::cin >> family_members;

    std::cout << "依次输入儿女姓名: ";
    std::vector<std::string> childs;
    for (int i = 0; i < family_members; ++i) {
        std::string cur_name;
        std::cin >> cur_name;
        father_ptr->add_child(cur_name);
        childs.push_back(cur_name);
    }

    // output
    std::cout << father_name <<"的子女是：";
    for (const auto&s: childs) {
        std::cout << s << ' ';
    }
    std::cout << '\n';
}
```
逻辑如下:
1. 指定需要创建家庭的人，并对其进行搜索, 不存在则返回此人不存在; 若此人已经存在家庭，则打印“此人已经存在家庭”，并返回。
2. 如果此人可以创建家庭，提示用户输入需要的儿女个数，并提示用户依次输入儿女姓名
3. 用户输入后，遍历输出。

用例如下

```
请选择接下来要进行的操作: A
选择要建立家族的人的姓名
P0
请输入P0的子女人数2
依次输入儿女姓名: P1 P2
P0的子女是：P1 P2 
P0 
P2 P1 
```

### 添加家庭成员

关键代码逻辑

```c++
void FmailyTree::add_children() {
    std::string father_name;
    std::cout << "请选择要添加儿女的人的姓名\n";
    std::cin >> father_name;

    auto father_ptr = find(ancestor, father_name);
    // father_ptr情况分支处理
    if (father_ptr == nullptr) {
        std::cout << "要添加子女的成员不存在" << std::endl;
        return;
    }

    std::cout << "请填入" <<  father_name << "新添加的儿女的姓名\n";
    std::string new_child;
    std::cin >> new_child;
    father_ptr->add_child(new_child);
    std::cout << father_name << "新添加的儿女的姓名是" << new_child;
}
```

1. 提示用户输入需要添加儿女者姓名，并在树中查找
2. 若是用户的输入不存在，则直接打印其不存在，并返回
3. 若是用户的输入存在，则让其打印需要输入的人的姓名，并且加入



用例测试如下

```
请选择接下来要进行的操作: B
请选择要添加儿女的人的姓名 P2
请填入P2新添加的儿女的姓名 P21
P2新添加的儿女的姓名是P21
P0 
P2 P1 
P21 
```



### 摧毁家庭

代码实现如下

```c++
void FmailyTree::break_family() {
    std::string processing_name;
    std::cout << "请输入要解散家族的人的姓名";
    std::cin >> processing_name;
    std::cout << "要解散家族的人的姓名是: " << processing_name;

    auto processing_ptr = find(ancestor, processing_name);
    if (processing_ptr == nullptr) {
        std::cout << "要解散家庭的成员不存在" << std::endl;
        return;
    }

    if (processing_ptr->childs == nullptr) {
        std::cout << "这个可怜的孩子已经没家庭了，请放过他吧\n";
        return;
    }
#ifdef FAMILY_TREE_DEBUG
    show_family();
#endif
    processing_ptr->clear_childs_recursive();
}

```

代码实现逻辑

1. 提示用户输入需要解散家庭的人的名称，并根据用户输入的名称查找。如果成员不存在则提示不存在并返回；如果成员没有儿子，则提醒并返回
2. 如果其有子节点(子女)，递归删除其所有的子节点，并返回。



#### 用例测试

```
请选择接下来要进行的操作: C
请输入要解散家族的人的姓名P2
要解散家族的人的姓名是: P2P0 
P2 P1 
P21 

P0 
P2 P1 
```

如其显示，P2子女都被我杀光了

### 成员更名

```c++
void FmailyTree::modify_name() {
    std::cout << "请输入要更名的人目前的姓名\n";
    std::string processing_name;
    std::cin >> processing_name;
    auto processing_ptr = find(ancestor, processing_name);
    if (processing_ptr == nullptr) {
        std::cout << "要更名的成员不存在" << std::endl;
        return;
    }
    std::cout << "请输入要更名的人("<<processing_name<<")目前的姓名\n";
    std::string new_name;
    std::cin >> new_name;

    std::cout <<processing_name<<"已经更名为"<<new_name;
    processing_ptr->change_name(new_name);
}
```

1. 提示用户输入需要更名者的姓名，若不存在则做出提示
2. 根据用户输入的新姓名，调用节点的`change_name`方法，更改成员的名称。