//
// Created by 付旭炜 on 2017/9/28.
//

#include "JosephRing.h"

void JosephRing::makeList() {
    int numbers;
    node* head = nullptr;
    node* cur = nullptr;
    node* pre;
    // TODO: FILL IT
    if (tourist < 1) {
        return;
    }
    for (int i = 1; i <= tourist; ++i) {
        pre = cur;
        cur = new node();
        if (cur == nullptr) {
            // bad alloc
        }
        cur->index = i;
//        std::cout << "Build " << cur->index << '\n';
        // set head
        if (head == nullptr) {
            head = cur;
            min = cur;
        }
        if (i == start) {
            prenode = pre;
            curnode = cur;
        }
        if (pre) pre->next = cur;
    }

    // MAKE IT A RING
    cur->next = head;
    if (prenode == nullptr) {
        prenode = cur;
    }
}

int JosephRing::die_one() {
    int count = 1;
    while (count < mod) {
        ++count;
        prenode = prenode->next;
        curnode = curnode->next;
    }
    if (prenode == curnode) {
        // pass
    }
    if (curnode == min) {
        min = min->next;
    }
    std::cout << "第" << ++dead << "个死者的位置是\t" << curnode->index << '\n';
    auto tmp = curnode->next;
    delete curnode;
    curnode = tmp;
    prenode->next = curnode;
//    ++dead;
}

void JosephRing::run() {
    while (dead < tourist - remains) {
        die_one();
    }
}

void JosephRing::show_remains() {
    if (!curnode) {
        // EMPTY
        return;
    }
    auto minnode = min->next;
    std::cout << min->index << '\t';
    while (minnode != min) {
        std::cout << minnode->index << '\t';
        minnode = minnode->next;
    }
    std::cout << '\n';
}

JosephRing::~JosephRing() {
    if (!min ) {
        return;
    }
    auto ptr_head = min;

    if (ptr_head->next == min) {
        delete min;
        min = curnode = prenode = nullptr;
    } else {
        ptr_head = ptr_head->next;
        while (ptr_head != min) {
            min->next = ptr_head->next;
#ifdef DEBUG
            std::cout << ptr_head->index << ": is deleted\n";
#endif
            delete ptr_head;
            ptr_head = min->next;
        }
        std::cout << min->index << ": is deleted\n";
        delete min;
        min = curnode = prenode = nullptr;
    }
}

