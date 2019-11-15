#include "link_list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

using namespace std;

using ListNodePtr = ListNode *;

inline void unsafe_to_next(ListNodePtr& node) {
    node = node->next;
}
inline bool ending(ListNodePtr node) { return node == nullptr; }

inline void to_next(ListNodePtr& node) {
    if (node != nullptr) unsafe_to_next(node);
}


/// Algorithm description:
/// https://leetcode.com/problems/linked-list-cycle-ii/discuss/44781/Concise-O(n)-solution-by-using-C%2B%2B-with-Detailed-Alogrithm-Description
///
/// l1: distance between the head point and entry point
/// l2: distance between the entry point and the meeting point
/// d : length of the cycle
///
/// When they meet: faster traversed

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (head == nullptr) return nullptr;
        ListNodePtr slow = head, fast = head->next;
        while (!ending(fast) && slow != fast) {
            to_next(slow);
            to_next(fast), to_next(fast);
        }
        if (slow != fast) {
            return nullptr;
        }
        // fast runs d faster than slow.
        // 2*(l1 + l2) = (l1 + l2 + d)
        // l1 + l2 = d
        // So we need to getting l1 = d - l2
        // Note: d - l2 == slow to entry point.

        ListNodePtr entry = head;
        unsafe_to_next(slow);

        while(slow != entry) {               // found the entry location
            unsafe_to_next(slow);
            unsafe_to_next(entry);
        }

        return slow;
    }
};

int main() {

    Solution soln;

    {
        ListNode* head = make_list({3, 2, 0, 4});
        {
            ListNode* tmp_tail = tail(head);
            tmp_tail->next = head->next;
        }
        soln.detectCycle(head);
    }
}