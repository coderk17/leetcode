/**
 * @file solution-2.c
 * @author coderk17
 * @brief Remove Duplicates from Sorted List
 * @date 2023-01-03
 * 
 * Given the head of a sorted linked list, delete all duplicates such that
 * each element appears only once. Return the linked list sorted as well.
 */

#include <linklist.h>

struct ListNode* deleteDuplicates(struct ListNode* head)
{
    if (NULL == head)
        return head;
    int max = head->val - 1;
    struct ListNode *ptr = head;
    while (ptr->next) {
        if (ptr->val == ptr->next->val) {
            ptr->next = ptr->next->next;
        } else {
            ptr = ptr->next;
        }
    }
    return head;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000083/solution-2.c ./lib/linklist.c -o bin/linklist/000083-solution-2 -I ./include
 * $ ./bin/linklist/000083-solution-2
 */
int main(void)
{
    int l1[] = {1, 2, 3, 3, 3, 3, 4, 4, 4, 5};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = deleteDuplicates(p1);
    print_llist(new_list);
}
