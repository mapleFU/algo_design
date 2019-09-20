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
#include <memory>

class Solution {
public:
    //  2->3->4
    //  n  c
    //  3->3->4
    //  3---->4 , del 3
    void deleteNode(ListNode* node) {

        node->val = node->next->val;
        node->next = node->next->next;
        if (node->next != nullptr) {
            delete node->next;
        }
    }
};

int main() {

}