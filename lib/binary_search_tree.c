#include "binary_search_tree.h"

int initializeBST(BinarySearchTreeNode *root, int data[], int size)
{
    if (size <= 0) {
        fprintf(stderr, "data number must larger than one!");
    }
    root->element = data[0];
    root->left = NULL;
    root->right = NULL;
    for (int i = 1; i < size; i++) {
        insertBST(root, data[i]);
    }
    return 0;
}

int insertBST(BinarySearchTreeNode *node, int val)
{   
    while (NULL != node)
    {
        if (val == node->element) {
            fprintf(stderr, "insert value can\'t duplicate! %d\n", val);
            return -1;
        } else if (val < node->element) {
            if (NULL == node->left) {
                node->left = (BinarySearchTreeNode *) malloc(sizeof(BinarySearchTreeNode));
                node->left->left = NULL;
                node->left->right = NULL;
                node->left->element = val;
                return 0;
            } else {
                node = node->left;
            }
        } else {
            if (NULL == node->right) {
                node->right = (BinarySearchTreeNode *) malloc(sizeof(BinarySearchTreeNode));
                node->right->left = NULL;
                node->right->right = NULL;
                node->right->element = val;
                return 0;
            } else {
                node = node->right;
            }
        }
    }
    fprintf(stderr, "insert error: %d!\n", val);
    return -1;
}

int deleteBST(BinarySearchTreeNode *node, int val)
{
    int deleteNodeIsLeft = 1;
    BinarySearchTreeNode *parent = node;
    while (NULL != node) {
        if (val == node->element) {
            if (NULL != node->left && NULL != node->right) {
                // exchange delete node value with minimum value of right subtree,
                BinarySearchTreeNode *pre = node;
                BinarySearchTreeNode *tmp = pre->right;
                while (NULL != tmp->left) {
                    pre = tmp;
                    tmp = tmp->left;
                }
                node->element = tmp->element;
                pre->left = NULL;
            } else if (NULL == node->left && NULL == node->right) {
                if (deleteNodeIsLeft == 1) {
                    parent->left = NULL;
                } else {
                    parent->right = NULL;
                }
            } else if (NULL == node->left) {
                if (deleteNodeIsLeft == 1) {
                    parent->left = node->right;
                } else {
                    parent->right = node->right;
                }
            } else if (NULL == node->right) {
                if (deleteNodeIsLeft == 1) {
                    parent->left = node->left;
                } else {
                    parent->right = node->left;
                }
            }
            // printf("parent: %d\n", parent->element);
            // printf("pleft: %d\n", parent->left->element);
            // printf("pright: %d\n", parent->right->element);
            return 0;
        } else if (val < node->element) {
            parent = node;
            node = node->left;
            deleteNodeIsLeft = 1;
        } else if (val > node->element) {
            parent = node;
            node = node->right;
            deleteNodeIsLeft = 0;
        }
    }
    fprintf(stderr, "delete error: this node not exists {%d}!\n", val);
    return -1;
}

BinarySearchTreeNode * searchBST(BinarySearchTreeNode *node, int val)
{
    while (NULL != node) {
        if (val == node->element) {
            return node;
        } else if (val < node->element) {
            node = node->left;
        } else if (val > node->element) {
            node = node->right;
        }
    }
    fprintf(stderr, "this node not find {%d}!\n", val);
    return NULL;
}

int freeBST(BinarySearchTreeNode *node)
{
    postorderFree(node);
}