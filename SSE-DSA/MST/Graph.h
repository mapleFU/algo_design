//
// Created by 付旭炜 on 2017/10/7.
//

#ifndef MST_GRAPH_H
#define MST_GRAPH_H


#include <vector>
#include <string>
#include <map>

struct Edge {
    int from;
    int to;
    int length;
    Edge(int _from, int _to, int _length): from(_from), to(_to), length(_length) {}
    Edge() = default;
    /*
     * 交换FROM和TO
     */
    void ft_swap() {std::swap(from, to);}
    bool operator<(const Edge& edge) const {
        return length > edge.length;
    }
};

/*
 * Graph用于表示无向图，
 */
class Graph {
private:
    std::vector<std::vector<Edge>> edges;    //图中的各个边
    std::map<std::string, int> name_to_index;            //图的名称向点的索引
    std::map<int, std::string> index_to_name;            //点对应图的名称的索引
    int vertaxs;                            //顶点的数目

    /*
     * 添加顶点名称
     */
    bool addVertaxName(std::istream& is);
    void addEdges(std::istream& is);
    bool edgeAdded;
public:
    friend class Mst;
    friend class Kruskal;

    int size() const { return vertaxs;}
    friend class Prim;
    /*
     * 用边数构造图
     */
    explicit Graph(unsigned V) :edges(V, std::vector<Edge>(V)), vertaxs(V), edgeAdded(false) {}


    static Graph* createVertax();
    /*
     * 添加边
     */
    static void createEdges(Graph* pgraph);


};


#endif //MST_GRAPH_H
