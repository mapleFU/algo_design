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


    int number;         //考号
    std::string name;  //考生姓名
    std::string gender;        //性别，F女M男
    int age;            //年龄
    std::string test_type;     //报考类别

public:
    Student(int i_num, const std::string&& i_name,
            const std::string&& i_gender, int i_age, const std::string&& i_test_type):
            number(i_num), name(i_name), gender(i_gender), age(i_age), test_type(i_test_type)
    {}
    Student() = delete;
//    Student(const Student& student):
//            age(student.age), number(student.number), gender(student.gender),
//            test_type(student.test_type), name(student.name)
//    {}
    Student(const Student& student) = default;
    Student(Student&& student) = default;
    Student&operator=(const Student& student) {
        age = student.age, number = student.number, gender = student.gender,
                test_type = student.test_type, name = student.name;
        return *this;
    }
};

struct StudentNode {

//    Student student;
    Student student;
    std::shared_ptr<StudentNode> next;
    // 注意构造函数
    StudentNode() = delete;
    /**
     * 原操作可能重复!
     */
    explicit StudentNode(const Student&& stu): student(stu) {}
    explicit StudentNode(Student&& stu): student(stu) {}
};

#endif //REGISTERATIONSYSTEM_STUDENT_H
