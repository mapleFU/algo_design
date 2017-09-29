//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_STUDENTLIST_H
#define REGISTERATIONSYSTEM_STUDENTLIST_H

#include "Student.h"
#include <memory>

class StudentList {
public:
//    friend class InsertCommand;
    StudentList() {
        // 创建表头
        head = rear = std::make_shared<StudentNode>(Student(-1, "NULL", "n", 0, "NIL"));
    }
    std::shared_ptr<StudentNode> insert(int pos, const Student& new_student);
    std::shared_ptr<StudentNode> pop(int number, int *position = nullptr);
    std::shared_ptr<StudentNode> find(int number);
    void push_back(const Student& new_student);
    void push_back(Student&& new_student);
    void traverse(std::ostream& os = std::cout);
private:
    std::shared_ptr<StudentNode> head, rear;
//    void deleteNode(std::shared_ptr<StudentNode>);
//    void insertNodeToPosition(std::shared_ptr<StudentNode>);
};


#endif //REGISTERATIONSYSTEM_STUDENTLIST_H
