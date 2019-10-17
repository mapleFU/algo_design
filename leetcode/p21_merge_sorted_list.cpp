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
    void stepNext(ListNode *&l) {
        if (l)
            l = l->next;
    }

  public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2) {
        ListNode *n1 = l1, *n2 = l2;
        ListNode *new_list_head = nullptr;
        ListNode *new_list_tail = nullptr;

        while (true) {
            ListNode *current;
            if (n1 && n2) {

                if (n1->val < n2->val) {
                    current = n1;
                    stepNext(n1);
                } else {
                    current = n2;
                    stepNext(n2);
                }
            } else if (n1) {
                current = n1;
                stepNext(n1);
            } else {
                current = n2;
                stepNext(n2);
            }

            if (current == nullptr) {
                return new_list_head;
            }
            if (new_list_head == nullptr) {
                new_list_head = new_list_tail = current;
            } else {
                new_list_tail->next = current;
                new_list_tail = new_list_tail->next;
            }
        }
    }
};