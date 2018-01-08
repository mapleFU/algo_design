//
// Created by 付旭炜 on 2017/12/30.
//
#include "Mst.h"
#include "Prim.h"
#include "Kruskal.h"

Mst *Mst::buildMst(Graph* graph) {
    if (graph == nullptr) {
        std::cout << "你应该先创建顶点！";
        return nullptr;
    } else if (!graph->edgeAdded) {
        std::cout << "你应该先创建边！";
        return nullptr;
    }
    std::cout << "请选出你想要的最小生成树生成方法，A为Prim B为Kruskal\n";
    std::string oper;
    while (std::cin >> oper) {
        switch (tolower(oper[0])) {
            case 'a':
                return Prim::buildMft(graph);
            case 'b':
                return Kruskal::buildMft(graph);
            default:
                break;
        }
        std::cout << "请选出你想要的最小生成树生成方法，A为Prim B为Kruskal\n";
    }
    return nullptr;
}