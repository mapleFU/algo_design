//
// Created by 付旭炜 on 2017/12/30.
//

#ifndef MST_MST_H
#define MST_MST_H

#include "../Graph.h"
#include <iostream>

class Mst {
protected:
    const Graph& graph;
    std::vector<Edge> route;    //得到的最终边
    virtual void run(int start) = 0;
public:
    explicit Mst(const Graph& graph): graph(graph) {}
    void run(const std::string& start) { run(graph.name_to_index.at(start)); }
    void show() {
        const auto &index2name = graph.index_to_name;
        for(auto& edge: route) {
            std::cout << index2name.at(edge.from) << "-<"<< edge.length <<">->" << index2name.at(edge.to);
            std::cout << "   ";
        }
    }

    static Mst* buildMst(Graph* graph);
    virtual ~Mst() {}
};



#endif //MST_MST_H
