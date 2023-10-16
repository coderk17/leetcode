#include <time.h>

#include "b_plus_tree.h"

int main()
{
    long seed = time(NULL);
    srand(seed);

    int vals[] = {6, 10, 4, 14, 5, 11, 15, 3, 2, 12, 1, 7, 8, 8, 6, 3, 6, 21, 5, 15, 15, 6, 32, 23, 45, 65, 7, 8, 6, 5, 4};
    int dataSize = sizeof(vals) / sizeof(int);

    int m = seed % dataSize + 3;
    BPlusTree *bPlusTree = createBPlusTree(m);

    for (int i = 0; i < dataSize; i++) {
        printf("-----%d, %d------\n", i, vals[i]);
        if (i == 8) {
            puts("=======");
        }
        insertBPlusTree(bPlusTree, vals[i]);
        printBPlusTree(bPlusTree);
    }
    puts("=============");
    printBPlusTree(bPlusTree);
    puts("=============");
    BPlusTreeNode *searchRes = NULL;
    for (int i = 0; i < dataSize - 1; i++) {
        searchRes = searchBPlusTree(bPlusTree, vals[i]);
        printf("search %d result: ", vals[i]);
        printBPlusTreeNode(searchRes, m - 1, 1);
        printf("next node result: ");
        printBPlusTreeNode(searchRes->next, m - 1, 1);
    }
    puts("=============");
    // BPlusTreeNode *searchRes = searchBPlusTree(bPlusTree, 15);
    // printBPlusTreeNode(searchRes, bPlusTree->m - 1, 0);
    // 1. After a node is deleted, the B-tree structure is not affected
    // deleteBPlusTree(bPlusTree, 65);
    // printBPlusTree(bPlusTree);
    // 2. After a node is deleted, the balance of the B-tree is restored by borrowing sibling nodes
    // 2.1 Borrow from left child node
    // deleteBPlusTree(bPlusTree, 4);
    // printBPlusTree(bPlusTree);
    // 2.2 Borrow from right child node
    // deleteBPlusTree(bPlusTree, 23);
    // printBPlusTree(bPlusTree);
    // 2.3 Borrow from left child node with child nodes
    // deleteBPlusTree(bPlusTree, 15);
    // printBPlusTree(bPlusTree);
    // 2.4 Borrow from right child node with child nodes
    // insertBPlusTree(bPlusTree, 8);
    // printBPlusTree(bPlusTree);
    // puts("=============");
    // deleteBPlusTree(bPlusTree, 15);
    // printBPlusTree(bPlusTree);
    // 3. Convert to delete a leaf node
    // 3.1 Convert to delete the maximum of left subPlusTree
    // deleteBPlusTree(bPlusTree, 11);
    // printBPlusTree(bPlusTree);
    // 3.2 Convert to delete the minimum of right subPlusTree
    // deleteBPlusTree(bPlusTree, 32);
    // printBPlusTree(bPlusTree);
    // 3.3 Convert to delete subPlusTree and borrow from brothers
    // deleteBPlusTree(bPlusTree, 21);
    // printBPlusTree(bPlusTree);
    // 4 After the node is deleted, the B-tree needs to merge child nodes to restore balance
    // 4.1 The merged node has no child nodes
    // deleteBPlusTree(bPlusTree, 65);
    // printBPlusTree(bPlusTree);
    // puts("=============");
    // deleteBPlusTree(bPlusTree, 45);
    // printBPlusTree(bPlusTree);
    // 4.2 The merged node has child nodes
    // deleteBPlusTree(bPlusTree, 65);
    // printBPlusTree(bPlusTree);
    // puts("=============");
    // deleteBPlusTree(bPlusTree, 45);
    // printBPlusTree(bPlusTree);
    // puts("=============");
    // deleteBPlusTree(bPlusTree, 32);
    // printBPlusTree(bPlusTree);
    // puts("=============");
    // deleteBPlusTree(bPlusTree, 23);
    // printBPlusTree(bPlusTree);

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
        deleteRes = deleteBPlusTree(bPlusTree, vals[i]);
        if (!deleteRes) {
            fprintf(stderr, "delete error: %d\n", vals[i]);
        }
        printBPlusTree(bPlusTree);
    }
    freeBPlusTree(bPlusTree);
    printf("m: %d\n", m);
}