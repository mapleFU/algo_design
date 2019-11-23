#include <cassert>
#include <memory>
#include <stack>
#include "common_use.h"

using namespace std;

class NumArray {
    // in fenwick tree, the array with index manages zero before 1.
    // IEEE integer get complement means (reversed) + 1.
    int lowbit(int x) {
        return (x & -x);
    }

    int getsum(int x) {  // a[1]……a[x]的和
        int ans = 0;
        while (x > 0) {
            ans = ans + binary_index_tree[x];
            x = x - lowbit(x);
        }
        return ans;
    }

    std::vector<int> binary_index_tree;
    std::vector<int> origin;
public:
    // Build fenwick tree
    // 1. Initialize `binary_index_tree` with size + 1 (the target begins with index 1).
    NumArray(vector<int>& nums): binary_index_tree(nums.size() + 1), origin(nums) {
        auto sz = nums.size();
        for (int i = 1; i <= sz; ++i) {
            binary_index_tree[i] += nums[i - 1];
            int j = i + lowbit(i);
            // inc father with current
            if (j <= sz) binary_index_tree[j] += binary_index_tree[i];
        }
//        print_perms(origin);
//        print_perms(binary_index_tree);
    }

    void add(int i, int val) {
        // the current point += val
        assert(i < binary_index_tree.size());
        int current_index = i + 1;
        // add to it's fathers.
        while (current_index < binary_index_tree.size()) {
            binary_index_tree[current_index] += val;
            current_index = current_index + lowbit(current_index);
        }
//        print_perms(origin);
//        print_perms(binary_index_tree);
    }

    void update(int i, int val) {
        assert(i < origin.size());
        int to_add = val - origin[i];
//        cout << "to_add == " << to_add << '\n';
        this->add(i, to_add);
        origin[i] = val;
//        print_perms(origin);
//        print_perms(binary_index_tree);
    }

    int sumRange(int i, int j) {
        return getsum(j + 1) - getsum(i + 1 - 1);
    }
};

class SegmentTree {
    struct SegmentTreeNode {
        int sum {0} ;
        int low ;
        int high;

        int inc_marker_ {0};

        std::unique_ptr<SegmentTreeNode> left_ {nullptr};
        std::unique_ptr<SegmentTreeNode> right_ {nullptr};

        int mid() const {
            return (high - low) / 2 + low;
        }
    };

    std::unique_ptr<SegmentTreeNode> root_ {nullptr};

    std::unique_ptr<SegmentTreeNode> build(int lower, int upper, const vector<int>& numbers) {
        auto current = make_unique<SegmentTreeNode>();
        current->low = lower; current->high = upper;
        if (upper == lower) {
            current->sum = numbers[upper];
            return current;
        }
        current->left_ = build(lower, current->mid(), numbers);
        if (current->mid() == upper) {
            current->sum = current->left_->sum;
            return current;
        }
        current->right_ = build(current->mid() + 1, upper, numbers);
        // recursively done it.
        current->sum = current->left_->sum + current->right_->sum;
        return current;
    }

    int sumRange(int low, int high, const SegmentTreeNode* node) {
        if (node == nullptr) {
            return 0;
        }
        assert(node != nullptr);
        assert(high <= node->high && low >= node->low);
        int sum {0};
        int mid = node->mid();
        // just matching the range
        if (low == node->low && high == node->high) {
            return node->sum;
        }
        // [low, mid, high]
        //   [nl, nh]
        if (high <= mid) {
            // single side
            return sumRange(low, high, node->left_.get());
        };
        if (low > mid) {
            return sumRange(low, high, node->right_.get());
        }
        return sumRange(low, mid, node->left_.get()) + sumRange(mid + 1, high, node->right_.get());
    }
public:
    SegmentTree(vector<int>& nums) {
        int beg = nums.size();

        root_ = make_unique<SegmentTreeNode>();
        // setting [low, high] for the root.
        root_->low = 0;
        root_->high = nums.size() - 1;
        int mid = root_->mid();
        root_->left_ = build(root_->low, mid, nums);
        root_->right_ = build(mid + 1, root_->high, nums);
        root_->sum = root_->left_->sum + root_->right_->sum;
    }

    void update(int i, int val) {
        // single point update
        // [i, i]
        SegmentTreeNode* current = root_.get();
        std::stack<SegmentTreeNode*> routes;
        while (current != nullptr && current->high != current->low) {
            int mid = current->mid();
            routes.push(current);
            if (i <= mid) {
                current = current->left_.get();
            } else {
                current = current->right_.get();
            }
        }

        if (current == nullptr) return;
        assert(current->high == i);
        int delta = val - current->sum;
        current->sum = val;
        while (!routes.empty()) {
            current = routes.top();
            current->sum += delta;
            routes.pop();
        }
    }

    int sumRange(int i, int j) {
        SegmentTreeNode* current = root_.get();
        return sumRange(i, j, current);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(i,val);
 * int param_2 = obj->sumRange(i,j);
 */

template <typename TestClass>
void testing() {
    vector<int> nums = {1, 3, 5};
    {
        // 1 3 5
        // 1 4 5
        TestClass obj(nums);
        cout << obj.sumRange(0, 2) << endl;
        obj.update(1, 2);
        cout << obj.sumRange(0, 2) << endl;
    }

    nums = {9, -8};
    {
        TestClass obj(nums); // 9, 1 (9, -8)
        obj.update(0, 3); // 3, -5 (3, -8)
        cout << obj.sumRange(1, 1) << endl; // 1, 1 --> -8
        cout << obj.sumRange(0, 1) << endl;
        obj.update(1, -3);
        cout << obj.sumRange(0, 1) << endl;
    }

    nums = {7, 2, 7, 2, 0};
    {
        TestClass obj(nums); // 7 2 7 2 0 (0 7 9 7 11 0)
        obj.update(4, 6);  // 7 2 7 2 6 (0 7 9 7 11 6)
        obj.update(0, 2);  // 2 2 7 2 6 (0 2 4 7 6 6)
        obj.update(0, 9);  // 9 2 7 2 6 (0 9 11 7 13 6 )
        cout << obj.sumRange(4, 4) << endl;
        obj.update(3, 8); // 9 2 7 8 6  (0 9 11 7 19 6 )
        cout << obj.sumRange(0, 4) << endl;
    }

}

int main() {
    testing<NumArray>();

    cout << "\n\n";

    testing<SegmentTree>();
}