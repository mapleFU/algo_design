//
// Created by 付旭炜 on 2017/9/28.
// 一个表示命令的抽象基类
//

#ifndef REGISTERATIONSYSTEM_BASECOMMAND_H
#define REGISTERATIONSYSTEM_BASECOMMAND_H

#include "../StudentList.h"

class BaseCommand {
public:
    explicit BaseCommand(StudentList& studentList):student_list(studentList) {}
    virtual void excute() = 0;
    virtual void undo() = 0;

protected:
    StudentList& student_list;
    std::shared_ptr<StudentNode> lastnode = nullptr;
};

#endif //REGISTERATIONSYSTEM_BASECOMMAND_H
