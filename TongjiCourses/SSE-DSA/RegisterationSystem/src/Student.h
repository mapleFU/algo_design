//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef REGISTERATIONSYSTEM_STUDENT_H
#define REGISTERATIONSYSTEM_STUDENT_H

#include <string>
#include <iostream>
#include <memory>

class Student;


// TODO:find out if we need wstring?
class Student {
private:
    friend class StudentList;

    friend std::ostream& operator<<(std::ostream& os, const Student& student);


    int number = 0;         //考号
    std::string name;  //考生姓名
    std::string gender;        //性别，F女M男
    int age = 0;            //年龄
    std::string test_type;     //报考类别

public:
    Student(int i_num, const std::string& i_name,
            const std::string& i_gender, int i_age, const std::string& i_test_type):
            number(i_num), name(i_name), gender(i_gender), age(i_age), test_type(i_test_type)
    {}
    Student() = default;
    Student(const Student& student) = default;
    Student(Student && student) = default;

};

struct StudentNode {

    std::shared_ptr<Student> student;
    std::shared_ptr<StudentNode> next;
    StudentNode(): student(nullptr), next(nullptr) {}
    StudentNode(const std::shared_ptr<Student>& stu): student(stu), next(nullptr) {}
};

#endif //REGISTERATIONSYSTEM_STUDENT_H
