#ifndef LEETCODE_B_TREE_H_
#define LEETCODE_B_TREE_H_
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define null -2147483648

struct BTreeNode {
    int keyNum;
    bool isLeaf;
    int *keys;
    struct BTreeNode **children;
};

struct BTree {
    int m;
    struct BTreeNode *root;
};

typedef struct BTreeNode BTreeNode;
typedef struct BTree BTree;

BTree * createBTree(int m);
int insertBTree(BTree *btree, int val);
BTreeNode * searchBTree(BTree *btree, int val);
int deleteBTree(BTree *btree, int val);
int freeBTree(BTree *btree);
void printBTree(BTree *btree);
void printBTreeNode(BTreeNode *node, int maxKeyNum, int level);

#endif /* LEETCODE_B_TREE_H_ */
