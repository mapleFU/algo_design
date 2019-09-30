//
// Created by 付旭炜 on 2019/3/24.
//
#include <iostream>
#include <vector>

using namespace std;

class Solution {

    int fetchNext(const vector<int> &nums1, const vector<int> &nums2, int &p1,
                  int &p2) {
        if (nums1.size() > p1 && nums2.size() > p2) {
            if (nums1[p1] < nums2[p2]) {
                return nums1[p1++];
            } else {
                return nums2[p2++];
            }
        }

        if (nums1.size() > p1) {
            return nums1[p1++];
        }

        if (nums2.size() > p2) {
            return nums2[p2++];
        }

        // something bad happened
        return -1;
    }

  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
        auto nums = nums1.size() + nums2.size();
        if (nums == 0) {
            return 0;
        }
        int mid = (nums - 1) / 2;
        int p1 = 0, p2 = 0;
        double result = -1;

        for (int i = 0; i < mid; ++i) {
            fetchNext(nums1, nums2, p1, p2);
        }
        result = fetchNext(nums1, nums2, p1, p2);
        if (nums % 2 == 0) {
            result += fetchNext(nums1, nums2, p1, p2);
            result /= 2;
        }
        return result;
    }
};

int main() {
    Solution solution;

    vector<int> nums1_1{1, 3};
    vector<int> nums1_2{2};
    cout << solution.findMedianSortedArrays(nums1_1, nums1_2) << '\n';

    vector<int> nums2_1{1, 2};
    vector<int> nums2_2{3, 4};
    cout << solution.findMedianSortedArrays(nums2_1, nums2_2) << '\n';
}