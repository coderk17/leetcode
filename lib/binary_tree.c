#include <math.h>
#include "binary_tree.h"
#include "queue.h"

breadthFirstInitialize(BinaryTreeNode *root, int data[], int size)
{
    int index = 0;
    int queueMaxSize = pow(2, (int) (log(size) / log(2)));
    Queue *q = (Queue *) malloc(sizeof(Queue));
    initialize(q, queueMaxSize);
    root->left = NULL;
    root->right = NULL;
    enqueue(q, root);
    while (!isEmpty(q))
    {
        BinaryTreeNode *cur = (BinaryTreeNode *) dequeue(q);
        if (NULL == cur) {
            continue;
        }
        if (null == data[index] || index >= size) {
            index++;
            cur->element = null;
            cur->left = NULL;
            cur->right = NULL;
            continue;
        }
        cur->element = data[index++];
        cur->left = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
        cur->left->element = null;            
        cur->left->left = NULL;
        cur->left->right = NULL;
        cur->right = (BinaryTreeNode *) malloc(sizeof(BinaryTreeNode));
        cur->right->element = null;            
        cur->right->left = NULL;
        cur->right->right = NULL;
        enqueue(q, cur->left);
        enqueue(q, cur->right);
    }
    return 0;
}

int preorderTraveral(BinaryTreeNode *node)
{
    if (NULL == node) {
        return 0;
    }
    if (null != node->element) {
        printf("node data: %d\n", node->element);
    }
    preorderTraveral(node->left);
    preorderTraveral(node->right);
    return 0;
}
 
int inorderTraveral(BinaryTreeNode *node)
{
    if (NULL == node) {
        return 0;
    }
    inorderTraveral(node->left);
    if (null != node->element) {
        printf("node data: %d\n", node->element);
    }
    inorderTraveral(node->right);
    return 0;
}

int postorderTraveral(BinaryTreeNode *node)
{
    if (NULL == node) {
        return 0;
    }
    postorderTraveral(node->left);
    postorderTraveral(node->right);
    if (null != node->element) {
        printf("node data: %d\n", node->element);
    }
    return 0;
}

int breadthFirstTraveral(BinaryTreeNode *node, int qSize)
{
    Queue *q = (Queue *) malloc(sizeof(Queue));
    initialize(q, qSize);
    enqueue(q, node);
    while (!isEmpty(q))
    {
        BinaryTreeNode *cur = (BinaryTreeNode *) dequeue(q);
        if (NULL == cur || null == cur->element) {
            continue;
        }
        printf("node data: %d\n", cur->element);
        enqueue(q, cur->left);
        enqueue(q, cur->right);
    }
    return 0;
}

int postorderFree(BinaryTreeNode *node)
{
    if (NULL == node)
        return 0;
    postorderFree(node->left);
    postorderFree(node->right);
    free(node);
}
