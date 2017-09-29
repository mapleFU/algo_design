#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

bool judge_queen(const vector<int>& queen_vec) {
    for (int i = 1; i < queen_vec.size(); ++i) {
        for (int j = 0; j < i; ++j) {
            if (abs(i - j) == abs(queen_vec[i] - queen_vec[j]))
                return false;
        }
    }
    return true;
}

void print_vec(const vector<int>& queen_vec) {
    auto size = queen_vec.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j + 1 != queen_vec[i]) {
                printf("O ");
            } else {
                printf("X ");
            }
        }
        putchar('\n');
    }
    putchar('\n');
}

int main() {
    int n ;
    cout << "现有NXN的棋盘，放入N个皇后要求所有皇后不再同一行、列和斜线上"<<'\n' << "请输入皇后的个数\n";
    cin >> n;
    vector<int> queen_vec(n);
    for (int i = 0; i < n; ++i) {
        queen_vec[i] = i + 1;
    }

    while (next_permutation(queen_vec.begin(), queen_vec.end())) {
        if(judge_queen(queen_vec)) {
            print_vec(queen_vec);
        }
    }
    return 0;
}