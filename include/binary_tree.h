#ifndef LEETCODE_BINARY_TREE_H_
#define LEETCODE_BINARY_TREE_H_

#define null -2147483648
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "queue.h"

struct BinaryTreeNode {
    int element;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

typedef struct BinaryTreeNode BinaryTreeNode;

int breadthFirstInitialize(BinaryTreeNode *root, int data[], int size);
int preorderTraveral(BinaryTreeNode *node);
int inorderTraveral(BinaryTreeNode *node);
int postorderTraveral(BinaryTreeNode *node);
int breadthFirstTraveral(BinaryTreeNode *node, int qSize);
int postorderFree(BinaryTreeNode *node);

#endif /* LEETCODE_BINARY_TREE_H_ */
