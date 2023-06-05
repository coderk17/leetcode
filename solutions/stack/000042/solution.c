/**
 * @file solution.c
 * @author coderk17
 * @brief Trapping Rain Water
 * @date 2023-06-05
 * 
 * Given n non-negative integers representing an elevation map
 * where the width of each bar is 1, compute how much water 
 * it can trap after raining.
 */

#include <stdio.h>
#include <stdlib.h>

int trap(int* height, int heightSize){
    if (heightSize <= 1)
        return 0;
    int top = -1, index = 0, stackSize = 10, res = 0;
    int left = height[index];
    int diff;
    int* stack = (int*)malloc(sizeof(int) * stackSize);
    while (index < heightSize - 1) {
        diff = height[++index] - left;
        if (diff >= 0) {
            // 1. Calculate the difference between the height of the left and the height of each pillar
            // in the stack and sum, then empty the stack.
            while (top >= 0) {
                res += (left - *(stack + top--));
            }
            // 2. Reset left.
            left = height[index];
        } else {
            // If right pillar is lower than left, push the height of right onto the stack.
            if (++top >= stackSize) {
                int *temp = NULL;
                stackSize *= 2;
                temp = (int*)realloc(stack, sizeof(int) * stackSize);
                if (NULL == temp)
                    return -1;
                stack = temp; 
            }
            *(stack + top) = height[index];
        }
    }
    if (top < 0)
        return res;

    int newHeightSize = top + 2;
    int* newHeight = (int*)malloc(sizeof(int) * (newHeightSize));
    if (newHeight == NULL)
        return -1;
    for (int i = 0; i <= newHeightSize - 2; i++) {
        newHeight[i] = *(stack + top--);
    }
    newHeight[newHeightSize - 1] = left;

    res += (trap(newHeight, newHeightSize));
    free(newHeight);
    free(stack);
    return res;
}

/*
 * run command:
 * $ gcc ./solutions/stack/000042/solution.c -o bin/stack/000042-solution
 * $ ./bin/stack/000042-solution
 */
int main(void)
{
    int *i1 = [0,1,0,2,1,0,1,3,2,1,2,1];
    printf("i1: %d\n", (i1));
}
