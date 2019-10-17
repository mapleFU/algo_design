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
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

void trimLeftTrailingSpaces(string &input) {
    input.erase(input.begin(), find_if(input.begin(), input.end(),
                                       [](int ch) { return !isspace(ch); }));
}

void trimRightTrailingSpaces(string &input) {
    input.erase(find_if(input.rbegin(), input.rend(),
                        [](int ch) { return !isspace(ch); })
                    .base(),
                input.end());
}

vector<int> stringToIntegerVector(string input) {
    vector<int> output;
    trimLeftTrailingSpaces(input);
    trimRightTrailingSpaces(input);
    input = input.substr(1, input.length() - 2);
    stringstream ss;
    ss.str(input);
    string item;
    char delim = ',';
    while (getline(ss, item, delim)) {
        output.push_back(stoi(item));
    }
    return output;
}

ListNode *stringToListNode(string input) {
    // Generate list from the input
    vector<int> list = stringToIntegerVector(input);

    // Now convert that list into linked list
    ListNode *dummyRoot = new ListNode(0);
    ListNode *ptr = dummyRoot;
    for (int item : list) {
        ptr->next = new ListNode(item);
        ptr = ptr->next;
    }
    ptr = dummyRoot->next;
    delete dummyRoot;
    return ptr;
}

string listNodeToString(ListNode *node) {
    if (node == nullptr) {
        return "[]";
    }

    string result;
    while (node) {
        result += to_string(node->val) + ", ";
        node = node->next;
    }
    return "[" + result.substr(0, result.length() - 2) + "]";
}

class Solution {
    void stepNext(ListNode *&l) {
        if (l)
            l = l->next;
    }

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

    ListNode *middleNode(ListNode *head) {
        // slow , fast pointer
        // 1 2 3 4 5
        // s F
        //   s   F
        //     s   f

        // 1 2 3 4 5 6
        //   s   F
        //     s     F
        //       s
        if (head == nullptr) {
            return head;
        }
        ListNode *slow = head;
        ListNode *fast = head->next;
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

  public:
    ListNode *sortList(ListNode *head) {
        if (head == nullptr || head->next == nullptr) {
            return head;
        }
        if (head->next->next == nullptr) {
            if (head->val > head->next->val) {
                ListNode *current_next = head->next;
                current_next->next = head;
                head->next = nullptr;
                return current_next;
            }
        }

        ListNode *middle = middleNode(head);
        // NOTICE: add split head here to find out it
        ListNode *splitHead = middle->next;
        middle->next = nullptr;

        head = sortList(head);
        splitHead = sortList(splitHead);

        ListNode *ret = mergeTwoLists(head, splitHead);
        //        cout << "Merge A: " << listNodeToString(head) << " And B:" <<
        //        listNodeToString(middle) << " Got" << listNodeToString(ret) <<
        //        endl;
        return ret;
    };
};

int main() {
    string line;
    while (getline(cin, line)) {
        ListNode *head = stringToListNode(line);
        cout << listNodeToString(head) << endl;
        ListNode *ret = Solution().sortList(head);

        string out = listNodeToString(ret);
        cout << out << endl;
    }
    return 0;
}