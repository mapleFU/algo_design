//
// Created by 付旭炜 on 2019/3/24.
//

#ifndef LEETCODE_C_LINK_LIST_H
#define LEETCODE_C_LINK_LIST_H

#include <initializer_list>
#include <iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

ListNode* make_list(std::initializer_list<int > val_list) {
    ListNode* head = nullptr;
    ListNode* tail = nullptr;
    for (int value: val_list) {
        ListNode* node = new ListNode(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            tail = node;
        }
    }
    return head;
}

void print_list(ListNode* head) {
    ListNode* node = head;
    std::cout << '[';
    while (node != nullptr) {
        std::cout << node->val << ' ';
        node = node->next;
    }
    std::cout << ']';
    std::cout << '\n';
}

bool list_checker(ListNode* list1, std::initializer_list<int > val_list) {
    auto list2 = make_list(val_list);
    while (true) {
        bool end_list1 = list1 == nullptr;
        bool end_list2 = list2 == nullptr;

        if (end_list1 && end_list2) {
            return true;
        }
        if (end_list1 || end_list2) {
            return false;
        }
        // all not end
        if (list1->val == list2->val) {
            list1 = list1->next;
            list2 = list2->next;
        } else {
            return false;
        }
    }
}


#endif //LEETCODE_C_LINK_LIST_H
