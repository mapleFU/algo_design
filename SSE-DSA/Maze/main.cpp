#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

/*
 * 表示位置
 */
struct Position {
    int x;
    int y;
    Position() = default;
    Position(int _x, int _y): x(_x), y(_y) {}
};

template <typename Type>
class MyQueue {
private:
    std::vector<Type> _queue;
    int top;
    int queue_size;
public:
    friend void output_route(const MyQueue<Position>& route);
    MyQueue() { queue_size = top = 0; }
    void push_back(const Type& value) {
        ++queue_size;
        _queue.push_back(value);
    }
    Type pop() {
        if (queue_size == 0) {
            // it's empty
            std::cout << "Error, the queue is empty!\n";
            exit(1);
        }
        auto value = _queue.back();
        _queue.pop_back();
        return value;
    }
    int size() const { return queue_size;}
};



using namespace std;

bool dfs(vector<vector<char>>& maze, Position beg_pos, MyQueue<Position>& route);
void output_route(const MyQueue<Position>& route);
void output_maze(const vector<vector<char>> &maze);

int main() {
    ifstream in_stream("/Users/fuasahi/ClionProjects/Maze/testdata");
    int maze_x, maze_y;
    in_stream >> maze_x >> maze_y;
    vector<vector<char>> maze(maze_x, vector<char>(maze_y));

    Position start_pos;
    for (int i = 0; i < maze_y; ++i) {
        for (int j = 0; j < maze_x; ++j) {
            in_stream >> maze[i][j];
            if (maze[i][j] == 'S') {
                start_pos.x = i;
                start_pos.y = j;
            }
        }
    }

    // 路径
    MyQueue<Position> route;
    output_maze(maze);
    if(dfs(maze, start_pos, route)) {
        output_route(route);
    } else {
        cout << "There are no path in the maze!\n";
    }
    return 0;
}

inline bool inmap(int x, int y, vector<vector<char>>& maze) {
    if (x < maze.size())
        if (y < maze[0].size())
            return true;
    return false;
}

bool dfs(vector<vector<char>>& maze, Position beg_pos, MyQueue<Position>& route) {
    route.push_back(beg_pos);
    maze[beg_pos.x][beg_pos.y] = 'X';       //标记为已经走过

    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (abs(i + j) == 1) {
                if (inmap(i + beg_pos.x, j + beg_pos.y, maze)) {
                    // 点是可以访问的
                    auto cur_pos = Position(i + beg_pos.x, j + beg_pos.y);
                    if( maze[i + beg_pos.x][j + beg_pos.y] == 'T') {    // 找到目的地
                        route.push_back(cur_pos);
                        return true;
                    } else if (maze[i + beg_pos.x][j + beg_pos.y] == 'O') {
                        if (dfs(maze, cur_pos, route))
                            return true;
                    }
                }
            }
        }
    }

    route.pop();
    return false;
}

void output_route(const MyQueue<Position>& route) {
    cout << '<' << route._queue[0].x << ','<< route._queue[0].y << '>';
    for (int i = 1; i < route.size(); ++i) {
        cout << "-->" << '<' << route._queue[i].x << ','<< route._queue[i].y << '>';
    }
    putchar('\n');
}

void output_maze(const vector<vector<char>> &maze) {
    cout << "x\t";
    for (int i = 0; i < maze[0].size(); ++i) {
        cout << i << '\t';
    }
    cout << '\n';
    int line = 0;
    for (int j = 0; j < maze.size(); ++j) {
        cout << j << '\t';
        for (int i = 0; i < maze[0].size(); ++i) {
            cout << maze[j][i] << '\t';
        }
        cout << '\n';
    }
}