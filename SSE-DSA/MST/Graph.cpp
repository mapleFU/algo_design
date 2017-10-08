//
// Created by 付旭炜 on 2017/10/7.
//

#include "Graph.h"
#include <iostream>

bool Graph::addVertaxName(std::istream& is = std::cin) {
    std::string name;
    for (int i = 0; i < vertaxs; ++i) {
        is >> name;
        name_to_index[name] = i;
        index_to_name[i] = name;
        std::cout << "DEBUG: " << "mapkey:" << name << "\tvalue: " << i << '\n';
    }
    return true;
}

void Graph::addEdges(std::istream &is = std::cin) {
    const static std::string END_STRING = "?";
    std::string edge1, edge2;
    int length;
    while (is >> edge1 >> edge2 >> length ) {
        if ((edge1 == END_STRING && edge2 == END_STRING)) {
            break;
        }
        int e1 = name_to_index[edge1], e2 = name_to_index[edge2];
        edges[e1].emplace_back(Edge(e1, e2, length));
        edges[e2].emplace_back(Edge(e2, e1, length));
    }
    edgeAdded = true;
}


