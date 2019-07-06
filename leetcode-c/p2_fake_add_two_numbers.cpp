//
// Created by 付旭炜 on 2019/7/6.
//

#include <iostream>
#include <tuple>
#include "link_list.h"

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 *
 * 这里我考虑的是递归到最后一位，相加然后拿到一个c，丢给上面的一位
 * 但是我题目意思好像理解错了
 */
class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        // return two nullptr for nodes
        if (l1 == nullptr) {
            return l2;
        }
        if (l2 == nullptr) {
            return l1;
        }
        ListNode* node;
        int carry;
        // carry point
        std::tie(node, carry) = sub_add(l1, l2);
        if (carry != 0) {
            // if node is nullptr
            // for 0 1->0
            ListNode* head = new ListNode(carry);
            head->next = node;
            node = head;
        }
        return node;
    }

private:
    // 返回值代表 carry 和返回的 Linked List
    std::tuple<ListNode*, int> sub_add(ListNode* sub1, ListNode* sub2) {
        int sub1_is_end = sub1->next == nullptr;
        int sub2_is_end = sub2->next == nullptr;

        if (sub1_is_end && sub2_is_end) {
            // 递归基
            int val = sub1->val + sub2->val;
            // split val to self and carry
            int self = val % 10;
            int carry = val / 10;
            ListNode* node = new ListNode(self);
            return std::make_tuple(node, carry);
        } else if (sub1_is_end) {

            return sub_add(sub1, sub2->next);
        } else if (sub2_is_end){
            return sub_add(sub1->next, sub2);
        } else {
            ListNode* node;
            int carry;
            // carry point
            std::tie(node, carry) = sub_add(sub1->next, sub2->next);
//            print_list(node);
//            std::cout << "Carry is " << carry << '\n';
            int val = sub1->val + sub2->val + carry;
            int self = val % 10;
            int r_carry = val / 10;
            ListNode* r_node = new ListNode(self);
            r_node->next = node;

            return std::make_tuple(r_node, r_carry);
        }
    }
};

int main() {
    auto list1 = make_list({1, 2, 3, 4, 5});
    auto list2 = make_list({5, 4, 3, 2, 1});
    print_list(list1);
    print_list(list2);

    Solution* sol = new Solution();
    print_list(sol->addTwoNumbers(list1, list2));
}