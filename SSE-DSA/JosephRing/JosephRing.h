//
// Created by 付旭炜 on 2017/9/28.
//

#ifndef JOSEPHRING_JOSEPHRING_H
#define JOSEPHRING_JOSEPHRING_H

#include <iostream>
#define NDEBUG

struct node {
    node* next;
    int index;
};

class JosephRing {
public:
    JosephRing(int tourist, int start, int mod, int remains) {
        dead = 0;
        min = prenode = curnode = nullptr;
        this->remains = remains;
        this->tourist = tourist;
        this->start = start;
        this->mod = mod;
        makeList();
    }

    // 整体运行
    void run();
    // 现实剩余者
    void show_remains();
    ~JosephRing();
private:
    int tourist, start, mod, remains;
    int dead;   //死亡数目
    // 根据信息构造环状链表
    // 只应该在构造函数使用
    void makeList();
    // 杀一个人
    int die_one();
    node* curnode, *prenode;
    node* min;
};


#endif //JOSEPHRING_JOSEPHRING_H
