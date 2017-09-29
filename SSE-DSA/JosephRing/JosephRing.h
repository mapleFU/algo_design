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
        if (tourist < 0) {std::cerr << "Number of tourists less than 1?"; exit(-1);}
        makeList();
    }
    int die_one();
    void run();
    void show_remains();
    ~JosephRing();
private:
    int tourist, start, mod, remains;
    int dead;   //死亡数目
    void makeList();

    node* curnode, *prenode;
    node* min;
};


#endif //JOSEPHRING_JOSEPHRING_H
