#include "common_use.h"

using namespace std;

class Solution {
public:
    // Counting bits should obey the rule:
    // 0 is 0, 1 is 1
    // f[x] = f[x << 1] + x % 1
    vector<int> countBits(int num) {
        vector<int> count_bits(num + 1, 0);
        for (unsigned i = 0; i <= num; ++i) {
            count_bits[i] = count_bits[i / 2] + (i & 1);
        }
        return count_bits;
    }
};

int main() {
    Solution soln;
    print_perms(soln.countBits(3));
    print_perms(soln.countBits(5));
}