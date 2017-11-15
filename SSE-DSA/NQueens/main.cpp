#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

#include "NQueen.h"

using namespace std;

int main() {
    int n ;
    cout << "现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上"<<'\n' << "请输入皇后的个数\n";
    cin >> n;
    NQueen queen(n);

    //25761364
    auto t1 = clock();

    queen.run(true);
    cout << queen.get_results() << endl;
    auto t2 = clock();
    cout << "time is " << t2 - t1 << endl;

    return 0;
}