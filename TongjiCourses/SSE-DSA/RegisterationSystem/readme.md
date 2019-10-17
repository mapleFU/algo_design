# 考试报名系统
在这个系统中，本人为了能够模块化的完成这个任务，采用了设计模式-命令模式，
并且用了类似MVC的模块设计，用SystemView处理外部信息，用Command处理命令，
StudentList作为基础模块
## 分析
### 背景和功能分析
根据考生给出的材料，学生应当具有如下信息:
#### 考生信息
1. 准考证号
2. 姓名
3. 性别
4. 年龄
5. 报考类别

有了以上这些信息，才能更好的描述出一个学生的基本情况，

对于整个系统而言，他们应当具备的功能有：
#### 系统功能
1. 输入考生信息
2. 输出考生信息
3. 查询考生信息
4. 添加考生信息
5. 修改考生信息
6. 删除考生信息
7. 撤销上述操作

## 设计
### testdata
给出的测试数据，用来进行模块功能的基础测试
### readme
类型的基础说明
### main
整体程序的入口
### src/
代码实现的目录
#### src/Student
学生(Student)和学生节点(StudentNode)的设计

Student、StudentNode信息对StudentList类是可以访问的

##### Student
目录下的结构体，拥有上述说明表示学生信息的字段
```doxygen
int number = 0;         //考号
std::string name;  //考生姓名
std::string gender;        //性别，F女M男
int age = 0;            //年龄
std::string test_type;     //报考类别
```
##### StudentNode
对Student进行了一层封装，表示在StudentList的Student节点

拥有next字段和STUDENT, 分别表示存储的下一个节点和存储的学生的信息
```doxygen
std::shared_ptr<Student> student;
std::shared_ptr<StudentNode> next;
```

#### src/StudentList
由StudentNode构成的链表，用来存储学生的信息

支持遍历(traverse), 查找(find), 删除(delete)操作

Public
```doxygen
// 根据给出的学生和位置插入学生，返回被插入的节点
std::shared_ptr<StudentNode> insert(int pos, std::shared_ptr<Student> new_student);
// 根据给出的序号删除学生，返回被删除的节点
std::shared_ptr<StudentNode> pop(int number);
// 根据给出的序号查找学生，找不到则返回NULLPTR
std::shared_ptr<StudentNode> find(int number) const ;
```
PRIVATE
```doxygen
// 直接吧给出的学生插入到最后
void push_back(std::shared_ptr<Student>&& new_student);
// 根据给出的函数来遍历学生劣币
void traverse(std::ostream& os);
// 根据外界输入做扩张
void append_by_input(std::istream& is=std::cin);
```
#### src/SystemView
与main交互的接口，负责与用户进行对话，
可以调用COMMANDS且只有它能访问Commands
```doxygen
class SystemView {
public:
    explicit SystemView(std::istream& in_os):os(in_os) {
        student_list = StudentList();
        commad_manager = std::make_shared<CommandManager>(student_list);
    }
    void run();             //主函数

    bool init_sys();        //初始化系统
    bool ask_operation();   //询问操作


private:
    // 存储学生信息的链表
    StudentList student_list;
    // 对应的输入流
    std::istream& os;
    // 对应的命令处理器
    std::shared_ptr<CommandManager> commad_manager;

};
```
该类用`bool init_sys()`初始化系统

用`bool ask_operation();`在一个循环中不断循环询问用户进行的操作种类

并用`void run()`将上面两个过程封装。
### src/Commands/
命令类的目录，负责执行用户发送过来的操作

**该部分用CommandManager与外界沟通，其他部分外界不可见**
#### src/Commands/BaseCommand
基础的命令类，负责与用户交互

该类是一个抽象基类，实现了以下两个接口:
```doxygen
// 操作相关的命令
virtual void excute() = 0;
// 撤销进行的操作
virtual void undo() = 0;
```
这个类保存了生成的StudentList的引用，可以直接影响到StudentList并且不会对内存由太多额外开销
```doxygen
protected:
    StudentList& student_list;
    std::shared_ptr<StudentNode> lastnode = nullptr;
```
#### src/Commands/Commands
这个目录下的类都是BaseCommand的子类，定义了具体的操作

1. insertCommand:执行插入的类
2. deleteCommand:删除的类
3. selectCommand:查找的类
4. updateCommand:更新信息的类
5. outputCommand:输出的类

#### src/Commands/CommandManager
负责管理Command命令的类，作为整体命令管理的接口。
字段：
```doxygen
explicit CommandManager(StudentList& student_list) {
        auto insertCommand = std::make_shared<InsertCommand>(student_list);
        auto deleteCommand = std::make_shared<DeleteCommand>(student_list);
        auto selectCommand = std::make_shared<SelectCommand>(student_list);
        auto updateCommand = std::make_shared<UpdateCommand>(student_list);
        auto outputCommand = std::make_shared<OutputCommand>(student_list);
        code_to_operator[1] = insertCommand;
        code_to_operator[2] = deleteCommand;
        code_to_operator[3] = selectCommand;
        code_to_operator[4] = updateCommand;
        code_to_operator[5] = outputCommand;
    }
```

``void excute(int code)``负责处理相应数字对应的逻辑

``void undo()`` 负责撤销上一部的处理

这个类在内部维护了一个<操作数, 命令对象>的表，并用这张表处理对应数据，并且拥有表明上一部操作对象的字段
```doxygen
private:
    std::map<int, std::shared_ptr<BaseCommand>> code_to_operator;
    std::shared_ptr<BaseCommand> precommand = nullptr;
```


## 整体逻辑
1. 进入main
2. 生成SystemView对象, 初始化学生信息
3. 调用SystemView.run(), 让查询-输出操作这个过程不停的进行下去

## 功能实现与测试
### 插入功能
在InsertCommand中调用了StudentList类的Insert操作

``student_list.insert(position, std::make_shared<Student>(new_student));``

```doxygen
std::shared_ptr<StudentNode> StudentList::insert(int pos, std::shared_ptr<Student> new_student) {
    int cur_pos = 1;        //1表示最开始
    // 自己添加一个伪表头
    auto tmp_head = std::make_shared<StudentNode>();
    tmp_head->next = head;
    auto ptr = tmp_head;
    while (cur_pos++ < pos && ptr) ptr = ptr->next;

    if (ptr == nullptr) {
        std::cout << "你确定么，太后面了！" << std::endl;
        return nullptr;
    } else {
        auto node = std::make_shared<StudentNode>(new_student);
        node->next = ptr->next;
        ptr->next = node;
        // update data
        // 如果HEAD插入，需要更改，这里直接更改
        head = tmp_head->next;
        // rear本身的更改
        if (rear->next != nullptr) rear = rear->next;

        return node;
    }
}
```
* 边界检测
```doxygen
    if (ptr == nullptr) {
        std::cout << "你确定么，太后面了！" << std::endl;
        return nullptr;
    }
```
如果过于偏移，则会提示插入的位置过于后方，不经心任何操作而且返回NULL

* 自身信息维护
```doxygen
// update data
// 如果HEAD插入，需要更改，这里直接更改
head = tmp_head->next;
// rear本身的更改
if (rear->next != nullptr) rear = rear->next;
```
如果插入的信息替换掉了HEAD, 就更换HEAD
替换叫了REAR就替换rear

* 对空表等情况的处理
``// 自己添加一个伪表头
      auto tmp_head = std::make_shared<StudentNode>();``
在处理表信息的时候会添加一个辅助的表头, 这样可以伪装成有表头的链表

#### 测试用例
```
  1	stu1	女	20	软件设计师
  2	stu2	男	21	软件开发师
  3	stu3	男	20	软件设计师
  请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）
  请选择您要进行的操作: 
  1
  请输入你要插入的考生的位置
  4
  请输入你的1. 准考证号 2. 姓名 3. 性别 4. 年龄 5. 报考类别
  4 stu4 女 21 软件测试师
```
信息成功被修改插入

### 删除功能
在DeleteManager中调用了StudentList的delete来处理信息
```doxygen
lastnode = student_list.pop(number);
std::cout << "你所删除的考生的信息是: " << *(lastnode->student) << '\n';
```
```doxygen
void StudentList::deleteNode(std::shared_ptr<StudentNode> ptr_delete) {
    // if no student
    if (head == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return;
    }

    // 临时表头
    auto sen = std::make_shared<StudentNode>();
    sen->next = head;
    auto ptr = sen->next;

    std::shared_ptr<StudentNode> pre = sen;
    while (ptr && ptr->student != ptr_delete->student ) {
        pre = ptr;
        ptr = ptr->next;
    }
    // can't find
    if (ptr == nullptr) {
        std::cout << "Delete Fail!" << std::endl;
        return;
    } else if (ptr == rear) {
        rear = pre;
    } else if (ptr == head) {
        // 切换HEAD
        head = head->next;
    }
    pre->next = ptr->next;
}
```

* 边界情况处理
和插入一样，准备了伪表头, 同时处理了HEAD=NULL的情况
```doxygen
   // if no student
    if (head == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return;
    }

    // 临时表头
    auto sen = std::make_shared<StudentNode>();
    sen->next = head;
    auto ptr = sen->next;
```
* 命中失败
```doxygen
if (ptr == nullptr) {
        std::cout << "Delete Fail!" << std::endl;
        return;
    } 
```
查找失败时，find会返回NULL,根据这个来处理

#### 示例
```doxygen
1 stu1 女 20 软件设计师
2 stu2 男 21 软件开发师
3 stu3 男 20 软件设计师
1	stu1	女	20	软件设计师
2	stu2	男	21	软件开发师
3	stu3	男	20	软件设计师
请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，5为统计，0为取消操作）
请选择您要进行的操作: 
2
请选择你要删除的考号
2
你所删除的考生的信息是: 2	stu2	男	21	软件开发师
```
删除成功

### 查找
顺序查找，查看匹配信息即可,对于未查找命中返回NULLPTR
```doxygen
std::shared_ptr<StudentNode> StudentList::find(int number) const {
//    std::shared_ptr<StudentNode> ptr = head->next;
    std::shared_ptr<StudentNode> ptr = head;
    // if no student
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    }
    while (ptr && ptr->student->number != number) ptr = ptr->next;
    return ptr;
}
```
#### 示例
```doxygen
你所删除的考生的信息是: 2	stu2	男	21	软件开发师
请选择您要进行的操作: 
3
请选择你要查找的考号
2
这个学生不存在，查找失败
请选择您要进行的操作: 
3
请选择你要查找的考号
3
你所查找的考生的信息是: 3	stu3	男	20	软件设计师
```

### 更新
查找对应的节点，没有完成则未命中返回，否则更新节点的STUDENT字段
```doxygen
void UpdateCommand::excute() {
    std::cout << "请选择你要更新的考号\n";
    int number;
    std::cin >> number;
    auto curnode = student_list.find(number);
    if (curnode == nullptr) {
        std::cout << "找不到这个成员" << '\n';
    }
    std::cout << "你所查找的考生的信息是: " << *(curnode->student) << '\n';

    std::cout << "请输入新的：1. 准考证号 "
            "2. 姓名 "
            "3. 性别 "
            "4. 年龄 "
            "5. 报考类别\n";
    int i_num;
    std::string i_name;
    std::string i_gender;
    int i_age;
    std::string i_test_type;
    // TODO: 右值引用
    std::cin >> i_num >> i_name >> i_gender >> i_age >> i_test_type;
    auto newnode = std::make_shared<Student>(i_num, i_name, i_gender, i_age, i_test_type);
    deleted_node = curnode->student;
    curnode->student = newnode;
    lastnode = curnode;
}
```
