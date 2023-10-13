#ifndef LEETCODE_B_PLUS_TREE_H_
#define LEETCODE_B_PLUS_TREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define null -2147483648

struct BPlusTreeNode {
    int keyNum;
    int *keys;
    struct BPlusTreeNode *next;
    struct BPlusTreeNode **children;
};

struct BPlusTree {
    int m;
    struct BPlusTreeNode *root;
};

typedef struct BPlusTreeNode BPlusTreeNode;
typedef struct BPlusTree BPlusTree;

BPlusTree * createBPlusTree(int m);
int insertBPlusTree(BPlusTree *bPlusTree, int val);
BPlusTreeNode * searchBPlusTree(BPlusTree *bPlusTree, int val);
int deleteBPlusTree(BPlusTree *bPlusTree, int val);
int freeBPlusTree(BPlusTree *bPlusTree);
void printBPlusTree(BPlusTree *bPlusTree);
void printBPlusTreeNode(BPlusTreeNode *node, int maxKeyNum, int level);

#endif /* LEETCODE_B_PLUS_TREE_H_ */
