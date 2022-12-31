#include <linklist.h>

struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode *prev, *ptr;
    prev = ptr = head;
    while (n--)
        ptr = ptr->next;
    if (NULL == ptr)
        return head->next;
    while (ptr->next) {
        ptr = ptr->next;
        prev = prev->next;
    }
    prev->next = prev->next->next;
    return head;
}

/**
 * run command:
 * $ gcc ./solutions/linklist/000019/solution.c ./lib/linklist.c -o bin/linklist/000019-solution -I ./include
 * $ ./bin/linklist/000019-solution
 */
int main(void)
{
    int l[] = {1, 2};
    struct ListNode *p = init_llist(l, sizeof(l) / sizeof(int));
    print_llist(p);
    struct ListNode * new_list = removeNthFromEnd(p, 1);
    print_llist(new_list);
}
