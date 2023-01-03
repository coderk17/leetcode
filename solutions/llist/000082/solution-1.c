/**
 * @file solution-1.c
 * @author coderk17
 * @brief Remove Duplicates from Sorted List II
 * @date 2023-01-01
 * 
 * Given the head of a sorted linked list, delete all nodes that have duplicate numbers,
 * leaving only distinct numbers from the original list. Return the linked list sorted as well.
 */

#include <llist.h>

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (NULL == head || NULL == head->next)
        return head;
    struct ListNode dummy;
    dummy.next = head;
    int max = head->val;
    struct ListNode *pPrev = &dummy;
    struct ListNode *ptr = &dummy;
    for (int k = 0; k < 2; k++) {
        ptr = ptr->next;
    }
    while (ptr) {
        if (ptr->val == max) {
            pPrev->next = NULL;
        } else {
            if (NULL == pPrev->next) {
                pPrev->next = deleteDuplicates(ptr);
                return dummy.next;
            } else {
                max = ptr->val;
                pPrev = pPrev->next;
            }
        }
        ptr = ptr->next;
    }
    return dummy.next; 
}

/*
 * run command:
 * $ gcc ./solutions/llist/000082/solution-1.c ./lib/llist.c -o bin/llist/000082-solution-1 -I ./include
 * $ ./bin/llist/000082-solution-1
 */
int main(void)
{
    int l1[] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = deleteDuplicates(p1);
    print_llist(new_list);
}
