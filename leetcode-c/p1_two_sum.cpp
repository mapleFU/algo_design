//
// Created by 付旭炜 on 2019/3/24.
//

#include <vector>
#import "common_use.h"
#include <iostream>
#include <unordered_map>

using namespace std;

/**
 * 用哈希记录历史信息，查找到对应的，有就提交
 *
 */
class HashSolution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int > uset;
        for (int i = 0; i < nums.size(); ++i) {
            auto to_find = uset.find(nums[i]);
            if (to_find != uset.end()) {
                // found it
                // 返回对应的 vector
                return vector<int>{
                    to_find->second,
                    i
                };
            }
            // target = nums[i]
            // 把"目标" 放到 set 里，方便进行测试
            uset[target - nums[i]] = i;

        }
        return vector<int>{};
    }
};

class SolutionRecursively {
    bool checkOk(vector<int>& used, int target) {
        return used.size() == 2 && target == 0;
    }
    bool twoSum(vector<int> &used, int target, const vector<int>& origin, int index) {
        if (index == origin.size()) {
            return target == 0 && used.size() == 2;
        }
        if (used.size() == 2) {
            return checkOk(used, target);
        }

        // 没有假定所有数据>0, 不要根据这个优化
        bool test_not_use = false;
        bool ok;
            // use this
        used.push_back(index);
        ok = twoSum(used, target - origin[index], origin, index + 1);
        if (ok) {
            return ok;
        } else {
            used.pop_back();
        }

        return twoSum(used, target, origin, index + 1);
    }
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        // dfs?
        vector<int> use_vec;
        twoSum(use_vec, target, nums, 0);
        return use_vec;
    }
};

class SolutionLoop {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i + 1; j < nums.size(); ++j) {
                if (nums[i] + nums[j] == target) {
                    return vector<int>{i, j};
                }
            }
        }
        return vector<int>{};
    }
};


/**
0 1
1 2
0 3
0 2

1 2
 2 4
 */
int main() {
    HashSolution solution;
    vector<int> vec{2, 7, 12, 19};
    print_perms(solution.twoSum(vec, 9));
    print_perms(solution.twoSum(vec, 19));
//
    vector<int> vec2{0, 4, 3, 0};
    print_perms(solution.twoSum(vec2, 0));
    print_perms(solution.twoSum(vec2, 3));
    print_perms(solution.twoSum(vec2, 6));

    vector<int> vec3{3, 2, 4};
    print_perms(solution.twoSum(vec3, 6));

    vector<int> vec4{-1,-2,-3,-4,-5};
    print_perms(solution.twoSum(vec4, -8));
}