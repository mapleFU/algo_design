#include <iostream>
#include "Graph.h"
#include "Mst/Prim.h"
#include "Mst/Kruskal.h"
#include "Mst/Mst.h"

/*
 * 显示最小生成树
 */
void showMft(Mst* mst) {
    if (mst == nullptr) {
        std::cout << "你应该先把最小生成树做出来，试试C\n";
        return;
    }
    mst->show();
}

void purge(Graph* pgraph, Mst* pprim);
int main() {
    std::cout << "------------------------------\n"
            "**\t\t 电网造价模拟系统 \t\t**\n"
            "------------------------------\n"
            "**\t\tA——创建电网顶点\t\t**\n"
            "**\t\tB——添加电网的边\t\t**\n"
            "**\t\tC——构造最小生成树\t\t**\n"
            "**\t\tD——显示最小生成树\t\t**\n"
            "**\t\tE——退出程序\t\t\t**\n"
            "------------------------------\n";

    std::string op;     //操作

    Graph* pgraph = nullptr;
    Mst *mst = nullptr;
    std::cout << "请选择操作\n";
    while (std::cin >> op) {
        if (op[0] == 'A') {
            if (pgraph) delete pgraph;
            pgraph = Graph::createVertax();
        } else if (op[0] == 'B') {
            Graph::createEdges(pgraph);
        } else if (op[0] == 'C') {
            mst = Mst::buildMst(pgraph);
        } else if (op[0] == 'D') {
            showMft(mst);
        } else if (op[0] == 'E') {
            break;
        }
        std::cout << "请选择操作\n";
    }

    purge(pgraph, mst);
    return 0;
}

void purge(Graph* pgraph, Mst* pprim) {
    if (pprim)
        delete pprim;
    if (pgraph)
        delete pgraph;
}