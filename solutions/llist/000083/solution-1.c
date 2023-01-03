/**
 * @file solution-1.c
 * @author coderk17
 * @brief Remove Duplicates from Sorted List
 * @date 2023-01-03
 * 
 * Given the head of a sorted linked list, delete all duplicates such that
 * each element appears only once. Return the linked list sorted as well.
 */

#include <llist.h>

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (NULL == head)
        return head;
    int max = head->val - 1;
    struct ListNode dummy;
    struct ListNode *ptr = head;
    struct ListNode *prev = &dummy;
    while (ptr) {
        if (ptr->val != max) {
            max = ptr->val;
            prev->next = ptr;
            prev = ptr;
        }
        ptr = ptr->next;
    }
    prev->next = NULL;
    return dummy.next;
}

/*
 * run command:
 * $ gcc ./solutions/llist/000083/solution-1.c ./lib/llist.c -o bin/llist/000083-solution-1 -I ./include
 * $ ./bin/llist/000083-solution-1
 */
int main(void)
{
    int l1[] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = deleteDuplicates(p1);
    print_llist(new_list);
}
