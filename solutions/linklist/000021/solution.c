#include <linklist.h>

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2)
{
    struct ListNode res;
    struct ListNode * prev = &res;
    while (NULL != list1 && NULL != list2) {
        if (list1->val < list2->val) {
            prev->next = list1;
            prev = prev->next;
            list1 = list1->next;
        } else {
            prev->next = list2;
            prev = prev->next;
            list2 = list2->next;
        }
    }
    prev->next = NULL == list1 ? list2 : list1;
    return res.next;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000021/solution.c ./lib/linklist.c -o bin/linklist/000021-solution -I ./include
 * $ ./bin/linklist/000021-solution
 */
int main(void)
{
    int l1[] = {0, 1, 3, 5, 6, 7};
    int l2[] = {2, 4, 8, 9};
    int size1 = sizeof(l1) / sizeof(int);
    int size2 = sizeof(l2) / sizeof(int);
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    struct ListNode *p2 = init_llist(l2, sizeof(l2) / sizeof(int));
    print_llist(p1);
    print_llist(p2);
    struct ListNode * new_list = mergeTwoLists(p1, p2);
    print_llist(new_list);
}
