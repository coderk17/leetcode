#ifndef LEETCODE_AVL_TREE_H_
#define LEETCODE_AVL_TREE_H_

#define null -2147483648
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct AVLTreeNode {
    struct AVLTreeNode *left;
    struct AVLTreeNode *right;
    int height;
    int element;
};

typedef struct AVLTreeNode AVLTreeNode;
AVLTreeNode * createNode(int val);
AVLTreeNode * leftRotate(AVLTreeNode *node);
AVLTreeNode * rightRotate(AVLTreeNode *node);
AVLTreeNode * initializeAVL(AVLTreeNode *root, int data[], int size);
AVLTreeNode * insertAVL(AVLTreeNode *root, int val);
AVLTreeNode * deleteAVL(AVLTreeNode *root, int val);
AVLTreeNode * searchAVL(AVLTreeNode *root, int val);
int freeAVL (AVLTreeNode *root);
int breadthFirstTraveral(AVLTreeNode *node, int qSize);

#endif /* LEETCODE_AVL_TREE_H_ */