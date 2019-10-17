//
// Created by 付旭炜 on 2017/10/7.
//

#include "Prim.h"
#include <iostream>

void Prim::run(int start) {
    std::priority_queue<Edge> pq;
    used[start] = true;
    auto intree = 1;           //已经在区域中的边
    int cur_point = start;
    const auto& edges = graph.edges;
    while (intree < used.size()) {
        for (int i = 0; i < edges[cur_point].size(); ++i) {
            if (!used[edges[cur_point][i].to])  pq.push(edges[cur_point][i]);
        }
        while (used[pq.top().to]) {pq.pop();}
        auto cur_edge = pq.top();
        pq.pop();
        used[cur_edge.to] = true;
        cur_point = cur_edge.to;
        route.push_back(cur_edge);
        ++intree;
    }
}


Prim *Prim::buildMft(Graph *pgraph) {

    if (pgraph == nullptr) {
        std::cout << "你应该先创建顶点！";
        return nullptr;
    } else if (!pgraph->edgeAdded) {
        std::cout << "你应该先创建边！";
        return nullptr;
    }
    auto pprim = new Prim(*pgraph);
    std::cout << "请输入起始顶点\n";
    std::string start;
    std::cin >> start;
    pprim->Mst::run(start);
    return pprim;

}
