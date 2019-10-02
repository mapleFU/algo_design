//
// Created by 付旭炜 on 2019/10/2.
//

#include "common_use.h"
#include <functional>

using namespace std;

class KthLargest {
    static void filter_down(std::vector<int> &nums, int pos, int size,
                            const std::function<bool(int, int)> &comp) {
        //        if (pos * 2 >= size ) return; // do nothing
        bool needs_iter = true;
        while (pos * 2 + 1 < size && needs_iter) {
            int left_child_pos = pos * 2 + 1;
            int right_child_pos = left_child_pos + 1;
            // find the smallest
            int next_pos;
            next_pos =
                comp(nums[pos], nums[left_child_pos]) ? pos : left_child_pos;
            if (right_child_pos < size) {
                next_pos = comp(nums[next_pos], nums[right_child_pos])
                               ? next_pos
                               : right_child_pos;
            }

            if (next_pos == pos) {
                // 堆序满足
                needs_iter = false;
            } else {
                std::swap(nums[pos], nums[next_pos]);
                pos = next_pos;
            }
        }
    }

    static void filter_up(std::vector<int> &nums, int pos, int size,
                   const std::function<bool(int, int)> &comp) {}

    // 应该 build 一个 size_ == k 的最小堆
    void build_heap() {
        // TODO: implement this
        // 最后一个节点序号是 heap_sz_ - 1
        // 层序遍历第 i 层 有 2^i 个元素，其之前是这个数目的累加，有 2^1 - 1 个
        // 一个节点的父节点 应该是 (x - 1) / 2, 儿子 (x * 2) + 1, (x * 2) + 2
        int end_node = std::min(static_cast<int>(nums_.size()), heap_sz_);
        int start = (end_node - 1) / 2;
        for (int i = start; i >= 0; --i) {
            filter_down(nums_, i, heap_sz_, std::less<>());
        }
        //        nums_.resize(heap_sz_);
    }

    int heap_sz_;
    std::vector<int> nums_;
    // 边界条件：考虑现有空间不足
    bool already_built;

  public:
    KthLargest(int k, vector<int> &nums)
        : heap_sz_(k), nums_(nums), already_built(false) {
        if (nums_.size() > k - 1) {
            already_built = true;
            // nums is a heap now
            build_heap();
            for (size_t i = k; i < nums_.size(); ++i) {
                add(nums_[i]);
            }
            nums_.resize(heap_sz_);
        }
    }

    int add(int val) {
        if (!already_built) {
            nums_.push_back(val);

            build_heap();
            for (size_t i = heap_sz_; i < nums_.size(); ++i) {
                add(nums_[i]);
            }
            nums_.resize(heap_sz_);

            already_built = true;
        } else if (val > nums_[0]) {
            // neads insert
            nums_[0] = val;
            filter_down(nums_, 0, heap_sz_, std::less<>());
        }
        return nums_[0];
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

/// ```
/// int k = 3;
/// int[] arr = [4,5,8,2];
/// KthLargest kthLargest = new KthLargest(3, arr);
/// kthLargest.add(3);   // returns 4
/// kthLargest.add(5);   // returns 5
/// kthLargest.add(10);  // returns 5
/// kthLargest.add(9);   // returns 8
/// kthLargest.add(4);   // returns 8
/// ```
int main() {


    {
        vector<int> testing{4, 5, 8, 2};
        int k = 3;
        KthLargest kthLargest(k, testing);
        cout << kthLargest.add(3) << '\n';  // 2 3 4 5 8
        cout << kthLargest.add(5) << '\n';  // 2 3 4 5 5 8
        cout << kthLargest.add(10) << '\n'; // 2 3 4 5 5 8 10
        cout << kthLargest.add(9) << '\n';  // 2 3 4 5 5 8 9 10
        cout << kthLargest.add(4) << '\n'; // 2 3 4 4 5 5 8 9 10
    }

    cout << "\n\n";

    {
        // 4 5 8 2 -> 2 4 5 8
        vector<int> testing{4, 5, 8, 2};
        int k = 4;
        KthLargest kthLargest(k, testing); // 2 4 5 8 -> 4 5 8 2

        cout << kthLargest.add(3) << '\n';
        cout << kthLargest.add(5) << '\n';
        cout << kthLargest.add(10) << '\n';
        cout << kthLargest.add(9) << '\n';
        cout << kthLargest.add(4) << '\n';
    }

    cout << "\n\n";

    {
        // 4 5 8 2 -> 2 4 5 8
        vector<int> testing{4, 5, 8, 2};
        int k = 5;
        KthLargest kthLargest(k, testing); // 2 4 5 8 -> 4 5 8 2

        cout << kthLargest.add(3) << '\n';
        cout << kthLargest.add(5) << '\n';
        cout << kthLargest.add(10) << '\n';
        cout << kthLargest.add(9) << '\n';
        cout << kthLargest.add(4) << '\n';
    }
}