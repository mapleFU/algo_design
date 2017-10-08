//
// Created by 付旭炜 on 2017/10/7.
//

#ifndef MST_PRIM_H
#define MST_PRIM_H


#include "Graph.h"
#include <queue>

//struct EdgeComp {
//    bool operator() (const Edge& edge1, const Edge& edge2) {
//        return (edge1.length > edge2.length);
//    }
//};

class Prim {
private:
    const Graph& graph;
    std::vector<bool> used;     //表示边有没有被用过
    std::priority_queue<Edge> pq;
    std::vector<Edge> route;    //得到的最终边
public:
    explicit Prim(const Graph& _graph): graph(_graph), used(_graph.vertaxs, false) {}
    void run(int start);
    void run(const std::string& start) { run(graph.name_to_index.at(start)); }
    void show();
};


#endif //MST_PRIM_H
