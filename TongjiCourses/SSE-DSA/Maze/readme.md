# 勇闯迷宫游戏
## 背景分析与解决思路
迷宫只有两个门，一个门叫入口，另一个门叫出口。一个骑士骑马从入口进入迷宫，迷宫设置很多障碍，骑士需要在迷宫中寻找通路以到达出口。

输入中以T代表初始勇者所在位置 #代表不可行的路径 O代表可以行走的路径

迷宫问题相当于一个无向图中寻找有没有到另一点的算法，可以考虑用深度优先搜索和广度优先搜索。由于本题中对路径长度并没有最短的需求，所以可以采用深度优先搜索的算法来解题。

同时如果对路径"最短"有要求，可以用最短的路径来输出结果，耗时可能相对较长
## 功能分析
对于一个给出的地图和路径，本题会根据用户要求的解决类型和提供的图，输出路径并且在地图上给予标注。

1. 对于功能的选择，可以采用`最快输出`和`输出最短`两种模式
2. 有稳健性，能够处理不正确的输入
3. 对于特殊情况，比如不能正确找到道路，能够正确处理

# 设计
## 数据结构功能设计
### Position
用来表示图中坐标的类

|字段|类型|
| ---------- |:-------------:|
| x| int|
| y| int|

### MyQueue
用于表示路径，并能够辅助BFS的队列。内部采用向量实现

|函数声明|作用|
| ---------- |:-------------:|
|`void push_back(const Type& value)`|向队列中插入元素|
|`int size() const`|求出队列中元素的大小|
|`Type pop()`|推出队列首元素|

### Maze
最重要的类，用于表示和存储迷宫，并能根据指定的方法返回需要的结果

下面是私有的字段

|类型|字段|
| ---------- |:-------------:|
|std::vector<std::vector<char>>| _maze|
|int |maze_x|
    |int| maze_y|
    |Position |start_pos|
    |bool |builded|

|函数声明|是否是私有的|作用|
|:----------:|:-------------:|:-------------:|
|`void build_maze(std::istream& in)`|PUBLIC| 根据输入创建图|
|`void output_route(const MyQueue<Position>& route)`|PUBLIC|打印路线|
|`MyQueue<Position> find_shortest()`|PUBLIC|找到最短的路径|
|`MyQueue<Position> find_fastest();`|PUBLIC|最快的返回一条可行的路径|
|`bool dfs(MyQueue<Position>& route, const Position& beg_pos)`|private|使用深度优先有搜索争取快速找到路径|
|`void bfs(MyQueue<Position>& route)`|private|用深度优先搜索找到最短的路径|
|`void bfs_route(MyQueue<Position> &route, Position trace, const std::vector<std::vector<Position>> &from)`|private|BFS辅助函数，用搜索的结果寻找路径|
|`bool inmap(int x, int y)`|private|bfs dfs的辅助函数，用于检查给出的点在图中是否越界|
|`bool check_input_valid(const char& ch)`|private|build_map辅助函数，用于检测输入是否可靠合法|

## 实现
### 图初始化的实现
```C++
int maze_x, maze_y;
get_value_with_lower(maze_x, 0, in_stream);
get_value_with_lower(maze_y, 0, in_stream);
Maze maze(maze_x, maze_y);
maze.build_maze(in_stream);
```
使用户输入x y，并用X Y在构造函数中初始化maze



再使用build_maze 函数，根据输入流来输入具体信息

```C++
// 出现的 T S 的数目
int entrance(0), wayout(0);
for (int i = 0; i < maze_y; ++i) {
    for (int j = 0; j < maze_x; ++j) {
        char ch;
        in >> ch;
        if (check_input_valid(ch)) {
            _maze[i][j] = ch;
        } else {
            std::cerr << "输入的需要是 '#', 'O', 'S', 'T' 四个中之一\n";
            exit(0);
        }
        if (_maze[i][j] == 'S') {
            start_pos.x = i;
            start_pos.y = j;
            ++entrance;
        } else if (_maze[i][j] == 'T') {
            ++wayout;
        }
    }
}
...
```

### 搜索的实现
搜索调用了`find_fastest`函数，并且能够返回一个表示路径的队列，使用搜索效果如下
```C++
 auto route = maze.find_fastest();
//    auto route = maze.find_shortest();
output_route(route);
maze.output(cout);
```

find_fastest调用DFS, 对于一个点，先将其标记为已访问，并找出其周围所有的可访问的点，分别DFS搜索。

如果找到目标点T，则返回TRUE。上层如果发现递归的调用返回了TRUE, 则把自己的点放入队列，并返回TRUE.
```C++
MyQueue<Position> Maze::find_fastest() {
    if (!builded) {
        std::cerr << "迷宫没有被初始化\n";
        exit(0);
    }
    MyQueue<Position> route;
    if (!dfs(route, start_pos)) {
        // return an empty route
        return MyQueue<Position>();
    }
    return route;
}
```

```doxygen
bool Maze::dfs(MyQueue<Position>& route, const Position& beg_pos) {
    route.push_back(beg_pos);
    _maze[beg_pos.x][beg_pos.y] = 'X';       //标记为已经走过

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (abs(i + j) == 1) {
                if (inmap(i + beg_pos.x, j + beg_pos.y)) {
                    // 点是可以访问的
                    auto cur_pos = Position(i + beg_pos.x, j + beg_pos.y);
                    if(_maze[i + beg_pos.x][j + beg_pos.y] == 'T') {    // 找到目的地
                        route.push_back(cur_pos);
                        return true;
                    } else if (_maze[i + beg_pos.x][j + beg_pos.y] == 'O') {
                        if (dfs(route, cur_pos))
                            return true;
                    }
                }
            }
        }
    }

    route.pop();
    return false;
}
```
## 测试与边界条件处理
### 初始化、输入的边界测试
本例使用以下测试数据进行测试, 可以在TESTDATA找到这些数据
```doxygen
4 3
S O # O
# O T O
# # O O
```

测试代码
```C++
ifstream in_stream("/Users/fuasahi/ClionProjects/Maze/testdata");
int maze_x, maze_y;
get_value_with_lower(maze_x, 0, in_stream);
get_value_with_lower(maze_y, 0, in_stream);

Maze maze(maze_x, maze_y);
maze.build_maze(in_stream);
// 路径
maze.output(cout);
```
    
输出
```doxygen
x	0	1	2	3	
0	S	O	#	O	
1	#	O	T	O	
2	#	#	O	O	
```
成功将图写入Maze，并能够正确打印

#### 边界条件测试
1. 输入规模不正确
利用`get_value_with_lower`做输入验证
```doxygen
void get_value_with_lower(int& value, const int lower, istream& is) {
    is >> value;
    while (value <= lower) {
        cout << "应该输入大于" << lower << "的数字\n!";
        is >> value;
    }
}
```
只有输入满足条件才可以正常运行

输入4 -3
输出`!应该输入大于0的数字`

2. 输入错误符号
```doxygen
4 3
S O # O
# O T O
# # 7 S
```
包含有不正常符号或者有多个T、S会抛出错误
输出``输入的需要是 '#', 'O', 'S', 'T' 四个中之一``

### 搜索的使用和测试
用下面的数据测试
```doxygen
4 3
S O # O
# O T O
# # O O
```

输出结果如下
```doxygen
<0,0>--><0,1>--><1,1>--><1,2>
x	0	1	2	3	
0	X	X	#	O	
1	#	X	T	O	
2	#	#	O	O	
```

对于没有路径的图，测试如下
```doxygen
x	0	1	2	3	
0	S	O	#	O	
1	#	O	#	O	
2	#	#	T	O	
找不到路径！
```