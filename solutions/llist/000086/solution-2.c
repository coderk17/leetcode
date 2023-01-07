/**
 * @file solution-2.c
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

#define isGreater(x, y) ({x >= y;})

struct ListNode* partition(struct ListNode* head, int x)
{
    if (NULL == head || NULL == head->next)
        return head;
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *ptr = &dummy;
    struct ListNode *prev = NULL;
    struct ListNode *lastLess = NULL;
    int state = isGreater(head->val, x);
    while (ptr->next)
    {
        if (isGreater(ptr->next->val, x) == state) {
            prev = ptr->next;
            ptr->next = ptr->next->next;
        } else {
            ptr = prev;
            state ^= 1;
        }
    }
    lastLess = isGreater(prev->val, x) ? ptr : prev;
    if (isGreater(head->val, x)) {
        lastLess->next = head;
        head = dummy.next;
    } else {
        lastLess->next = dummy.next;
    }
    return head;
}

/*
 * run command:
 * $ gcc ./solutions/llist/000086/solution-2.c ./lib/llist.c -o bin/llist/000086-solution-2 -I ./include
 * $ ./bin/llist/000086-solution-2
 */
int main(void)
{
    int l1[] = {1, 1};
    int x = 2;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = partition(p1, x);
    print_llist(new_list);
}
