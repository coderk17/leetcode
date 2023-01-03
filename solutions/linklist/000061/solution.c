/**
 * @file solution.c
 * @author coderk17
 * @brief Rotate List
 * @date 2023-01-01
 * 
 * Given the head of a linked list, rotate the list to the right by k places.
 */

#include <linklist.h>

struct ListNode* rotateRight(struct ListNode* head, int k)
{
    if (NULL == head)
        return head;
    int length = 1;
    struct ListNode *last = head;
    struct ListNode *prev = head;
    struct ListNode *res = head;
    while (last->next) {
        last = last->next;
        length += 1;
    }
    k = length - k % length;
    if (k == length)
        return head;
    while (k--) {
        prev = res;
        res = res->next;
    }
    last->next = head;
    prev->next = NULL;
    return res;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000061/solution.c ./lib/linklist.c -o bin/linklist/000061-solution -I ./include
 * $ ./bin/linklist/000061-solution
 */
int main(void)
{
    int l1[] = {1, 2, 3, 4, 5};
    int k = 2;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = rotateRight(p1, k);
    print_llist(new_list);
}
