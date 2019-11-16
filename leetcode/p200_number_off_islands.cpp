#include "common_use.h"

using namespace std;

constexpr char LAND = '1';
constexpr char WATER = '0';

class Solution {
    // mark right and down
    void dfs_mark(const vector<vector<char>> &grid, vector<vector<bool>> &mark,
                  int x, int y) {
        // handle coasts
        if (x >= grid.size() || y >= grid[0].size() || x < 0 || y < 0)
            return;

        if (grid[x][y] == WATER || mark[x][y])
            return;
        mark[x][y] = true;

        dfs_mark(grid, mark, x + 1, y);
        dfs_mark(grid, mark, x, y + 1);
        dfs_mark(grid, mark, x - 1, y);
        dfs_mark(grid, mark, x, y - 1);
    }

  public:
    int numIslands(vector<vector<char>> &grid) {
        if (grid.empty())
            return 0;

        vector<vector<bool>> occupied_grids;

        // Note: reserve only mark the capacity.
        occupied_grids.resize(grid.size());

        for (auto &v : occupied_grids) {
            v.resize(grid[0].size());
        }

        int cnt{};
        for (int i = 0; i < grid.size(); ++i) {
            for (int j = 0; j < grid[0].size(); ++j) {
                // (i, j) is unmarked
                if (!occupied_grids[i][j] && grid[i][j] == LAND) {
                    ++cnt;
                    dfs_mark(grid, occupied_grids, i, j);
                } else if (!occupied_grids[i][j]) {
                    occupied_grids[i][j] = true;
                }
            }
        }
        return cnt;
    }
};

int main() {
    vector<vector<char>> testing = {
        {'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'},
        {'0', '0', '0', '0', '0'},
    };
    Solution soln;
    cout << soln.numIslands(testing) << '\n';

    testing = {
        {'1', '1', '1', '1', '0'}, {'1', '1', '0', '1', '0'},
        {'1', '1', '0', '0', '1'}, {'0', '0', '1', '0', '0'},
        {'1', '0', '0', '1', '1'},
    };
    cout << soln.numIslands(testing) << '\n';

    testing = {
        {'1', '1', '1'},
        {'0', '1', '0'},
        {'1', '1', '1'},
    };
    cout << soln.numIslands(testing) << '\n';
}