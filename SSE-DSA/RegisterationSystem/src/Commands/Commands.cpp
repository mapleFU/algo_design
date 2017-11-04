//
// Created by 付旭炜 on 2017/9/28.
//

#include "Commands.h"

void InsertCommand::excute() {
    std::cout << "请输入你要插入的考生的位置\n";
    int position;
    std::cin >> position;
    std::cout << "请输入你的1. 准考证号 "
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
    auto new_student = Student(i_num, std::move(i_name),
                               std::move(i_gender), i_age, std::move(i_test_type));
    lastnode = student_list.insert(position, std::make_shared<Student>(new_student));

}

void InsertCommand::undo() {
    student_list.deleteNode(lastnode);
}

void DeleteCommand::excute() {
    std::cout << "请选择你要删除的考号\n";
    int number;
    std::cin >> number;
    lastnode = student_list.pop(number);
    if (lastnode == nullptr) {
        std::cout << "删除失败\n";
        return;
    }
    std::cout << "你所删除的考生的信息是: " << *(lastnode->student) << '\n';
}

void DeleteCommand::undo() {

}

void SelectCommand::excute() {
    std::cout << "请选择你要查找的考号\n";
    int number;
    std::cin >> number;
    lastnode = student_list.find(number);
    if (lastnode == nullptr) {
        std::cout << "这个学生不存在，查找失败\n";
        return;
    }
    std::cout << "你所查找的考生的信息是: " << *(lastnode->student) << '\n';
}

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

void UpdateCommand::undo() {
    lastnode->student = deleted_node;
}

void OutputCommand::excute() {
    student_list.traverse(std::cout);
}
