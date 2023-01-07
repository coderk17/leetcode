/**
 * @file solution-1.c
 * @author coderk17
 * @brief Partition List
 * @date 2023-01-06
 * 
 * Given the head of a linked list and a value x, partition it
 * such that all nodes less than x come before nodes greater than or equal to x.
 * 
 * You should preserve the original relative order of the nodes in each of the two partitions.
 */

#include <llist.h>

struct ListNode* partition(struct ListNode* head, int x)
{
    if (NULL == head || NULL == head->next)
        return head;
    struct ListNode *greater = NULL;
    struct ListNode *greaterHead = NULL;
    struct ListNode *less = NULL;
    struct ListNode *lessHead = NULL;
    struct ListNode *ptr = head;
    while (ptr->next) {
        if (ptr->val >= x)
        {
            if (NULL == greaterHead)
                greaterHead = ptr;
            while (ptr->next && ptr->next->val >= x) {
                ptr = ptr->next;
            }
            if (NULL == less) {
                lessHead = ptr->next;
            } else {
                less->next = ptr->next;
            }
            greater = ptr;
            if (ptr->next) {
                ptr = ptr->next;
                less = ptr;
            }
        } 
        else 
        {
            if (NULL == lessHead)
                lessHead = ptr;
            while (ptr->next && ptr->next->val < x) {
                ptr = ptr->next;
            }
            if (NULL == greater) {
                greaterHead = ptr->next;
            } else {
                greater->next = ptr->next;
            }
            less = ptr;
            if (ptr->next) {
                ptr = ptr->next;
                greater = ptr;
            }
        }
    }
    if (greater)
        greater->next = NULL;
    if (lessHead) {
        less->next = greaterHead;
    } else {
        lessHead = greaterHead;
    }
    return lessHead;
}

/*
 * run command:
 * $ gcc ./solutions/llist/000086/solution-1.c ./lib/llist.c -o bin/llist/000086-solution-1 -I ./include
 * $ ./bin/llist/000086-solution-1
 */
int main(void)
{
    int l1[] = {1, 4, 3, 0, 5, 2};
    int x = 2;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = partition(p1, x);
    print_llist(new_list);
}
