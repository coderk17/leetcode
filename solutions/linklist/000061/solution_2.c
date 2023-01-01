/**
 * @file solution.c
 * @author coderk17
 * @date 2023-01-01
 * @brief Rotate List
 * 
 * Given the head of a linked list, rotate the list to the right by k places.
 */

#include <linklist.h>

struct ListNode* rotateRight(struct ListNode* head, int k)
{
    if (NULL == head)
        return head;
    int counter = 0;
    struct ListNode *ptr = head;
    struct ListNode *prev = head;
    struct ListNode *res = head;
    while (ptr) {
        ptr = ptr->next;
        counter += 1;
    }
    k %= counter;
    if (k == 0)
        return head;
    ptr = head;
    while (k--) {
        ptr = ptr->next;
    }
    prev = head;
    while (ptr->next)
    {
        ptr = ptr->next;
        prev = prev->next;
    }
    res = prev->next;
    ptr->next = head;
    prev->next = NULL;
    return res;
}

int main(void)
{
    int l1[] = {1, 2, 3, 4, 5};
    int k = 5;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = rotateRight(p1, k);
    print_llist(new_list);
}
