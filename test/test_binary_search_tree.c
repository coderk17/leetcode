#include "binary_search_tree.h"

/*
 * command:
 * $ gcc -g lib/binary_tree.c lib/queue.c lib/binary_search_tree.c test/test_binary_search_tree.c -I include/ -o bin/test/test_binary_search_tree -lm
 * $ ./bin/test/test_binary_search_tree
 * 
 */
int main()
{
    int data[] = {6, 13, 3, 15, 1, 11, 2, 4, 14, 8, 9, 12, 7, 10, 5};
    int size = sizeof(data) / sizeof(int);
    int searchVal = 10;
    printf("size: %d\n", size);
    BinarySearchTreeNode *root = (BinarySearchTreeNode *) malloc(sizeof(BinarySearchTreeNode));
    initializeBST(root, data, size);
    deleteBST(root, 13);
    BinarySearchTreeNode *searchRes = searchBST(root, searchVal);
    if (NULL != searchRes)
        printf("search node %d: %p -- %d\n", searchVal, searchRes, searchRes->element);
    breadthFirstTraveral(root, 1000);
    printf("==================\n");
    preorderTraveral(root);
    freeBST(root);
}