//
// Created by 付旭炜 on 2017/12/30.
//

#ifndef MST_KRUSKAL_H
#define MST_KRUSKAL_H


#include "Mst.h"

class UnionFind {
private:
    int _size;
    std::vector<int> uf;
public:
    explicit UnionFind(int size): _size(size), uf(size, -1) {}
    int find_father(int node);
    void union_nodes(int node1, int node2);
    bool equal(int node1, int node2) { return find_father(node1) == find_father(node2);}
    bool equal_and_union(int node1, int node2) {
        int f1 = find_father(node1);
        int f2 = find_father(node2);
        if (f1 == f2) {
            return false;
        } else {
            uf[f1] = f2;
            return true;
        }
    }
};

class Kruskal: public Mst {
private:
    // 需要用到的 UnionFind
    UnionFind unionFind;
public:
    explicit Kruskal(const Graph& _graph): Mst(_graph), unionFind(_graph.size()) {}

    static Kruskal* buildMft(Graph* pgraph);

private:
    void run(int start) override final ;
};


#endif //MST_KRUSKAL_H
