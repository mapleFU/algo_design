//
// Created by 付旭炜 on 2017/12/30.
//

#include "Kruskal.h"
#include <queue>

Kruskal *Kruskal::buildMft(Graph *pgraph) {
    auto kru = new Kruskal(*pgraph);
    std::cout << "请输入起始顶点\n";
    std::string start;
    std::cin >> start;
    kru->Mst::run(start);
    return kru;
}

void Kruskal::run(int start) {
    std::priority_queue<Edge> pq;

    for (auto &edge_vec: graph.edges) {
        for (auto &edge: edge_vec) {
            pq.push(edge);
        }
    }

    int cnt(0);
    while (cnt < graph.size() - 1) {
        auto edge = pq.top();
        pq.pop();
        if (unionFind.equal_and_union(edge.from, edge.to)) {
            route.push_back(edge);
            ++cnt;
        }
    }
}

int UnionFind::find_father(int node) {
    if (uf[node] != -1) {
        uf[node] = find_father(uf[node]);
        return uf[node];
    } else {
        return node;
    }
}

void UnionFind::union_nodes(int node1, int node2) {
    int f1 = find_father(node1);
    int f2 = find_father(node2);
    if (f1 == f2) return;
    else {
        uf[f1] = f2;
    }
}


