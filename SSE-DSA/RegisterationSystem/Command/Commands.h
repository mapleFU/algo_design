//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_COMMANDS_H
#define REGISTERATIONSYSTEM_COMMANDS_H

#include "BaseCommand.h"

class InsertCommand: public BaseCommand {
public:
    explicit InsertCommand(StudentList& studentList): BaseCommand(studentList) {}
    void excute() override ;
    void undo() override;
};

class DeleteCommand: public BaseCommand {
public:
    explicit DeleteCommand(StudentList& studentList): BaseCommand(studentList) {delete_pos = 0;}
    void excute() override ;
    void undo() override;

private:
    int delete_pos;
};

class SelectCommand: public BaseCommand {
public:
    explicit SelectCommand(StudentList& studentList): BaseCommand(studentList) {}
    void excute() override ;
    void undo() override {}
};


class UpdateCommand: public BaseCommand {
public:
    explicit UpdateCommand(StudentList& studentList): BaseCommand(studentList) {}
    void excute() override ;
    void undo() override;

private:
    std::shared_ptr<Student> deleted_student;
};

class OutputCommand: public BaseCommand {
    explicit OutputCommand(StudentList& studentList): BaseCommand(studentList) {}
    void excute() override ;
    void undo() override {}

};
#endif //REGISTERATIONSYSTEM_COMMANDS_H
