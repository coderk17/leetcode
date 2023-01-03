/**
 * @file solution-2.c
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
    if (NULL == head || NULL == head->next)
        return head;
    struct ListNode dummy;
    dummy.next = head;
    int max = head->val;
    struct ListNode *cur = head;
    struct ListNode *prev = &dummy;
    while (cur->next) {
        if (cur->next->val != max) {
            if (NULL == prev->next) {
                prev->next = cur->next;
            } else {
                prev = prev->next;
            }
            cur = cur->next;
            max = cur->val;
        } else {
            while (cur) {
                if (NULL == cur->next || cur->next->val != max) {
                    prev->next = NULL;
                    break;
                } else {
                    cur = cur->next;
                }
            }
        }
    }
    return dummy.next;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000082/solution-2.c ./lib/linklist.c -o bin/linklist/000082-solution-2 -I ./include
 * $ ./bin/linklist/000082-solution-2
 */
int main(void)
{
    int l1[] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = deleteDuplicates(p1);
    print_llist(new_list);
}
