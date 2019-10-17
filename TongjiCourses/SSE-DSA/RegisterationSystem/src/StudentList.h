//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_STUDENTLIST_H
#define REGISTERATIONSYSTEM_STUDENTLIST_H

#include "Student.h"
#include <memory>

class StudentList {
public:
    friend class InsertCommand;
    StudentList() = default;
    std::shared_ptr<StudentNode> insert(int pos, std::shared_ptr<Student> new_student);
    std::shared_ptr<StudentNode> pop(int number);
    std::shared_ptr<StudentNode> find(int number) const ;
    void push_back(std::shared_ptr<Student>&& new_student);
    void traverse(std::ostream& os);
    // 根据外界输入做扩张
    void append_by_input(std::istream& is=std::cin);
private:
    std::shared_ptr<StudentNode> head, rear;

    void deleteNode(std::shared_ptr<StudentNode>);
    void insertNodeToPosition(std::shared_ptr<StudentNode>);
};


#endif //REGISTERATIONSYSTEM_STUDENTLIST_H
