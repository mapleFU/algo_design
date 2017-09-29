#include <iostream>
#include "Student.h"
#include "StudentList.h"
#include "SystemView.h"

using namespace std;

void sys_view_test() {
    SystemView systemView(std::cin);
    systemView.run();
}

int main() {
    Student t(1, "fxw", "男", 19, "傻逼工程师");
    cout << t << endl;

    StudentNode node(t);
    cout << node.student << endl;

    if (node.next == nullptr) {
        cout << "Node from const t constructed" <<endl;
    }

    StudentNode node2(Student(2, "lyh", "男", 19, "全栈工程师"));

    cout << node2.student << endl;
//    StudentList l;
//    l.push_back(make_shared<Student>(t));
//    l.traverse(std::cout);

    // STUDENT LIST TEST
    StudentList studentList;
    studentList.push_back(node2.student);
    studentList.push_back(node.student);

    cout << "\nBelow is our traverse\n";
    studentList.traverse(std::cout);

    cout << "\nBelow is our traverse after add mmx\n";
    studentList.insert(3, Student(3, "mmx", "男", 19, "软件测试"));
    studentList.traverse();

    cout << "\nBelow is our traverse after remove fxw\n";
    studentList.pop(1);
    studentList.traverse();

    cout << "\nfind mmx" << endl;
    auto mmx = studentList.find(3);
    cout << mmx->student << endl;

    sys_view_test();
    return 0;
}