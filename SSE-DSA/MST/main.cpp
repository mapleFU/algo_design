#include <iostream>
#include "Graph.h"
#include "Prim.h"
#include <functional>
#include <map>

/*
 * A: 创建电网顶点
 */
Graph* createVertax() {
    std::cout << "请输入顶点的个数：";
    unsigned int vertaxs;
    std::cin >> vertaxs;
    auto graph = new Graph(vertaxs);
    graph->addVertaxName(std::cin);
    return graph;
}

/*
 * 添加边
 */
void createEdges(Graph* pgraph) {
    if (pgraph == nullptr) {
        std::cout << "你应该先创建顶点！";
        return;
    }
    pgraph->addEdges(std::cin);
}

/*
 * 建立最小生成树
 */
Prim* buildMft(Graph* pgraph) {
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
    pprim->run(start);
    return pprim;
}
/*
 * 显示最小生成树
 */
void showMft(Prim* pprim) {
    if (pprim == nullptr) {
        std::cout << "你应该先把最小生成树做出来，试试C\n";
        return;
    }
    pprim->show();
}

void purge(Graph* pgraph, Prim* pprim);
int main() {
    std::string op;     //操作

    Graph* pgraph = nullptr;
    Prim* pprim = nullptr;
    std::cout << "请选择操作\n";
    while (std::cin >> op) {
        if (op[0] == 'A') {
            if (pgraph) delete pgraph;
            pgraph = createVertax();
        } else if (op[0] == 'B') {
            createEdges(pgraph);
        } else if (op[0] == 'C') {
            pprim = buildMft(pgraph);
        } else if (op[0] == 'D') {
            showMft(pprim);
        } else if (op[0] == 'E') {
            break;
        }
        std::cout << "请选择操作\n";
    }

    purge(pgraph, pprim);
    return 0;
}

void purge(Graph* pgraph, Prim* pprim) {
    if (pprim)
        delete pprim;
    if (pgraph)
        delete pgraph;
}