/**
 * @file solution.c
 * @author coderk17
 * @brief Longest Valid Parentheses
 * @date 2023-02-04
 * 
 * Given a string containing just the characters '(' and ')',
 * return the length of the longest valid (well-formed) 
 * parentheses substring.
 */

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int longestValidParentheses(char * s){
    int maxLegth = 0, index = 0;
    int top = -1, stackSize = 10;
    int *stack = (int *) malloc(sizeof(int) * stackSize);
    *(stack + ++top) = -1;
    while (*s) {
        if (top >= stackSize) {
            int *temp = NULL;
            stackSize *= 2;
            temp = (int *) realloc(stack, sizeof(int) * stackSize);
            if (NULL == temp)
                return -1;
            stack = temp; 
        }
        switch (*s) {
            case '(':
                *(stack + ++top) = index;
                break;
            case ')':
                top--;
                if (top == -1) {
                    *(stack + ++top) = index;
                } else {
                    maxLegth = fmax(maxLegth, index - *(stack + top));
                }
                break;
            default:
                return -1;
        }
        s++;
        index++;
    }
    return maxLegth;
}


/*
 * run command:
 * $ gcc ./solutions/stack/000032/solution.c -o bin/stack/000032-solution
 * $ ./bin/stack/000032-solution
 */
int main(void)
{
    char *s1 = "()(()";
    printf("s1: %d\n", longestValidParentheses(s1));
    char *s2 = ")(()(()(((())(((((()()))((((()()(()()())())())()))()()()())(())()()(((()))))()((()))(((())()((()()())((())))(())))())((()())()()((()((())))))((()(((((()((()))(()()(())))((()))()))())";
    printf("s2: %d\n", longestValidParentheses(s2));
}
