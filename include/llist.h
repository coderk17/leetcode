#ifndef LLIST
#define LLIST

#include <stdio.h>
#include <stdlib.h>

struct ListNode {
    int val;
    struct ListNode *next;
};

void print_llist(struct ListNode * list);

struct ListNode *init_llist(int list[], int size);

#endif
