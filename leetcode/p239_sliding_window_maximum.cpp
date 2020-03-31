#include "common_use.h"
#include <deque>
#include <utility>

using namespace std;

// https://oi-wiki.org/ds/monotonous-queue/
// This problem is a monotonous queue problem.

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::deque<std::pair<int, int>> monotonous_queue;
        int cnt(0);
        std::vector<int> result;
        // If c larger than tail, pop the tail.
        for (auto c: nums) {
            ++cnt;
            while (!monotonous_queue.empty() && monotonous_queue.back().first < c) {
                monotonous_queue.pop_back();
            }
            monotonous_queue.emplace_back(c, cnt);
            if (cnt - monotonous_queue.front().second >= k) {
                monotonous_queue.pop_front();
            }
            if (cnt < k) {
                continue;
            } else {
                result.push_back(monotonous_queue[0].first);
            }
        }
        return result;
    }
};

int main() {
    Solution soln;
    vector<int> test_data {1,3,-1,-3,5,3,6,7};
    print_perms(soln.maxSlidingWindow(test_data, 3));
}