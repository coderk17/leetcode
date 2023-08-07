#include "avl_tree.h"

/*
 * command:
 * $ gcc -g lib/avl_tree.c lib/queue.c lib/stack.c test/test_avl_tree.c -I include/ -o bin/test/test_avl_tree -lm
 * $ ./bin/test/test_avl_tree
 */
int main()
{
    // int insertList[6] = {6, 4, 7, 3, 5, 2};    // insertList 4, 3, 6, 2, 5, 7
    // int insertList[6] = {6, 3, 7, 2, 4, 5};    // LR 4, 3, 6, 2, 5, 7
    // int insertList[6] = {3, 2, 5, 4, 6, 7};    // RR 5, 3, 6, 2, 4, 7
    int insertList[] = {3, 2, 6, 5, 7, 4};    // RL 5, 3, 6, 2, 4, 7
    const int insertListSIZE = sizeof(insertList) / sizeof(int);
    AVLTreeNode *insertRoot = initializeAVL(NULL, insertList, insertListSIZE);
    breadthFirstTraveral(insertRoot, 100);
    AVLTreeNode *searchNode = searchAVL(insertRoot, 2);
    printf("search result %p: %d\n", searchNode, searchNode->element);
    freeAVL(insertRoot);
    puts("===========================\n");
    int deleteList[] = {5, 2, 10, 1, 3, 8, 11, 4, 7, 9, 12, 6};
    const int deleteListSIZE = sizeof(deleteList) / sizeof(int);
    AVLTreeNode *deleteRoot = initializeAVL(NULL, deleteList, deleteListSIZE);
    puts("===========================\n");
    breadthFirstTraveral(deleteRoot, 100);
    puts("===========================\n");
    deleteRoot = deleteAVL(deleteRoot, 2);
    breadthFirstTraveral(deleteRoot, 100);
    freeAVL(deleteRoot);
}