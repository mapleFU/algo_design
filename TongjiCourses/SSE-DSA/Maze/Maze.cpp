//
// Created by 付旭炜 on 2017/12/20.
//

#include "Maze.h"

void Maze::output(std::ostream &os) {
    os << "x\t";
    for (int i = 0; i < _maze[0].size(); ++i) {
        os << i << '\t';
    }
    os << '\n';
    int line = 0;
    for (int j = 0; j < _maze.size(); ++j) {
        os << j << '\t';
        for (int i = 0; i < _maze[0].size(); ++i) {
            os << _maze[j][i] << '\t';
        }
        os << '\n';
    }
}

MyQueue<Position> Maze::find_shortest() {
    if (!builded) {
        std::cerr << "迷宫没有被初始化\n";
        exit(0);
    }
    MyQueue<Position> route;
    bfs(route);
    return route;
}

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

void Maze::bfs_route(MyQueue<Position> &route, Position trace, const std::vector<std::vector<Position>> &from) {
    if (trace != start_pos) {
        auto to_trace = from[trace.x][trace.y];
        bfs_route(route, to_trace, from);
        route.push_back(from[trace.x][trace.y]);
    } else {
        route.push_back(trace);
    }
}

void Maze::bfs(MyQueue<Position>& route) {
    MyQueue<Position> process;      // 处理队列
//    auto beg_pos = start_pos;
    std::vector<std::vector<bool>> mark(maze_y, std::vector<bool >(maze_x, false));
    std::vector<std::vector<Position>> from(maze_y, std::vector<Position>(maze_x));
    from[start_pos.x][start_pos.y] = start_pos;
    process.push_back(start_pos);
    while (process.size() != 0) {
        auto beg_pos = process.pop();
        mark[beg_pos.x][beg_pos.y] = true;
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                if (abs(i + j) == 1) {
                    if (inmap(i + beg_pos.x, j + beg_pos.y) && _maze[beg_pos.x][beg_pos.y] != '#' &&
                            !mark[i + beg_pos.x][j + beg_pos.y]) {
                        // 点是可以访问的
                        auto cur_pos = Position(i + beg_pos.x, j + beg_pos.y);
                        from[cur_pos.x][cur_pos.y] = beg_pos;
                        if (_maze[cur_pos.x][cur_pos.y] == 'T') {
                            // found
                            Position trace = cur_pos;
                            bfs_route(route, trace, from);
                            return;
                        }
                        process.push_back(cur_pos);
                    }
                }
            }
        }
    }

}

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


