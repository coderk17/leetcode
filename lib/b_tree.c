#include "b_tree.h"

int _freeBTreeNode(BTreeNode *node, bool isFreeChildren)
{
    int keyNum = node->keyNum;
    free(node->keys);
    node->keys = NULL;
    if (node->children) {
        if (isFreeChildren) {
            for (int i = 0; i < keyNum + 1; i++) {
                _freeBTreeNode(*(node->children + i), isFreeChildren);
            }
        }
        free(node->children);
        node->children = NULL;
    }
    free(node);
    node = NULL;
    return 0;
}

BTreeNode * _createBTreeNode(int *keys, BTreeNode **children, int index, int length, int maxKeyNum)
{
    BTreeNode *node = (BTreeNode *) malloc(sizeof(BTreeNode));
    node->keys = (int *) malloc(sizeof(int) * (maxKeyNum + 1));
    node->children = NULL;
    node->keyNum = length;
    for (int i = 0; i < length; i++) {
        *(node->keys + i) = *(keys + index + i);
    }
    if (children) {
        node->children = (BTreeNode **) calloc(maxKeyNum + 2, sizeof(BTreeNode *));
        for (int i = 0; i < length + 1; i++) {
            *(node->children + i) = *(children + index + i);
        }
    }
    return node;
}

BTreeNode * _splitBTreeNode(BTreeNode *node, int maxKeyNum)
{
    int m = maxKeyNum + 1;
    int splitIndex = ceil(m / 2.0) - 1;

    int leftLength = splitIndex;
    int rightLength = maxKeyNum - leftLength;

    int leftIndex = 0;
    int rightIndex = splitIndex + 1;

    BTreeNode *leftNode = _createBTreeNode(node->keys, node->children, leftIndex, leftLength, maxKeyNum);
    BTreeNode *rightNode = _createBTreeNode(node->keys, node->children, rightIndex, rightLength, maxKeyNum);
    BTreeNode *newNode = _createBTreeNode(node->keys, NULL, splitIndex, 1, maxKeyNum);
    newNode->children = (BTreeNode **) calloc(m + 1, sizeof(BTreeNode *));
    *(newNode->children) = leftNode;
    *(newNode->children + 1) = rightNode;
    _freeBTreeNode(node, false);
    return newNode;
}

BTreeNode * _insertBTreeNode(BTreeNode *node, BTreeNode *insertNode, int maxKeyNum)
{
    int val = *(insertNode->keys);
    int keyNum = node->keyNum;
    int i = 0;
    while (i < keyNum && *(node->keys + i) < val)
    {
        i++;
    }
    if (node->children) {
        BTreeNode *resNode = _insertBTreeNode(*(node->children + i), insertNode, maxKeyNum);
        if (resNode != *(node->children + i)) {
            val = *(resNode->keys);

            for (int k = keyNum; k >= i; k--) {
                *(node->children + k + 1) = *(node->children + k);
            }
            if (resNode->children) {
                *(node->children + i) = *(resNode->children);
                *(node->children + i + 1) = *(resNode->children + 1);
            } else {
                fprintf(stderr, "resNode data error: %p\n", resNode);
            }
            _freeBTreeNode(resNode, false);
        } else {
            return node;
        }
    }
    for (int j = keyNum - 1; j >= i; j--) {
        *(node->keys + j + 1) = *(node->keys + j);
    }
    *(node->keys + i) = val;
    node->keyNum += 1;

    if (keyNum >= maxKeyNum) {
        node = _splitBTreeNode(node, maxKeyNum);
    }
    return node;
}

int _rebalance(BTreeNode *node, int i, int minKeyNum)
{
    BTreeNode *deleteChildNode = *(node->children + i);
    if (deleteChildNode->keyNum < minKeyNum) {
        BTreeNode *leftChildNode = i > 0 ? *(node->children + i - 1) : NULL;
        BTreeNode *rightChildNode = i < node->keyNum ? *(node->children + i + 1) : NULL;
        if (leftChildNode && leftChildNode->keyNum > minKeyNum) {
            for (int j = deleteChildNode->keyNum; j > 0; j--) {
                *(deleteChildNode->keys + j) = *(deleteChildNode->keys + j - 1);
            }
            *(deleteChildNode->keys) = *(node->keys + i - 1);
            if (leftChildNode->children) {
                for (int j = deleteChildNode->keyNum + 1; j > 0; j--) {
                    *(deleteChildNode->children + j) = *(deleteChildNode->children + j - 1);
                }
                *(deleteChildNode->children) = *(leftChildNode->children + leftChildNode->keyNum);
            }
            deleteChildNode->keyNum++;
            *(node->keys + i - 1) = *(leftChildNode->keys + --leftChildNode->keyNum);
        } else if (rightChildNode && rightChildNode->keyNum > minKeyNum) {
            *(deleteChildNode->keys + deleteChildNode->keyNum++) = *(node->keys + i);
            *(node->keys + i) = *(rightChildNode->keys);
            for (int j = 0; j < rightChildNode->keyNum - 1; j++) {
                *(rightChildNode->keys + j) = *(rightChildNode->keys + j + 1);
            }
            if (rightChildNode->children) {
                *(deleteChildNode->children + deleteChildNode->keyNum) = *(rightChildNode->children);
                for (int j = 0; j < rightChildNode->keyNum; j++) {
                    *(rightChildNode->children + j) = *(rightChildNode->children + j + 1);
                }
            }
            rightChildNode->keyNum--;
        } else {
            BTreeNode *mergeNode = leftChildNode ? leftChildNode : deleteChildNode;
            BTreeNode *moveNode = leftChildNode ? deleteChildNode : rightChildNode;
            int keyIndex = leftChildNode ? i - 1 : i;

            *(mergeNode->keys + mergeNode->keyNum++) = *(node->keys + keyIndex);
            int lastChildIndex = mergeNode->keyNum;
            for (int j = 0; j < moveNode->keyNum; j++) {
                *(mergeNode->keys + mergeNode->keyNum++) = *(moveNode->keys + j);
            }
            if (mergeNode->children) {
                for (int j = 0; j < moveNode->keyNum + 1; j++) {
                    *(mergeNode->children + lastChildIndex + j) = *(moveNode->children + j);
                }
            }
            moveNode->keyNum = 0;
            if (moveNode == deleteChildNode) {
                *(node->children + i) = NULL;
            } else {
                *(node->children + i + 1) = NULL;
            }

            for (int j = keyIndex; j < node->keyNum - 1; j++) {
                *(node->keys + j) = *(node->keys + j + 1);
                *(node->children + j + 1) = *(node->children + j + 2);
            }
            node->keyNum--;
            _freeBTreeNode(moveNode, false);
        }
    }
}

int _deleteBTreeNode(BTreeNode *node, int val, int m)
{
    int deleteRes = 0;
    int i = 0;
    int keyNum = node->keyNum;
    int minKeyNum = ceil(m / 2.0) - 1;
    while (i < keyNum && *(node->keys + i) < val) {
        i++;
    }
    if (i == keyNum || *(node->keys + i) > val) {
        if (!node->children) {
            fprintf(stderr, "this btree do not have this val: %d!\n", val);
        } else {
            deleteRes = _deleteBTreeNode(*(node->children + i), val, m);
        }
    } else {
        if (node->children) {
            int realDeleteVal = 0;
            BTreeNode *leftNode = *(node->children + i);
            BTreeNode *rightNode = *(node->children + i + 1);
            BTreeNode *tmp = leftNode;
            BTreeNode *tmpParent = leftNode;
            // find maximum value of left child node
            while (tmp->children)
            {
                tmp = *(tmp->children + tmp->keyNum);
            }
            realDeleteVal = *(tmp->keys + tmp->keyNum - 1);
            if (tmp->keyNum <= minKeyNum) {
                // find minimum value of right child node
                tmp = rightNode;
                tmpParent = rightNode;
                while (tmp->children)
                {
                    tmp = *(tmp->children);
                }
                realDeleteVal = *(tmp->keys);
            }
            // fprintf(stdout, "The value of the deleted node has changed: %d -> %d!\n", val, realDeleteVal);
            *(node->keys + i) = realDeleteVal;
            deleteRes = _deleteBTreeNode(tmpParent, realDeleteVal, m);
            if (tmpParent == leftNode) {
                _rebalance(node, i, minKeyNum);
                return deleteRes;
            } else {
                _rebalance(node, i + 1, minKeyNum);
                return deleteRes;
            }
        } else {
            for (int j = i; j < node->keyNum - 1; j++) {
                *(node->keys + j) = *(node->keys + j + 1);
            }
            node->keyNum--;
            deleteRes = 1;
        }
    }
    if (node->children) {
        _rebalance(node, i, minKeyNum);
    } 
    return deleteRes;
}

BTree * createBTree(int m)
{
    BTree *btree = (BTree *) malloc(sizeof(BTree));
    btree->m = m;
    btree->root = _createBTreeNode(NULL, NULL, 0, 0, m);
    return btree;
}

int insertBTree(BTree *btree, int val)
{
    BTreeNode *root = btree->root;
    int maxKeyNum = btree->m - 1;
    BTreeNode *insertNode = _createBTreeNode(&val, NULL, 0, 1, maxKeyNum);
    btree->root = _insertBTreeNode(root, insertNode, maxKeyNum);
    _freeBTreeNode(insertNode, false);
    return 0;
}

int deleteBTree(BTree *btree, int val)
{
    int res = _deleteBTreeNode(btree->root, val, btree->m);
    if (btree->root->keyNum == 0) {
        BTreeNode *tmp = btree->root;
        if (tmp->children) {
            btree->root = *(tmp->children) ? *(tmp->children) : *(tmp->children + 1);
            _freeBTreeNode(tmp, false);
            tmp = NULL;
        } else {
            if (tmp->keyNum == 0) {
                btree->root = NULL;
                _freeBTreeNode(tmp, false);
                tmp = NULL;
            }
        }
    }
    return res;
}

BTreeNode * searchBTree(BTree *btree, int val)
{
    BTreeNode *node = btree->root;
    BTreeNode *searchRes = NULL;
    int i = 0;
    while (node) {
        while (i < node->keyNum && *(node->keys + i) < val)
        {
            i++;
        }
        if (i == node->keyNum || *(node->keys + i) > val) {
            if (!node->children) {
                fprintf(stderr, "this btree do not have this val: %d!\n", val);
                return NULL;
            } else {
                node = *(node->children + i);
            }
        } else {
            return node;
        }
        i = 0;
    }
    return NULL;
}

int freeBTree(BTree *btree)
{
    if (btree->root) {
        _freeBTreeNode(btree->root, true);
    }
    free(btree);
    btree = NULL;
    return 0;
}

void printBTree(BTree *btree)
{
    printBTreeNode(btree->root, btree->m - 1, 0);
}

void printBTreeNode(BTreeNode *node, int maxKeyNum, int level)
{
    printf("level: %d -- ", level);
    if (!node) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < node->keyNum; i++) {
        printf("%d, ", *(node->keys + i));
    }
    puts("\n");
    if (node->children) {
        for (int j = 0; j < node->keyNum + 1; j++) {
            printBTreeNode(*(node->children + j), maxKeyNum, level + 1);
        }
    }
}
