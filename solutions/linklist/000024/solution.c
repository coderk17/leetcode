#include <linklist.h>

struct ListNode* swapPairs(struct ListNode* head)
{
    if (NULL == head || NULL == head->next)
        return head;

    struct ListNode *second = head->next;
    struct ListNode *third = second->next;
    second->next = head; 
    head->next = swapPairs(third);
    return second;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000024/solution.c ./lib/linklist.c -o bin/linklist/000024-solution -I ./include
 * $ ./bin/linklist/000024-solution
 */
int main(void)
{
    int l1[] = {1, 2, 3, 4, 1, 2, 3, 4, 1};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    print_llist(p1);
    struct ListNode * new_list = swapPairs(p1);
    print_llist(new_list);
}
