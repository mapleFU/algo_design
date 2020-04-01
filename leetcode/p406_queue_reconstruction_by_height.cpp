#include "common_use.h"
#include <list>

using namespace std;

class Solution {
public:
    // vector<int> is like [7, 1]
    // the first means value, the second means the rank.
    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        // TODO: make clear the right call of std::sort.
        // 返回 true, 表示 `func(前面, 后面) == true`
        std::sort(people.begin(), people.end(), [](const std::vector<int>& v1, const std::vector<int>& v2) {
            if (v1[0] != v2[0]) {
                return v1[0] > v2[0];
            } else {
                return v1[1] < v2[1];
            }
        });

        // maybe a skiplist is a better choice.
        std::vector<int> res;
        for (int i = 0; i < people.size(); ++i) {
            if (res.size() <= people[i][1]) {
                res.push_back(i);
            } else {
                res.insert(res.begin() + people[i][1], i);
            }
        }
        std::vector<std::vector<int>> res_final(res.size());
        {
            int i = 0;
            for (int re : res) {
                res_final[i++] = people[re];
            }
        }
        return res_final;
    }
};

int main() {
    Solution soln;
    std::vector<std::vector<int>> test_vec {
            {7, 0},
            {4, 4},
            {7, 1},
            {5, 0},
            {6, 1},
            {5, 2},
    };
    print_perms(soln.reconstructQueue(test_vec));
}