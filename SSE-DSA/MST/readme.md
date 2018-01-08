# 电网建设造价模拟系统
## 分析
### 需求分析
项目简介
	假设一个城市有n个小区，要实现n个小区之间的电网都能够相互接通，构造这个城市n个小区之间的电网，使总工程造价最低。请设计一个能够满足要求的造价方案。

项目功能要求：
	在每个小区之间都可以设置一条电网线路，都要付出相应的经济代价。n个小区之间最多可以有n（n-1）/2条线路，选择其中的n-1条使总的耗费最少。

### 功能分析
1. 需要能提速用户构建无向图(Graph)
2. 能根据无向图构建最小生成树
3. 能够根据不同的初始节点给出可能的不同的最小生成树
4. **提供Prim算法，Kruskal算法两种操作并提供同样的接口**

## 数据结构设计
### Edge: 无向图的边
表示无向图的一条边，能够表示来自的点，目标点及边的长度

数据结构描述

|     字段名或声明     |   类型    |    功能     |
| :------------: | :-----: | :-------: |
|      from      |   int   | 表示无向图出自的边 |
|       to       |   int   | 表示无向图到达的边 |
|     length     |   int   | 表示无向图边的长度 |
| void ft_swap() | private | 交换from to |

### Graph: 设计的无向图

用于存放用户输入的无向图

以下为对应字段

| 字段名           | 类型                                 | 功能         |
| ------------- | ---------------------------------- | ---------- |
| edges         | std::vector\<std::vector\<Edge\>\> | 表示图中的各个边   |
| name_to_index | std::map\<std::string, int\>       | 图的名称向点的索引  |
| index_to_name | std::map\<int, std::string\>       | 点对应图的名称的索引 |
| edgeAdded     | bool                               | 表示是否添加了边   |

以下为对应方法

|                  方法声明                  | 是否public |      对应功能      |
| :------------------------------------: | :------: | :------------: |
|  bool addVertaxName(std::istream& is)  |    否     | 借助输入流向图中加入一个顶点 |
|    void addEdges(std::istream& is)     |    否     |    向输入流加入边     |
|      static Graph* createVertax()      |    是     |    提示用户添加点     |
| static void createEdges(Graph* pgraph) |    是     |    提示用户添加边     |


### MST(抽象基类): 需要调用的最小生成树生成

主要的算法，程序的执行者，通过调用 `run()` 方法执行主要的程序逻辑

| 字段    | 类型                  | 功能                    |
| ----- | ------------------- | --------------------- |
| graph | const Graph&        | 保存整个需要处理的图            |
| used  | std::vector\<bool\> | 表示整个边没有被用过，被初始化为false |
| route | std::vector\<Edge\> | 得到的最终边的序列             |

下为该算法的对应方法

| 方法声明                                | 是否public | 对应功能                                     | 是否virtual |
| ----------------------------------- | -------- | ---------------------------------------- | --------- |
| void run(int start)                 | 否        | 指定开始顶点的序号，开始运行最小生成树算法(用于被以下函数调用)(**实际执行的算法**) | 是         |
| void run(const std::string& start)  | 是        | 指定开始顶点的名称，开始借助`void run(int start)`运行prim算法 | 否         |
| void show()                         | 是        | 打印得到的prm算法的结果(即得到的最小生成树)                 | 否         |
| static Mst* buildMft(Graph* pgraph) | 是        | 使用户构建Prim算法                              | 否         |



### 子类: Prim

继承自MST，实现了MST对应的接口

以下是Prim算法的特有字段

| 字段名称与类型                  | 功能       |
| ------------------------ | -------- |
| std::vector\<bool\> used | 标记边是否被用过 |

### 子类: Kruskal

继承自MST，实现了MST对应的接口

以下是Kruskal算法的特有字段

| 字段名称与类型              | 功能      |
| -------------------- | ------- |
| UnionFind unionFind; | 标记边的并查集 |

## 测试与运行

### 最小生成树的构造

这里在构造中可以采用先对顶点创建、再对边创建的顺序。

#### 顶点构建

下列为创建顶点的方法

```c++
Graph *Graph::createVertax() {
    std::cout << "请输入顶点的个数：";
    unsigned int vertaxs;
    std::cin >> vertaxs;
    auto graph = new Graph(vertaxs);
    graph->addVertaxName(std::cin);
    return graph;
}

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
```

借助`Graph`的构造函数，并且用数据流cin创建顶点

以下是在DEBUG模式下的输出

```
------------------------------
**		 电网造价模拟系统 		**
------------------------------
**		A——创建电网顶点		**
**		B——添加电网的边		**
**		C——构造最小生成树		**
**		D——显示最小生成树		**
**		E——退出程序			**
------------------------------
请选择操作
A
请输入顶点的个数：4
请依次输入各个顶点的名称
a b c d
DEBUG: mapkey:a	value: 0
DEBUG: mapkey:b	value: 1
DEBUG: mapkey:c	value: 2
DEBUG: mapkey:d	value: 3
```

可以看到，由打印的DEBUG显示，顶点已经被成功的创建了

#### 边构建

构建边即在顶点对象的vector后添加边的对象，使点对点显示是可达的

操作的代码显示如下

```c++
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
        std::cout << e1 << " --> " << e2 << " with length " << length << '\n';
#endif
        std::cout << HINT_STRING;
    }
    edgeAdded = true;
}
```

以下是在DEBUG 模式下的输出结果，可以看到在DEBUG模式下，边被成功的添加

```
a b 8
b c 7
c d 5
d a 11
a c 18
b d 12
? ? 00 --> 1 with length 8
0 --> 1 with length 8
请输入两个顶点及边
1 --> 2 with length 7
1 --> 2 with length 7
请输入两个顶点及边
2 --> 3 with length 5
2 --> 3 with length 5
请输入两个顶点及边
3 --> 0 with length 11
3 --> 0 with length 11
请输入两个顶点及边
0 --> 2 with length 18
0 --> 2 with length 18
请输入两个顶点及边
1 --> 3 with length 12
1 --> 3 with length 12
请输入两个顶点及边
? ? 0
```

### 最小生成树的构建

#### Prim

根据以下的提示，可以直接借助`	Prim`算法创建最小生成树。

```
请选择操作
C
请输入起始顶点
a
```

Prim算法借助优先队列实现，返回的结果是一个prim指针，储存最小生成树的结果

```c++
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
```

算法利用优先队列，每次取出优先队列中最小的边，并借助此边来优化

```
请选择操作
D
a-<8>->b   b-<7>->c   c-<5>->d   
请选择操作
```

已知输入序列的情况下，显然这就是最小生成树。

#### kruskal

```c++
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
```

加入所有的边至优先队列，并逐个取出，在并查集中判断等价。