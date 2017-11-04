#include <iostream>
#include <fstream>
#include <functional>
#include "JosephRing.h"

constexpr char test_file[] = "/Users/fuasahi/Desktop/test.txt";

using namespace std;

template <typename ValueType>
void get_input(ValueType& inputed, function<bool(const ValueType& value)> judge_func,
               const std::string& hint, const std::string& error) {
    /*
     * inputed: 被输入的对象
     * Judge_func: 判别是否合理的函数
     * hint: 输入提示语
     * error: 报错的字符串
     */
    while (true) {
        std::cout << hint << '\n';
        std::cin >> inputed;
        if (judge_func(inputed)) {
            // 通过测试
            return;
        }
        // 否则没通过测试
        std::cout << error << '\n';
    }
}

int main() {

#ifdef DEBUG
    // TEST
    ifstream infile;
    infile.open(test_file, ios::in);
    istream& is = infile;
#else
    istream& is = std::cin;
#endif

    int tourists, start, mod, remains;

    get_input<int>(tourists,
              [](const int&value)->bool { return value > 0;},
              "请输入生死游戏的总人数N：",
              "人数过少，游戏无法进行");

    get_input<int>(start,
              [tourists](const int&value)->bool { return value >= 0 && value < tourists;},
              "请输入游戏的开始位置S：",
              "开始的位置应该不小于0且大于旅客数");

    get_input<int>(mod,
                   [](const int&value)->bool { return value > 0;},
                   "请输入死亡数字M：",
                   "死亡数字应当大于0");

    get_input<int>(remains,
                   [tourists](const int&value)->bool { return value >= 0 && value < tourists;},
                   "请输入剩余人数R：",
                   "剩余人数应当大于0且小于30");

    JosephRing josephRing(tourists, start, mod, remains);
    cout << "Build josephring\n";
    josephRing.run();

    cout << "最后剩下" << remains << "人";
    cout << "剩余的生者位置为：";
    josephRing.show_remains();
    return 0;
}