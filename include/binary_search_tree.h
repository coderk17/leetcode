#ifndef LEETCODE_BINARY_SEARCH_TREE_H_
#define LEETCODE_BINARY_SEARCH_TREE_H_

#include <stdio.h>
#include <stdlib.h>
#include "binary_tree.h"

typedef struct BinaryTreeNode BinarySearchTreeNode;

int initializeBST(BinarySearchTreeNode *root, int data[], int size);
int insertBST(BinarySearchTreeNode *node, int val);
int deleteBST(BinarySearchTreeNode *node, int val);
BinarySearchTreeNode * searchBST(BinarySearchTreeNode *node, int val);
int freeBST(BinarySearchTreeNode *node);

#endif /* LEETCODE_BINARY_SEARCH_TREE_H_ */
