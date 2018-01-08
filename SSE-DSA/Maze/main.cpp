#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

#include "MyQueue.h"
#include "Maze.h"

using namespace std;

bool dfs(vector<vector<char>>& maze, Position beg_pos, MyQueue<Position>& route);
void output_route(const MyQueue<Position>& route);
void output_maze(const vector<vector<char>> &maze);

void get_value_with_lower(int& value, const int lower, istream& is) {
    is >> value;
    while (value <= lower) {
        cout << "应该输入大于" << lower << "的数字\n!";
        is >> value;
    }
}

int main() {
    ifstream in_stream("/Users/fuasahi/ClionProjects/Maze/Testdatas/testdata4");
    int maze_x, maze_y;
    get_value_with_lower(maze_x, 0, in_stream);
    get_value_with_lower(maze_y, 0, in_stream);

    Maze maze(maze_x, maze_y);
    maze.build_maze(in_stream);
    // 路径
    maze.output(cout);
    auto route = maze.find_fastest();
//    auto route = maze.find_shortest();
    output_route(route);
    maze.output(cout);
    return 0;
}


void output_route(const MyQueue<Position>& route) {
    if (route.size() == 0) {
        cout << "找不到路径！\n";
        return;
    }
    cout << '<' << route._queue[0].x << ','<< route._queue[0].y << '>';
    for (int i = 1; i < route.size(); ++i) {
        cout << "-->" << '<' << route._queue[i].x << ','<< route._queue[i].y << '>';
    }
    putchar('\n');
}

