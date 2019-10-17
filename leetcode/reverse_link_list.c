//
// 反转链表
// Created by 付旭炜 on 2019/3/19.
//


// Node of link list
typedef struct {
    int data;   // data store in linked list
    ListNode* next; // next node
} ListNode;

typedef struct {
    ListNode* head;
} LinkedList;

// create a linked list
LinkedList* newList();
// free a linked list
void freeList(LinkedList* linkedList);
void addNode(LinkedList* linkedList, ListNode* node);

void reverseLinkedList(LinkedList* list);

int main(int argc, char* argv[]) {

}

void reverseLinkedList(LinkedList* list) {
    if (list == NULL) {
        // null list, hey you
        return;
    }
    ListNode* current = list->head;
    ListNode* pre = NULL;

    // every time, pre(maybe null)-> current will be set to opre <- ocurrent(pre) current->
    // stop while <- pre current(NULL)
    while (current != NULL) {
        ListNode* next = current->next;
        current->next = pre;
        pre = current;
        current = next;

    }
    list->head = pre;
    return;
}