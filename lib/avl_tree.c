#include "stack.h"
#include "queue.h"
#include "avl_tree.h"

int _height(AVLTreeNode *node)
{
    if (NULL == node) {
        return -1;
    } else {
        int height = fmax(
            NULL == node->left ? -1 : node->left->height,
            NULL == node->right ? -1 : node->right->height) + 1;
        return height;
    }
}

int _balance(AVLTreeNode *node)
{
    int balance = ((NULL == node->left ? -1 : node->left->height)
                   - (NULL == node->right ? -1: node->right->height));
    return balance;
}

AVLTreeNode * createNode(int val)
{
    AVLTreeNode *node = (AVLTreeNode *) malloc(sizeof(AVLTreeNode));
    node->element = val;
    node->height = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

AVLTreeNode * leftRotate(AVLTreeNode *node)
{
    if (NULL == node) {
        fprintf(stderr, "empty node can\'t rotate!\n");
        return -1;
    }
    AVLTreeNode *tr = node->right;
    node->right = tr->left;
    tr->left = node;
    node->height = _height(node);
    tr->height = _height(tr);
    
    return tr;
}

AVLTreeNode * rightRotate(AVLTreeNode *node)
{
    if (NULL == node) {
        fprintf(stderr, "empty node can\'t rotate!\n");
        return -1;
    }
    AVLTreeNode *tl = node->left;
    node->left = tl->right;
    tl->right = node;
    node->height = _height(node);
    tl->height = _height(tl);

    return tl;
}

AVLTreeNode * initializeAVL(AVLTreeNode *root, int data[], int size)
{
    for (int i = 0; i < size; i++) {
        root = insertAVL(root, data[i]);
    }
    return root;
}

AVLTreeNode * insertAVL(AVLTreeNode *root, int val)
{
    if (NULL == root) {
        return createNode(val);
    }
    if (val > root->element) {
        root->right = insertAVL(root->right, val);
    } else if (val < root->element) {
        root->left = insertAVL(root->left, val);
    } else {
        fprintf(stderr, "insert value can\'t duplicate! %d\n", val);
        return NULL;
    }
    root->height = _height(root);
    int balance = _balance(root);
    if (balance > 1) {
        // LR
        if (_balance(root->left) < 0) {
            root->left = leftRotate(root->left);
        }
        // LL
        return rightRotate(root);
    } else if (balance < -1) {
        // RL
        if (_balance(root->right) > 0) {
            root->right = rightRotate(root->right);
        }
        // RR
        return leftRotate(root);
    } else {
        return root;
    }
}

AVLTreeNode * deleteAVL(AVLTreeNode *root, int val)
{
    if (NULL == root) {
        fprintf(stderr, "this node is not exists!\n");
        return NULL;
    }

    if (val < root->element) {
        root->left = deleteAVL(root->left, val);
    } else if (val > root->element) {
        root->right = deleteAVL(root->right, val);
    } else {
        if (NULL != root->left && NULL != root->right) {
            AVLTreeNode *node = root->left;
            while (node->right)
            {
                node = node->right;
            }
            int leftMax = node->element;
            int realDelete = leftMax;
            AVLTreeNode *oriRoot = root;
            if (node->right) {
                realDelete = node->right->element;
                root = deleteAVL(root, realDelete);
                node->element = realDelete;
            }
            else {
                root = deleteAVL(root, leftMax);
            }
            oriRoot->element = leftMax;
        } else if (NULL != root->left) {
            AVLTreeNode *rootLeft = root->left;
            root->element = rootLeft->element;
            root->right = rootLeft->right;
            root->left = rootLeft->left;
            free(rootLeft);
            rootLeft = NULL;
        } else if (NULL != root->right) {
            AVLTreeNode *rootRight = root->right;
            root->element = rootRight->element;
            root->left = rootRight->left;
            root->right = rootRight->right;
            free(rootRight);
            rootRight = NULL;
        } else {
            free(root);
            root = NULL;
        }
        return root;
    }
    root->height = _height(root);
    int balance = _balance(root);
    printf("balance: %d\n", balance);
    if (balance > 1) {
        // LR
        if (_balance(root->left) < 0) {
            root->left = leftRotate(root->left);
        }
        // LL
        return rightRotate(root);
    } else if (balance < -1) {
        // RL
        if (_balance(root->right) > 0) {
            root->right = rightRotate(root->right);
        }
        // RR
        return leftRotate(root);
    } else {
        return root;
    } 
}

AVLTreeNode * searchAVL(AVLTreeNode *root, int val)
{
    AVLTreeNode *node = root;
    while (node)
    {
        if (val < node->element) {
            node = node->left;
        } else if (val > node->element) {
            node = node->right;
        } else {
            return node;
        }
    }
    return NULL;
}

int freeAVL (AVLTreeNode *root)
{
    if (NULL == root)
        return 0;
    freeAVL(root->left);
    freeAVL(root->right);
    free(root);
    root = NULL;
    return 0;
}

int breadthFirstTraveral(AVLTreeNode *node, int qSize)
{
    Queue *q = (Queue *) malloc(sizeof(Queue));
    initializeQueue(q, qSize);
    enqueue(q, node);
    while (!queueIsEmpty(q))
    {
        AVLTreeNode *cur = (AVLTreeNode *) dequeue(q);
        if (NULL == cur || null == cur->element) {
            continue;
        }
        printf("node data: %d\n", cur->element);
        enqueue(q, cur->left);
        enqueue(q, cur->right);
    }
    freeQueue(q);
    return 0;
}
