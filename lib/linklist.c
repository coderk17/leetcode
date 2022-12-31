#include <linklist.h>

void print_llist(struct ListNode * list)
{
    while (list) {
        printf("...%d(%p),", list->val, list);
        list = list->next;
    }
    puts("\n");
}

struct ListNode *init_llist(int list[], int size)
{
    struct ListNode res;
    struct ListNode *ptr = &res;
    for (int i = 0; i < size; i++) {
        struct ListNode *next = (struct ListNode *) malloc(sizeof(struct ListNode));
        next->next = NULL;
        next->val = list[i];
        ptr->next = next;
        ptr = next;
    }
    return res.next;
}
