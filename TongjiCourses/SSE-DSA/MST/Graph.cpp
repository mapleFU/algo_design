//
// Created by 付旭炜 on 2017/10/7.
//

#include "Graph.h"
#include <iostream>

#define DEBUG


bool Graph::addVertaxName(std::istream& is = std::cin) {
    std::string name;
    std::cout << "请依次输入各个顶点的名称\n";
    for (int i = 0; i < vertaxs; ++i) {
        is >> name;
        name_to_index[name] = i;
        index_to_name[i] = name;
#ifdef DEBUG
        std::cout << "DEBUG: " << "mapkey:" << name << "\tvalue: " << i << '\n';
#endif
    }
    return true;
}

void Graph::addEdges(std::istream &is = std::cin) {
    const static std::string END_STRING = "?";
    const static std::string HINT_STRING = "请输入两个顶点及边\n";
    std::string edge1, edge2;
    int length;
    std::cout << HINT_STRING;
    while (is >> edge1 >> edge2 >> length ) {
        if ((edge1 == END_STRING && edge2 == END_STRING)) {
            break;
        }
        int e1 = name_to_index[edge1], e2 = name_to_index[edge2];
        edges[e1].emplace_back(Edge(e1, e2, length));
#ifdef DEBUG
        std::cout << e1 << " --> " << e2 << " with length " << length << '\n';
#endif
        edges[e2].emplace_back(Edge(e2, e1, length));
#ifdef DEBUG
        std::cout << e2 << " --> " << e1 << " with length " << length << '\n';
#endif
        std::cout << HINT_STRING;
    }
    edgeAdded = true;
}

Graph *Graph::createVertax() {
    std::cout << "请输入顶点的个数：";
    unsigned int vertaxs;
    std::cin >> vertaxs;
    auto graph = new Graph(vertaxs);
    graph->addVertaxName(std::cin);
    return graph;
}

void Graph::createEdges(Graph *pgraph) {
    if (pgraph == nullptr) {
        std::cout << "你应该先创建顶点！";
        return;
    }
    pgraph->addEdges(std::cin);
}


