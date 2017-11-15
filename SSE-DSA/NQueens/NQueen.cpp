//
// Created by 付旭炜 on 2017/11/15.
//

#include "NQueen.h"


void QueenTable::show_table(std::ostream &os) {
    auto size = _table.size();
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (j + 1 != _table[i]) {
                os << "O ";
            } else {
                os << "X ";
            }
        }
        os.put('\n');
    }
    putchar('\n');
}

int QueenTable::dfs(int depth, bool is_print, std::ostream& os) {
    int sum = 0;
//    show_table(os);
    for (int j = 1; j <= _table.size(); ++j) {
        _table[depth] = j;

        if (judge_queen(depth + 1)) {
            if (depth + 1 == _table.size()) {
                if (is_print) {
                    show_table(os);
                }
                return 1;
            } else {
                sum += dfs(depth + 1, is_print, os);
            }
        }
    }
    _table[depth] = 0;
    return sum;
}

int QueenTable::judge_queen(int range) {
//    std::cout << "Judge:\n";
//    show_table(std::cout);
    for (int i = 1; i < range; ++i) {
        for (int j = 0; j < i; ++j) {
            if (abs(i - j) == abs(_table[i] - _table[j]) || _table[i] == _table[j])
                return false;
        }
    }
    return true;
}

void NQueen::run(bool is_print) {

    // 运行过不再运行
    if (_runned) {
        return;
    }
    _result = _table.dfs(0, is_print);
    _runned = true;

}

int NQueen::get_results() {
    if (!_runned) {
        run();
    }
    return _result;
}
