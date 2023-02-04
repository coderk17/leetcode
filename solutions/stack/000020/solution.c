/**
 * @file solution.c
 * @author coderk17
 * @brief Valid Parentheses
 * @date 2023-02-04
 * 
 * Given a string s containing just the characters
 * '(', ')', '{', '}', '[' and ']', determine if the input string is valid.
 * 
 * An input string is valid if:
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * Every close bracket has a corresponding open bracket of the same type.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool isValid(char * s){
    int stackSize = 10;
    char *stack = (char *) malloc(sizeof(char) * stackSize);
    int top = 0;
    while (*s)
    {
        if (top >= stackSize) {
            char *temp = NULL;
            stackSize *= 2;
            temp = realloc(stack, sizeof(char) * stackSize);
            // realloc memory failed
            if (NULL == temp)
                return false;
            stack = temp;
        };
        switch (*s)
        {
            case '(':
            case '{':
            case '[':
                *(stack + top) = *s;
                top++;
                break;
            case ')':
                if (top > 0 && *(stack + top - 1) == '(') {
                    top--;
                } else {
                    return false;
                }
                break;

            case '}':
                if (top > 0 && *(stack + top - 1) == '{') {
                    top--;
                } else {
                    return false;
                }
                break;

            case ']':
                if (top > 0 && *(stack + top - 1) == '[') {
                    top--;
                } else {
                    return false;
                }
                break;
            default:
                return false;
        }
        s++;
    }
    return top == 0;
}


/*
 * run command:
 * $ gcc ./solutions/stack/000020/solution.c -o bin/stack/000020-solution
 * $ ./bin/stack/000020-solution
 */
int main(void)
{
    char *s1 = "{}[{}]";
    printf("s1: %d\n", isValid(s1));
    char *s2 = "[[[[[[[[[[[[[[[[[[[";
    printf("s2: %d\n", isValid(s2));
}
