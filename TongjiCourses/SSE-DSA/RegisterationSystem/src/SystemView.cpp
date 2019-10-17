//
// Created by 付旭炜 on 2017/9/28.
//

#include "SystemView.h"

inline void cout_print(const char* s) {
    std::cout << s << '\n';
}

void SystemView::run() {
    init_sys();
    cout_print("请选择您要进行的操作（1为插入，2为删除，3为查找，4为修改，"
                       "5为统计，6为退出，0为取消上一步操作）");

    bool inf_loop(true);        // 是否一直循环
    while (inf_loop) {
        inf_loop = ask_operation();
    }
    cout_print("欢迎再次使用我们的系统，再见！");
}


// TODO: find goo value to return
bool SystemView::init_sys() {
    cout_print("请输入考生人数");
    int size;
    os >> size;

    // TODO: 输入验证？
    cout_print("请依次输入考生的1.考号 2.姓名 3.姓名 4.年龄 5.已经报考类别");

    // TODO: 右值引用
    // add student via input
    for (int i = 0; i < size; ++i) {
        // 扩张
        student_list.append_by_input();
    }

    student_list.traverse(std::cout);
    return true;
}

// TODO: find good value to return
bool SystemView::ask_operation() {
    cout_print("请选择您要进行的操作: ");
    int code;
    os >> code;
    if (code == 6) {
        return false;
    }
    commad_manager->excute(code);
    return true;
}
