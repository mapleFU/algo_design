//
// Created by 付旭炜 on 2019/7/7.
//

#include <iostream>
#include <string>

using namespace std;

/**
 * 映射关系：
 * (numRow - 1) 为一组
 * 第k组
 * 1: [0-(numRow - 1)] * (k-1)
 * 2...
 */
class Solution {
public:
    string convert(string s, int numRows) {
        if (numRows <= 1) {
            return s;
        }


        // format
        auto format_edge = [numRows](int line_num, int cnt) {
            return (numRows - 1) * cnt * 2 + line_num;
        };

        auto incline_edge = [numRows](int line_num, int cnt) {
            return (numRows - 1) * 2 * cnt - line_num;
        };
        // 最大的 groups
        int max_groups = (s.length() / (2 * numRows - 2)) ;

        int remain_nodes = s.length() % (2 * numRows - 2) ;

        int remain_lines = 0;
        if (remain_nodes == 0) {
            remain_lines = 0;
        } else if (remain_nodes <= numRows - 1) {
            remain_lines = 1;
        } else {
            remain_lines = remain_nodes - (numRows - 1);
        }
        int sum_lines = max_groups * (numRows - 1) + remain_lines;

//        cout << max_groups << ' ' << remain_lines << ' ' << remain_nodes << '\n';
        // 开始吧
        string ret_s;
        for (int i = 0; i < numRows; ++i) {
            // n 行

            // 先对 max_group 填充
            for (int j = 0; j < max_groups; ++j) {
                auto c1 = s[format_edge(i, j)];
                ret_s.push_back(c1);
                auto c2 = s[incline_edge(i, j + 1)];
                // 不在最大的地方就添加
                if (i != 0 && i != numRows - 1) {
                    ret_s.push_back(c2);
                }
            }
            // 补 i 行的, 剩余的点比i大
            if (remain_nodes > i) {
                auto pos = format_edge(i, max_groups);
//                cout << "Pos " << pos << '\n';
                auto c1 = s[pos];

//                cout << "push " << c1 << " in " << pos << '\n';
                ret_s.push_back(c1);
            }
            if (remain_nodes > (numRows - 1) && remain_nodes > (2 * numRows - 2 - i)) {
                int cn = incline_edge(i, max_groups + 1);
//                cout << "Pos " << cn << '\n';
                auto c2 = s[cn];
//                cout << "push " << c2 << " in " << cn << '\n';

                if (i != 0 && i != numRows - 1 && cn < s.length()) {
                    ret_s.push_back(c2);
                }
            }

        }

        return ret_s;
    }
};

int main() {
    Solution solution;

    cout << solution.convert("PAYPALISHIRING", 3) << '\n';
    cout << solution.convert("PAYPALISHIRING", 4) << '\n';
    cout << solution.convert("PAYPALISHIRING", 3).compare("PAHNAPLSIIGYIR") << '\n';
    cout << solution.convert("PAYPALISHIRING", 4).compare("PINALSIGYAHRPI") << '\n';
    cout << solution.convert("nmsl", 1).compare("nmsl") << '\n';
    cout << solution.convert("nmsl", 2).compare("nsml") << '\n';

    string s("wlrbbmqbhcdarzowkkyhiddqscdxrjmowfrxsjybldbefsarcbynecdyggxxpklorellnmpapqfwkhopkmco");
    int cnt = 61;
    cout << solution.convert(s, cnt) << '\n';


}