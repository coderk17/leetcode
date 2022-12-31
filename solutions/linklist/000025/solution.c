/*
 * @file solution.c
 * @author coderk17
 * @date 2023-01-01
 * 
 * @brief Given the head of a linked list, reverse the nodes of the list k at a time,
 * and return the modified list.
 * 
 * k is a positive integer and is less than or equal to the length of the linked list.
 * If the number of nodes is not a multiple of k then left-out nodes, in the end, 
 * should remain as it is.
 * 
 * You may not alter the values in the list's nodes, 
 * only nodes themselves may be changed.
 */

#include <linklist.h>

struct ListNode* reverse(struct ListNode* head)
{
    // if (NULL == head || NULL == head->next)
    if (NULL == head->next)
        return head;
    struct ListNode *last = reverse(head->next);
    last->next = head;
    head->next = NULL;
    return head;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k)
{
    int counter = k;
    struct ListNode *ptr = head;
    struct ListNode *prev = head;
    while (counter--)
    {
        if (NULL == ptr)
            return head;
        prev = ptr;
        ptr = ptr->next;
    }
    struct ListNode *nextGroup = ptr;
    prev->next = NULL;
    ptr = reverse(head);
    if (NULL != nextGroup)
        ptr->next = reverseKGroup(nextGroup, k);
    return prev;
}

int main(void)
{
    int l1[] = {1, 2, 3, 4, 5};
    int k = 2;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = reverseKGroup(p1, k);
    print_llist(new_list);
}