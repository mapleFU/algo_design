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

inline bool ending(ListNodePtr node) { return node == nullptr; }

inline void to_next(ListNodePtr& node) {
    if (node != nullptr) node = node->next;
}

class Solution {

  public:
    bool hasCycle(ListNode *head) {
        if (head == nullptr)
            return false;
        ListNodePtr slow = head, fast = head->next;
        // 快慢指针
        while (!ending(fast) && slow != fast) {
            to_next(fast);
            to_next(fast);
            to_next(slow);
        }
        return slow == fast;
    }
};