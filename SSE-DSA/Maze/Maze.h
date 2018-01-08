//
// Created by 付旭炜 on 2017/12/20.
//

#ifndef MAZE_MAZE_H
#define MAZE_MAZE_H

#include <vector>
#include <iostream>
#include <set>
#include "MyQueue.h"

/*
 * 表示迷宫的类
 */
class Maze {
private:
    const std::set<char> VALID_SET{'#', 'O', 'S', 'T'};
    // 存储迷宫的内部结构
    std::vector<std::vector<char>> _maze;
    int maze_x;
    int maze_y;
    Position start_pos;
    bool builded;

    bool dfs(MyQueue<Position>& route, const Position& beg_pos);
    void bfs(MyQueue<Position>& route);
    void bfs_route(MyQueue<Position> &route, Position trace, const std::vector<std::vector<Position>> &from);
    bool inmap(int x, int y) {
        if (x < _maze.size())
            if (y < _maze[0].size())
                return true;
        return false;
    }
    bool check_input_valid(const char& ch) { return VALID_SET.find(ch) != VALID_SET.end(); }
public:
    // 构造函数
    Maze(int size_x, int size_y): _maze(size_y, std::vector<char>(size_x)),
                                  maze_x(size_x), maze_y(size_y), builded(false)
    {}



    void build_maze(std::istream& in) {
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

        // 验证输入的数据的合法性
        if (entrance == 0 || entrance > 1) {
            std::cerr << "只能有一个表示入口的S 请重新输入\n";
            return;
        } else if (wayout == 0 || wayout > 1) {
            std::cerr << "只能有一个表示出口的T 请重新输入\n";
            return;
        }
        // 已经成功建造
        builded = true;
    }

    void output(std::ostream& os=std::cout);

    // 用BFS寻找最短路径
    MyQueue<Position> find_shortest();
    // DFS快速查找
    MyQueue<Position> find_fastest();

};


#endif //MAZE_MAZE_H
