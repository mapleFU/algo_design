////
// Created by 付旭炜 on 2017/9/28.
//

#include "StudentList.h"

void StudentList::push_back(const Student& new_student) {
    auto new_node = std::make_shared<StudentNode>(new_student);
    // TODO: if new node is nullptr
    rear->next = new_node;
    rear = new_node;
}

void StudentList::push_back(Student &&new_student) {
    auto new_node = std::make_shared<StudentNode>(new_student);
    // TODO: if new node is nullptr
    rear->next = new_node;
    rear = new_node;
}

/**
 *
 * @param number
 * @return the node of the student
 * return nullptr if can't find
 */
std::shared_ptr<StudentNode> StudentList::find(int number) {
    std::shared_ptr<StudentNode> ptr = head->next;
    // if no student
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    }
    while (ptr && ptr->student.number != number) ptr = ptr->next;
    return ptr;
}

std::shared_ptr<StudentNode> StudentList::pop(int number, int *position) {
    int cur_pos = 0;
    auto ptr = head->next;
    // if no student
    if (ptr == nullptr) {
        std::cout << "NO STUDENT!" << std::endl;
        return nullptr;
    }

    // pre is the pre of it
    std::shared_ptr<StudentNode> pre = head;
    while (ptr && ptr->student.number != number) {
        ++cur_pos;
        pre = ptr;
        ptr = ptr->next;
    }
    // can't find
    if (ptr == nullptr) {
        std::cout << "NO THIS STUDENT!" << std::endl;
        position = nullptr;
        return nullptr;
    } else if (ptr == rear) {
        rear = pre;
    }
    pre->next = ptr->next;
    // 需要提供位置信息
    if (position != nullptr) {
        *position = cur_pos;
    }

    return ptr;
}

std::shared_ptr<StudentNode> StudentList::insert(int pos, const Student& new_student) {
    int cur_pos = 1;        //1表示最开始
    auto ptr = head;
    while (cur_pos++ < pos && ptr) ptr = ptr->next;

    if (ptr == nullptr) {
        std::cout << "你确定么，太后面了！" << std::endl;
        return nullptr;
    } else {
        auto node = std::make_shared<StudentNode>(new_student);
        node->next = ptr->next;
        ptr->next = node;
        return node;
    }
}

void StudentList::traverse(std::ostream& os) {
    auto ptr = head->next;
    while (ptr) {
        os << ptr->student << '\n';
        ptr = ptr->next;
    }
}




//void StudentList::deleteNode(std::shared_ptr<StudentNode> ptr_delete) {
//    auto ptr = head->next;
//    // if no student
//    if (ptr == nullptr) {
//        std::cout << "NO STUDENT!" << std::endl;
//        return;
//    }
//
//    std::shared_ptr<StudentNode> pre = head;
//    while (ptr && ptr ) {
//        pre = ptr;
//        ptr = ptr->next;
//    }
//    // can't find
//    if (ptr == nullptr) {
//        std::cout << "Delete Fail!" << std::endl;
//        return;
//    } else if (ptr == rear) {
//        rear = pre;
//    }
//    pre->next = ptr->next;
//}
//
//// todo implete it
//void StudentList::insertNodeToPosition(std::shared_ptr<StudentNode>) {
//
//}
