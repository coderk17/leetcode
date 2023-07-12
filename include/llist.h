#ifndef LEETCODE_LLIST_H_
#define LEETCODE_LLIST_H_

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_llist(struct ListNode * list);

struct ListNode *init_llist(int list[], int size);

#endif /* LEETCODE_LLIST_H_ */
