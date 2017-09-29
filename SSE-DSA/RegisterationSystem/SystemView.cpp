//
// Created by 付旭炜 on 2017/9/28.
//

#include "SystemView.h"

void cout_print(const char* s) {
    std::cout << s << '\n';
}

void SystemView::run() {
    init_sys();
    cout_print("请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，"
                       "5为统计，0为取消操作）");
    while (true) {
        ask_operation();
    }
}


// TODO: find goo value to return
bool SystemView::init_sys() {
    cout_print("请输入考生人数");
    int size;
    os >> size;

    // TODO: 输入验证？
    int i_num;
    std::string i_name;
    std::string i_gender;
    int i_age;
    std::string i_test_type;
    cout_print("请依次输入考生的考号 姓名 性别 年龄和报考类别");

    // TODO: 右值引用
    for (int i = 0; i < size; ++i) {

        os >> i_num >> i_name >> i_gender >> i_age >> i_test_type;
        student_list.push_back(Student(i_num, std::move(i_name), std::move(i_gender), i_age,
                                       std::move(i_test_type)));
    }

    student_list.traverse(std::cout);
    return true;
}

// TODO: find good value to return
bool SystemView::ask_operation() {
    cout_print("请选择您要进行的操作: ");
    int code;
    os >> code;
    commad_manager->excute(code);
    return true;
}
