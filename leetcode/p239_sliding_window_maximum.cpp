#include "common_use.h"
#include <deque>
#include <utility>
#include <list>

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

class SolutionIndexOpt {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        std::deque<int> monotonous_queue;
        int cnt(0);
        std::vector<int> result;
        // If c larger than tail, pop the tail.
        for (auto c: nums) {
            ++cnt;
            while (!monotonous_queue.empty() && nums[monotonous_queue.back()] < c) {
                monotonous_queue.pop_back();
            }
            monotonous_queue.push_back(cnt - 1);
            if (cnt - 1 - monotonous_queue.front() >= k) {
                monotonous_queue.pop_front();
            }
            if (cnt < k) {
                continue;
            } else {
                result.push_back(nums[monotonous_queue.front()]);
            }
        }
        return result;
    }
};

int main() {
    SolutionIndexOpt soln;
    vector<int> test_data {1,3,-1,-3,5,3,6,7};
    print_perms(soln.maxSlidingWindow(test_data, 3));
}