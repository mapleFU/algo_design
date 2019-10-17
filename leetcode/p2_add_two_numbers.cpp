//
// Created by 付旭炜 on 2019/7/6.
//

#include "link_list.h"
#include <iostream>
#include <tuple>

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
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        // return two nullptr for nodes
        ListNode *head = nullptr;
        ListNode *tail = nullptr;

        int carry = 0;

        while (true) {
            bool list_1_end = l1 == nullptr;
            bool list_2_end = l2 == nullptr;

            int add1 = 0;
            int add2 = 0;
            // 注意这里 carry 需要是0!!!
            if (list_1_end && list_2_end && carry == 0) {
                return head;
            } else {
                add1 = get_add(l1);
                add2 = get_add(l2);
            }
            // handing carry and add
            //            std::cout << "carry is " << carry << "; add1 is " <<
            //            add1 << "; add2 is " << add2;
            int sum = add1 + add2 + carry;
            //            std::cout << "      Sum is" << sum << '\n';
            carry = sum / 10;
            int val = sum % 10;

            ListNode *node = new ListNode(val);
            if (head == nullptr) {
                head = node;
            } else {
                tail->next = node;
            }

            tail = node;

            move_list(l1);
            move_list(l2);
        }
    }

  private:
    int get_add(const ListNode *node) {
        if (node == nullptr) {
            return 0;
        }
        return node->val;
    }

    void move_list(ListNode *&node) {
        if (node == nullptr) {
            return;
        }
        node = node->next;
    }
};

int main() {
    // 342 + 465 = 807.
    auto list1 = make_list({2, 4, 3});
    auto list2 = make_list({5, 6, 4, 1});
    //    auto expected = make_list();
    print_list(list1);
    print_list(list2);

    Solution *sol = new Solution();
    auto answer = sol->addTwoNumbers(list1, list2);
    print_list(answer);

    std::cout << list_checker(answer, {7, 0, 8, 1}) << '\n';

    list1 = make_list({5});
    list2 = make_list({5});
    //    auto expected = make_list();
    print_list(list1);
    print_list(list2);
    answer = sol->addTwoNumbers(list1, list2);
    print_list(answer);

    std::cout << list_checker(answer, {0, 1}) << '\n';
}