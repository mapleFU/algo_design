//
// Created by 付旭炜 on 2017/9/28.
//

#include "Student.h"

// output student data
std::ostream &operator<<(std::ostream &os, const Student &student) {
    os << student.number<< '\t' << student.name << '\t' << student.gender
       << '\t' << student.age << '\t' << student.test_type;
    return os;
}
