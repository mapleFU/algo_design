#include "common_use.h"

using namespace std;
class Solution {
  public:
    int minDistance(string word1, string word2) {
        size_t sx = word1.size();
        size_t sy = word2.size();
        // dp: an array of (sx + 1) * (sy + 1)
        vector<vector<int>> dp_vec(sx + 1, vector<int>(sy + 1));
        for (int i = 0; i <= sx; ++i) {
            dp_vec[i][0] = i;
        }
        for (int i = 0; i <= sy; ++i) {
            dp_vec[0][i] = i;
        }

        for (int i = 1; i <= sx; ++i) {
            for (int j = 1; j <= sy; ++j) {
                // 1. if word1[j] == word2[i],
                if (word1[i - 1] == word2[j - 1]) {
                    dp_vec[i][j] = dp_vec[i - 1][j - 1];
                } else {
                    // 2. min of three below
                    // 2.1 add a letter in word1
                    int arm1 = dp_vec[i - 1][j];

                    int arm2 = dp_vec[i][j - 1];

                    int arm3 = dp_vec[i - 1][j - 1];
                    dp_vec[i][j] = std::min({arm1, arm2, arm3}) + 1;
                }
            }
        }
        print_perms(dp_vec);
//        for (const auto& dp: dp_vec) {
//            print_perms(dp);
//        }
//        print_perms(dp_vec);

        return dp_vec[sx][sy];
    }
};

int main() {
    Solution soln;
    string s1 = "horse", s2 = "ros";
    cout << soln.minDistance(s1, s2) << endl;

    s1 = "intention", s2 = "execution";
    cout << soln.minDistance(s1, s2) << endl;
}