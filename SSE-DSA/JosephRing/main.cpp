#include <iostream>
#include <fstream>
#include "JosephRing.h"

constexpr char test_file[] = "/Users/fuasahi/Desktop/test.txt";

using namespace std;



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
    cout << "请输入生死游戏的总人数N：";
    is >> tourists;

    cout << "请输入游戏的开始位置S ";
    is >> start;

    cout << "请输入死亡数字M ";
    is >> mod;

    cout << "请输入剩余人数K ";
    is >> remains;

    JosephRing josephRing(tourists, start, mod, remains);
    cout << "Build josephring\n";
    josephRing.run();

    cout << "最后剩下" << remains << "人";
    cout << "剩余的生者位置为：";
    josephRing.show_remains();
    return 0;
}