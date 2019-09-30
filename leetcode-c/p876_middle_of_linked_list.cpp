//
// Created by 付旭炜 on 2019/3/24.
//

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
#include "link_list.h"

class Solution {
  public:
    ListNode *middleNode(ListNode *head) {
        int size = 0;
        ListNode *cur = head;
        while (cur) {
            cur = cur->next;
            ++size;
        }
        cur = head;
        int pos = size / 2;
        while (pos--) {
            cur = cur->next;
        }
        return cur;
    }
};

class SolutionTwoPointer {
  public:
    ListNode *middleNode(ListNode *head) {
        // slow , fast pointer
        // 1 2 3 4 5
        // sf
        //   s f
        //     s   f

        // 1 2 3 4 5 6
        //   s f
        //     s   f
        //       s     f
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};