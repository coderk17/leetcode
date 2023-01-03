#include <llist.h>

struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
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

struct ListNode* merge(struct ListNode** lists, int start, int end) {
    if (end - start == 0)
        return lists[start];
    if (end - start == 1)
        return mergeTwoLists(lists[start], lists[end]);
    int mid = (start + end) / 2;
    return mergeTwoLists(merge(lists, start, mid), merge(lists, mid+1, end));
}

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    if (listsSize == 0)
        return NULL;
    if (listsSize == 1)
        return lists[0];
    struct ListNode *res = merge(lists, 0, listsSize-1);
    return res;
}

/*
 * run command:
 * $ gcc ./solutions/llist/000023/solution.c ./lib/llist.c -o bin/llist/000023-solution -I ./include
 * $ ./bin/llist/000023-solution
 */
int main(void)
{
    int l1[] = {1, 3, 9};
    int l2[] = {2, 4, 6};
    int l3[] = {0, 3, 8};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    struct ListNode *p2 = init_llist(l2, sizeof(l2) / sizeof(int));
    struct ListNode *p3 = init_llist(l3, sizeof(l3) / sizeof(int));
    print_llist(p1);
    print_llist(p2);
    print_llist(p3);
    struct ListNode **lists = (struct ListNode **) malloc(sizeof(struct ListNode *));
    lists[0] = p1;
    lists[1] = p2;
    lists[2] = p3;
    struct ListNode * new_list = mergeKLists(lists, 3);
    print_llist(new_list);
}
