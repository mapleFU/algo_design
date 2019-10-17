//
// Created by 付旭炜 on 2017/12/20.
//

#ifndef MAZE_MYQUEUE_H
#define MAZE_MYQUEUE_H

/*
 * 表示位置的结构
 */
struct Position {
    int x;
    int y;
    Position() = default;
    Position(int _x, int _y): x(_x), y(_y) {}
    bool operator==(const Position& pos) {
        if (pos.x == x && pos.y == y) return true;
        return false;
    }
    bool operator!=(const Position& pos) {
        return !(*this == pos);
    }
};


/*
 * 个人实现的队列
 */
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

#endif //MAZE_MYQUEUE_H
