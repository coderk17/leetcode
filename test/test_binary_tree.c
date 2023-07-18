#include "binary_tree.h"

int main()
{
    // int data[] = {1, 2, null, 3, 4, 5, null, 6, null, 7};
    int data[] = {1, 2, 3, 4, null, 5, 6, null, null, 7, 8, null, 9};
    int size = sizeof(data) / sizeof(int);
    BinaryTreeNode *root = malloc(sizeof(BinaryTreeNode));
    breadthFirstInitialize(root, data, size);
    preorderTraveral(root);
    printf("===============\n");
    inorderTraveral(root);
    printf("===============\n");
    postorderTraveral(root);
    printf("===============\n");
    breadthFirstTraveral(root, 100);
    printf("===============\n");
    postorderFree(root);
    return 0;
}