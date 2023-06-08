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
#include <math.h>

int trap(int* height, int heightSize) {
    int top = -1;
    int res = 0;
    int stackSize = 10;
    int* stack = (int*)malloc(sizeof(int) * stackSize);
    for (int i = 0; i < heightSize; i++) {
        while (top >= 0 && height[i] > height[stack[top]]) {
            int index = stack[top--];
            if (top < 0) break;
            int left = stack[top];
            int diffH = fmin(height[i], height[left]) - height[index];
            int diffW = i - (left + 1);
            res += diffH * diffW; 
        }
        if (top + 1 >= stackSize) {
            stackSize *= 2;
            int* tmp = (int*)realloc(stack, sizeof(int) * stackSize);
            if (NULL == tmp) {
                free(stack);
                return -1;
            }
            stack = tmp;
        }
        stack[++top] = i;
    }
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
    // int i1[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    // int i1[] = {4,2,0,3,2,5};
    // int i1[] = {4,2,0,3,2,4,3,4};
    int i1[] = {5,2,1,2,1,5};
    int size = sizeof(i1) / sizeof(int);
    printf("i1: %d\n", trap(i1, size));
}
