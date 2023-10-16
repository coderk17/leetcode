#include "b_plus_tree.h"

int _freeBPlusTreeNode(BPlusTreeNode *node, bool isFreeChildren)
{
    int keyNum = node->keyNum;
    free(node->keys);
    node->keys = NULL;
    if (node->children) {
        if (isFreeChildren) {
            for (int i = 0; i < keyNum + 1; i++) {
                _freeBPlusTreeNode(*(node->children + i), isFreeChildren);
            }
        }
        free(node->children);
        node->children = NULL;
    }
    free(node);
    node = NULL;
    return 0;
}

BPlusTreeNode * _createBPlusTreeNode(int *keys, BPlusTreeNode **children, int index, int length, int maxKeyNum)
{
    BPlusTreeNode *node = (BPlusTreeNode *) malloc(sizeof(BPlusTreeNode));
    node->keys = (int *) malloc(sizeof(int) * (maxKeyNum + 1));
    node->children = NULL;
    node->next = NULL;
    node->keyNum = length;
    for (int i = 0; i < length; i++) {
        *(node->keys + i) = *(keys + index + i);
    }
    if (children) {
        node->children = (BPlusTreeNode **) calloc(maxKeyNum + 2, sizeof(BPlusTreeNode *));
        for (int i = 0; i < length + 1; i++) {
            *(node->children + i) = *(children + index + i);
        }
    }
    return node;
}

BPlusTreeNode * _splitBPlusTreeNode(BPlusTreeNode *node, int maxKeyNum)
{
    BPlusTreeNode *nextNode = NULL;
    int m = maxKeyNum + 1;
    int splitIndex = ceil(m / 2.0) - 1;

    int leftLength = splitIndex;
    int rightLength = maxKeyNum - leftLength;

    int leftIndex = 0;
    int rightIndex = splitIndex + 1;

    BPlusTreeNode *rightNode = _createBPlusTreeNode(node->keys, node->children, rightIndex, rightLength, maxKeyNum);

    if (!node->children) {
        leftLength++;
    }
    BPlusTreeNode *leftNode = _createBPlusTreeNode(node->keys, node->children, leftIndex, leftLength, maxKeyNum);
    BPlusTreeNode *newNode = _createBPlusTreeNode(node->keys, NULL, splitIndex, 1, maxKeyNum);
    newNode->children = (BPlusTreeNode **) calloc(m + 1, sizeof(BPlusTreeNode *));
    *(newNode->children) = leftNode;
    *(newNode->children + 1) = rightNode;
    _freeBPlusTreeNode(node, false);
    node = NULL;
    return newNode;
}

BPlusTreeNode * _insertBPlusTreeNode(BPlusTreeNode *node, BPlusTreeNode *insertNode, int maxKeyNum)
{
    int val = *(insertNode->keys);
    int keyNum = node->keyNum;
    int i = 0;
    while (i < keyNum && *(node->keys + i) < val)
    {
        i++;
    }
    if (node->children) {
        BPlusTreeNode *insertChild = *(node->children + i);
        BPlusTreeNode *oldChildNext = (*(node->children + i))->next;
        BPlusTreeNode *resNode = _insertBPlusTreeNode(insertChild, insertNode, maxKeyNum);
        if (resNode != insertChild) {
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
            if (!(*(node->children + i))->children) {
                (*(node->children + i))->next = *(node->children + i + 1);
                (*(node->children + i + 1))->next = oldChildNext;
                if (i > 0) {
                    (*(node->children + i - 1))->next = *(node->children + i);
                }
            }
            _freeBPlusTreeNode(resNode, false);
            resNode = NULL;
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
        node = _splitBPlusTreeNode(node, maxKeyNum);
    }
    return node;
}

BPlusTreeNode * _searchBPlusTreeNode(BPlusTreeNode *node, int val)
{
    int i = 0;
    while (i < node->keyNum && *(node->keys + i) < val)
    {
        i++;
    }
    if (i == node->keyNum || *(node->keys + i) > val) {
        if (node->children) {
            return _searchBPlusTreeNode(*(node->children + i), val);
        } else {
            return NULL;
        }
    } else {
        if (!node->children) {
            return node;
        }
        BPlusTreeNode *searchRes = _searchBPlusTreeNode(*(node->children + i), val);
        if (NULL == searchRes) {
            searchRes = _searchBPlusTreeNode(*(node->children + i + 1), val);
        }
        return searchRes;
    }
}

int _rebalance(BPlusTreeNode *node, int i, int minKeyNum)
{
    BPlusTreeNode *deleteChildNode = *(node->children + i);
    if (deleteChildNode->keyNum < minKeyNum) {
        BPlusTreeNode *leftChildNode = i > 0 ? *(node->children + i - 1) : NULL;
        BPlusTreeNode *rightChildNode = i < node->keyNum ? *(node->children + i + 1) : NULL;
        if (leftChildNode && leftChildNode->keyNum > minKeyNum) {
            int nodeVal = *(node->keys + i - 1);
            *(node->keys + i - 1) = *(leftChildNode->keys + (leftChildNode->keyNum - 1));
            for (int j = deleteChildNode->keyNum; j > 0; j--) {
                *(deleteChildNode->keys + j) = *(deleteChildNode->keys + j - 1);
            }
            if (leftChildNode->children) {
                *(deleteChildNode->keys) = nodeVal;
                for (int j = deleteChildNode->keyNum + 1; j > 0; j--) {
                    *(deleteChildNode->children + j) = *(deleteChildNode->children + j - 1);
                }
                *(deleteChildNode->children) = *(leftChildNode->children + leftChildNode->keyNum);
            } else {
                *(deleteChildNode->keys) = *(node->keys + i - 1);
            }
            leftChildNode->keyNum--;
            deleteChildNode->keyNum++;
        } else if (rightChildNode && rightChildNode->keyNum > minKeyNum) {
            int nodeVal = *(node->keys + i);
            *(node->keys + i) = *(rightChildNode->keys);
            for (int j = 0; j < rightChildNode->keyNum - 1; j++) {
                *(rightChildNode->keys + j) = *(rightChildNode->keys + j + 1);
            }
            if (rightChildNode->children) {
                *(deleteChildNode->keys + deleteChildNode->keyNum) = nodeVal;
                *(deleteChildNode->children + (deleteChildNode->keyNum + 1)) = *(rightChildNode->children);
                for (int j = 0; j < rightChildNode->keyNum; j++) {
                    *(rightChildNode->children + j) = *(rightChildNode->children + j + 1);
                }
            } else {
                *(deleteChildNode->keys + deleteChildNode->keyNum) = *(node->keys + i);
            }
            rightChildNode->keyNum--;
            deleteChildNode->keyNum++;
        } else {
            BPlusTreeNode *mergeNode = leftChildNode ? leftChildNode : deleteChildNode;
            BPlusTreeNode *moveNode = leftChildNode ? deleteChildNode : rightChildNode;
            int keyIndex = leftChildNode ? i - 1 : i;

            if (mergeNode->children) {
                *(mergeNode->keys + mergeNode->keyNum++) = *(node->keys + keyIndex);
            }
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
            _freeBPlusTreeNode(moveNode, false);
            moveNode = NULL;
        }
    }
}

int _deleteBTreeNode(BPlusTreeNode *node, int val, int m)
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
            BPlusTreeNode *leftNode = *(node->children + i);
            BPlusTreeNode *rightNode = *(node->children + i + 1);
            BPlusTreeNode *tmp = leftNode;
            BPlusTreeNode *tmpParent = leftNode;
            // find maximum value of left child node
            while (tmp->children)
            {
                tmp = *(tmp->children + tmp->keyNum);
            }
            realDeleteVal = *(tmp->keys + tmp->keyNum - 1);
            if (realDeleteVal != val) {
                // find minimum value of right child node
                tmp = rightNode;
                tmpParent = rightNode;
                while (tmp->children)
                {
                    tmp = *(tmp->children);
                }
                realDeleteVal = *(tmp->keys);
            }
            if (val != realDeleteVal) {
                fprintf(stderr, "This value not exists: %d!\n", val);
            }
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

BPlusTree * createBPlusTree(int m)
{
    BPlusTree *bPlusTree = (BPlusTree *) malloc(sizeof(BPlusTree));
    bPlusTree->m = m;
    bPlusTree->root = _createBPlusTreeNode(NULL, NULL, 0, 0, m);
    return bPlusTree;
}

int insertBPlusTree(BPlusTree *bPlusTree, int val)
{
    BPlusTreeNode *root = bPlusTree->root;
    int maxKeyNum = bPlusTree->m - 1;
    BPlusTreeNode *insertNode = _createBPlusTreeNode(&val, NULL, 0, 1, maxKeyNum);
    bPlusTree->root = _insertBPlusTreeNode(root, insertNode, maxKeyNum);
    _freeBPlusTreeNode(insertNode, false);
    insertNode = NULL;
    return 0;
}

int deleteBPlusTree(BPlusTree *btree, int val)
{
    int res = _deleteBTreeNode(btree->root, val, btree->m);
    if (btree->root->keyNum == 0) {
        BPlusTreeNode *tmp = btree->root;
        if (tmp->children) {
            btree->root = *(tmp->children) ? *(tmp->children) : *(tmp->children + 1);
            _freeBPlusTreeNode(tmp, false);
            tmp = NULL;
        } else {
            if (tmp->keyNum == 0) {
                btree->root = NULL;
                _freeBPlusTreeNode(tmp, false);
                tmp = NULL;
            }
        }
    }
    return res;
}

BPlusTreeNode * searchBPlusTree(BPlusTree *bPlusTree, int val)
{
    BPlusTreeNode *node = bPlusTree->root;
    BPlusTreeNode *searchRes = _searchBPlusTreeNode(node, val);
    if (NULL == searchRes) {
        fprintf(stderr, "this btree do not have this val: %d!\n", val);
    }
    return searchRes;
}

int freeBPlusTree(BPlusTree *bPlustree)
{
    if (bPlustree->root) {
        _freeBPlusTreeNode(bPlustree->root, true);
    }
    free(bPlustree);
    bPlustree = NULL;
    return 0;
}

void printBPlusTree(BPlusTree *btree)
{
    printBPlusTreeNode(btree->root, btree->m - 1, 0);
}

void printBPlusTreeNode(BPlusTreeNode *node, int maxKeyNum, int level)
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
            printBPlusTreeNode(*(node->children + j), maxKeyNum, level + 1);
        }
    }
}
