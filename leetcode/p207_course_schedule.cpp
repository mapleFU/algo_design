#include "common_use.h"

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        // if the graph is a DAG, it can be solved
        std::vector<int> in_counter(numCourses);    // in_counter
        std::unordered_map<int, vector<int>> count_graph;

        for(const auto prerequisite: prerequisites) {
            // prerequisite means (a <-- b),
            ++in_counter[prerequisite[0]];
            count_graph[prerequisite[1]].push_back(prerequisite[0]);
        }
        std::queue<int> countings;

        for (int i = 0; i < numCourses; ++i) {
            if (in_counter[i] == 0) countings.push(i);
        }

        while (!countings.empty()) {
            int top = countings.front();
            countings.pop();

            for(int target: count_graph[top]) {
                if (--in_counter[target] == 0) {
                    countings.push(target);
                }
            }
        }

        return std::all_of(in_counter.cbegin(), in_counter.cend(), [](auto v) {
            return v == 0;
        });
    }
};

int main() {
    Solution soln;

    std::vector<vector<int>> args;
    int cnt;
    args = {
            {1, 0},
    };
    cnt = 2;
    cout << soln.canFinish(cnt, args) << endl;
    args = {
            {1, 0},
            {0, 1},
    };
    cnt = 2;
    cout << soln.canFinish(cnt, args) << endl;
}