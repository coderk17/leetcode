/**
 * @file solution-3.c
 * @author coderk17
 * @brief Remove Duplicates from Sorted List II
 * @date 2023-01-01
 * 
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list. Return the linked list sorted as well.
 */

#include <linklist.h>

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (NULL == head)
        return head;
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *cur = &dummy;
    while (cur->next && cur->next->next) {
        if (cur->next->val == cur->next->next->val) {
            int max = cur->next->val;
            while (cur->next && max == cur->next->val) {
                cur->next = cur->next->next;
            }
        }
        else {
            cur = cur->next;
        }
    }
    return dummy.next;
}

int main(void)
{
    int l1[] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = deleteDuplicates(p1);
    print_llist(new_list);
}
