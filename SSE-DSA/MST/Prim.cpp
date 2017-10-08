//
// Created by 付旭炜 on 2017/10/7.
//

#include "Prim.h"
#include <iostream>

void Prim::run(int start) {
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

void Prim::show() {
    const auto &index2name = graph.index_to_name;
    for(auto& edge: route) {
        std::cout << index2name.at(edge.from) << "-<"<< edge.length <<">->" << index2name.at(edge.to);
        std::cout << "   ";
    }
}
