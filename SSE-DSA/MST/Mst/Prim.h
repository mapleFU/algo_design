//
// Created by 付旭炜 on 2017/10/7.
//

#ifndef MST_PRIM_H
#define MST_PRIM_H


#include "../Graph.h"
#include <queue>
#include "Mst.h"

class Prim: public Mst{
private:
    std::vector<bool> used;     //表示边有没有被用过


public:
    explicit Prim(const Graph& _graph): Mst(_graph), used(_graph.vertaxs, false) {}

    static Prim* buildMft(Graph* pgraph);

protected:
    void run(int start) override ;
};


#endif //MST_PRIM_H
