//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_SYSTEMVIEW_H
#define REGISTERATIONSYSTEM_SYSTEMVIEW_H

#include "StudentList.h"
#include "Commands/CommandManager.h"
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


#endif //REGISTERATIONSYSTEM_SYSTEMVIEW_H
