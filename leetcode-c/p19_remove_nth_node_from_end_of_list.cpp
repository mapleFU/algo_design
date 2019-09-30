//
// Created by 付旭炜 on 2019/9/17.
//

#include "common_use.h"
#include "link_list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
  public:
    // remove nth from end
    // 1->2->3->4->5
    // 1->2   ->4->5
    //       p1    p2
    ListNode *removeNthFromEnd(ListNode *head, int n) {
        if (head == nullptr) {
            return nullptr;
        }
        ListNode *prev_cursor = nullptr;
        ListNode *post_cursor = head;
        int counter = 0;
        // seek n 次
        while (post_cursor->next != nullptr && counter < n - 1) {
            ++counter;
            post_cursor = post_cursor->next;
        }
        while (post_cursor->next != nullptr) {
            if (prev_cursor == nullptr) {
                prev_cursor = head;
            } else {
                prev_cursor = prev_cursor->next;
            }
            post_cursor = post_cursor->next;
        }
        if (prev_cursor == nullptr) {
            head = head->next;
            return head;
        }
        prev_cursor->next = prev_cursor->next->next;
        return head;
    }
};

int main() {
    Solution soln;

    auto test_list = make_list({1, 2, 3, 4, 5});
    print_list(test_list);
    print_list(soln.removeNthFromEnd(test_list, 2));
    test_list = make_list({1, 2, 3, 4, 5});
    assert(list_checker(soln.removeNthFromEnd(test_list, 2), {1, 2, 3, 5}));
    test_list = make_list({1, 2, 3, 4, 5});
    assert(list_checker(soln.removeNthFromEnd(test_list, 5), {2, 3, 4, 5}));
}