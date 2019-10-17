#include <iostream>

#include "NQueen.h"

using namespace std;

constexpr int UPPER_BOUND = 16;
constexpr int LOWER_BOUND = 0;

inline bool input_valid(int input) {
    return (UPPER_BOUND > input && LOWER_BOUND < input);
}

int main() {
    int n ;
    cout << "现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上"<<'\n' << "请输入皇后的个数\n";

    // 数据可靠性验证
    while (cin >> n && !input_valid(n)) {
        cout << "请输入" << UPPER_BOUND << " 和 " << LOWER_BOUND << " 内的数据\n";
    }

    NQueen queen(n);

    queen.run();
    cout << queen.get_results() << endl;

    return 0;
}