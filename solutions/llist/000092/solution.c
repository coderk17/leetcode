/**
 * @file solution.c
 * @author coderk17
 * @brief Reverse Linked List II
 * @date 2023-01-08
 * 
 * Given the head of a singly linked list and two integers left and right
 * where left <= right, reverse the nodes of the list from position left
 * to position right, and return the reversed list.
 */

#include <llist.h>

struct ListNode *temp = NULL;
struct ListNode *rest = NULL;

struct ListNode* reverseX(struct ListNode* head, int x)
{
    if (!head->next || x == 0)
        return head;
    if (x == 1) {
        temp = head->next;
        rest = temp->next;
        head->next->next = head;
        return head;
    }
    struct ListNode *res = NULL;
    res = reverseX(head->next, x-1);
    res->next = head;
    return head;
}

struct ListNode* reverseBetween(struct ListNode* head, int left, int right)
{
    struct ListNode dummy;
    dummy.next = head;
    struct ListNode *res = NULL;
    struct ListNode *ptr = &dummy;
    struct ListNode *prev = &dummy;
    int x = right - left;
    while (left--)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    if (!ptr)
        return head;
    res = reverseX(ptr, x);
    if (temp)
        prev->next = temp;
    res->next = rest;
    return dummy.next;
}

/*
 * run command:
 * $ gcc ./solutions/llist/000092/solution.c ./lib/llist.c -o bin/llist/000092-solution -I ./include
 * $ ./bin/llist/000092-solution
 */
int main(void)
{
    int l1[] = {1, 2, 3, 4, 5};
    int left = 2;
    int right = 4;
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = reverseBetween(p1, left, right);
    print_llist(new_list);
}
