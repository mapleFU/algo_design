//
// Created by 付旭炜 on 2017/9/28.
//

#include "StudentList.h"

void StudentList::push_back(std::shared_ptr<Student> &&new_student) {

    auto new_node = std::make_shared<StudentNode>(new_student);
    // TODO: if new node is nullptr
    if (rear) {
        rear->next = new_node;
        rear = new_node;
    } else {
        head = rear = new_node;
    }
}

/**
 *
 * @param number
 * @return the node of the student
 * return nullptr if can't find
 */
std::shared_ptr<StudentNode> StudentList::find(int number) const {
//    std::shared_ptr<StudentNode> ptr = head->next;
    std::shared_ptr<StudentNode> ptr = head;
    // if no student
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    }
    while (ptr && ptr->student->number != number) ptr = ptr->next;
    return ptr;
}

std::shared_ptr<StudentNode> StudentList::pop(int number) {
//    auto ptr = head->next;
    auto ptr = head;
    // if no student
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    }

    // pre is the pre of it
    std::shared_ptr<StudentNode> pre = head;
    while (ptr && ptr->student->number != number) {
        pre = ptr;
        ptr = ptr->next;
    }
    // can't find
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    } else if (ptr == rear) {
        rear = pre;
    }
    pre->next = ptr->next;
    return ptr;
}

std::shared_ptr<StudentNode> StudentList::insert(int pos, std::shared_ptr<Student> new_student) {
    int cur_pos = 1;        //1表示最开始
    // 自己添加一个伪表头
    auto tmp_head = std::make_shared<StudentNode>();
    tmp_head->next = head;
    auto ptr = tmp_head;
    while (cur_pos++ < pos && ptr) ptr = ptr->next;

    if (ptr == nullptr) {
        std::cout << "你确定么，太后面了！" << std::endl;
        return nullptr;
    } else {
        auto node = std::make_shared<StudentNode>(new_student);
        node->next = ptr->next;
        ptr->next = node;
        // update data
        // 如果HEAD插入，需要更改，这里直接更改
        head = tmp_head->next;
        // rear本身的更改
        if (rear->next != nullptr) rear = rear->next;

        return node;
    }
}

void StudentList::traverse(std::ostream& os) {
    auto ptr = head;
    while (ptr) {
         os << *(ptr->student) << '\n';
        ptr = ptr->next;
    }
}

void StudentList::deleteNode(std::shared_ptr<StudentNode> ptr_delete) {
    // if no student
    if (head == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return;
    }

    // 临时表头
    auto sen = std::make_shared<StudentNode>();
    sen->next = head;
    auto ptr = sen->next;

    std::shared_ptr<StudentNode> pre = sen;
    while (ptr && ptr->student != ptr_delete->student ) {
        pre = ptr;
        ptr = ptr->next;
    }
    // can't find
    if (ptr == nullptr) {
        std::cout << "Delete Fail!" << std::endl;
        return;
    } else if (ptr == rear) {
        rear = pre;
    } else if (ptr == head) {
        // 切换HEAD
        head = head->next;
    }
    pre->next = ptr->next;
}

// todo implete it
void StudentList::insertNodeToPosition(std::shared_ptr<StudentNode>) {

}

void StudentList::append_by_input(std::istream &is) {
    int i_num;
    std::string i_name;
    std::string i_gender;
    int i_age;
    std::string i_test_type;
    auto ptr_student = std::make_shared<Student>();
    is >> i_num >> i_name >> i_gender >> i_age >> i_test_type;
    push_back(std::make_shared<Student>(i_num, i_name, i_gender, i_age, i_test_type));
}
