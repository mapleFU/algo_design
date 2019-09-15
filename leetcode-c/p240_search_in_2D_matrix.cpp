//
// Created by 付旭炜 on 2019/9/15.
//
#include "common_use.h"

using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        // do asserts

        // do checkings
        if (matrix.size() == 0 || matrix[0].size() == 0) {
            return false;
        }

        const int ROW = matrix.size();
        const int COL = matrix[0].size();
        // initialize rows and cols
        int row = 0, col = COL - 1;
        bool found = false;
        while (row < ROW && col >= 0) {
            if (matrix[row][col] == target) {
                found = true;
                break;
            }
            if (matrix[row][col] > target) {
                --col;
            } else if (matrix[row][col] < target) {
                ++row;
            }
        }
        return found;
    }
};


int main() {

    vector<vector<int>> vec {
            {1,   4,  7, 11, 15},
            {2,   5,  8, 12, 19},
            {3,   6,  9, 16, 22},
            {10, 13, 14, 17, 24},
            {18, 21, 23, 26, 30},
    };
    Solution soln;

    assert(soln.searchMatrix(vec, 1) == true);
    assert(soln.searchMatrix(vec, 33) == false);

    vector<vector<int>> vec2 {
            {1,  1},
    };
    assert(soln.searchMatrix(vec2, 2) == false);
}