#include <time.h>

#include "b_tree.h"

int main()
{
    long seed = time(NULL);
    srand(seed);

    int vals[] = {6, 10, 4, 14, 5, 11, 15, 3, 2, 12, 1, 7, 8, 8, 6, 3, 6, 21, 5, 15, 15, 6, 32, 23, 45, 65, 7, 8, 6, 5, 4};
    int dataSize = sizeof(vals) / sizeof(int);

    int m = seed % dataSize + 3;
    BTree *btree = createBTree(m);

    for (int i = 0; i < dataSize; i++) {
        insertBTree(btree, vals[i]);
        printBTree(btree);
    }
    puts("=============");
    printBTree(btree);
    puts("=============");
    BTreeNode *searchRes = searchBTree(btree, 15);
    // printBTreeNode(searchRes, btree->m - 1, 0);
    // 1. After a node is deleted, the B-tree structure is not affected
    // deleteBTree(btree, 65);
    // printBTree(btree);
    // 2. After a node is deleted, the balance of the B-tree is restored by borrowing sibling nodes
    // 2.1 Borrow from left child node
    // deleteBTree(btree, 4);
    // printBTree(btree);
    // 2.2 Borrow from right child node
    // deleteBTree(btree, 23);
    // printBTree(btree);
    // 2.3 Borrow from left child node with child nodes
    // deleteBTree(btree, 15);
    // printBTree(btree);
    // 2.4 Borrow from right child node with child nodes
    // insertBTree(btree, 8);
    // printBTree(btree);
    // puts("=============");
    // deleteBTree(btree, 15);
    // printBTree(btree);
    // 3. Convert to delete a leaf node
    // 3.1 Convert to delete the maximum of left subtree
    // deleteBTree(btree, 11);
    // printBTree(btree);
    // 3.2 Convert to delete the minimum of right subtree
    // deleteBTree(btree, 32);
    // printBTree(btree);
    // 3.3 Convert to delete subtree and borrow from brothers
    // deleteBTree(btree, 21);
    // printBTree(btree);
    // 4 After the node is deleted, the B-tree needs to merge child nodes to restore balance
    // 4.1 The merged node has no child nodes
    // deleteBTree(btree, 65);
    // printBTree(btree);
    // puts("=============");
    // deleteBTree(btree, 45);
    // printBTree(btree);
    // 4.2 The merged node has child nodes
    // deleteBTree(btree, 65);
    // printBTree(btree);
    // puts("=============");
    // deleteBTree(btree, 45);
    // printBTree(btree);
    // puts("=============");
    // deleteBTree(btree, 32);
    // printBTree(btree);
    // puts("=============");
    // deleteBTree(btree, 23);
    // printBTree(btree);

    int deleteRes = 0;

    for (int i = 0; i < 100; i++) {
        int r1 = rand() % dataSize;
        int r2 = rand() % dataSize;
        int tmp = vals[r1];
        vals[r1] = vals[r2];
        vals[r2] = tmp;
    }
    for (int i = 0; i < dataSize; i++) {
        printf("delete val: %d, %d\n", i, vals[i]);
        puts("=============");
        deleteRes = deleteBTree(btree, vals[i]);
        if (!deleteRes) {
            fprintf(stderr, "delete error: %d\n", vals[i]);
        }
        printBTree(btree);
    }
    printBTree(btree);
    freeBTree(btree);
}