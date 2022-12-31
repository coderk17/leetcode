#include <linklist.h>

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    struct ListNode res;
    struct ListNode *prev = &res;
    while (l1 || l2) {
        int l1_val = NULL == l1 ? 0 : l1->val;
        int l2_val = NULL == l2 ? 0 : l2->val;
        int sum = l1_val + l2_val + carry;
        carry = sum / 10;
        struct ListNode *ptr = (struct ListNode *) malloc(sizeof(struct ListNode));
        ptr->val = sum % 10;
        prev->next = ptr;
        prev = ptr;

        l1 = NULL == l1 ? NULL : l1->next;
        l2 = NULL == l2 ? NULL : l2->next;
    }
    if (carry) {
        struct ListNode *ptr = (struct ListNode *) malloc(sizeof(struct ListNode));
        ptr->next = NULL;
        ptr->val = carry;
        prev->next = ptr;
    }
    return res.next;
}

/*
 * run command:
 * $ gcc ./solutions/linklist/000002/solution.c ./lib/linklist.c -o bin/linklist/000002-solution -I ./include 
 * $ ./bin/linklist/000002-solution
 */
int main(void)
{
    int l1[] = {1, 3, 5, 6, 7};
    int l2[] = {2, 4, 8, 9};
    struct ListNode *p1 = init_llist(l1, sizeof(l1) / sizeof(int));
    struct ListNode *p2 = init_llist(l2, sizeof(l2) / sizeof(int));
    print_llist(p1);
    print_llist(p2);
    struct ListNode * new_list = addTwoNumbers(p1, p2);
    print_llist(new_list);
}
