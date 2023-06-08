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
    int n = heightSize;
    if (n == 0) {
        return 0;
    }
    int ans = 0;
    int stk[n], top = 0;
    for (int i = 0; i < n; ++i) {
        while (top && height[i] > height[stk[top - 1]]) {
            int stk_top = stk[--top];
            if (!top) {
                break;
            }
            int left = stk[top - 1];
            int currWidth = i - left - 1;
            int currHeight = fmin(height[left], height[i]) - height[stk_top];
            ans += currWidth * currHeight;
        }
        stk[top++] = i;
    }
    return ans;
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
    int i1[] = {4,2,0,3,2,4,3,4};
    int size = sizeof(i1) / sizeof(int);
    printf("i1: %d\n", trap(i1, size));
}
