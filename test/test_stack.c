#include "stack.h"

int main()
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (NULL == stack) {
        printf("malloc memory failed!");
        return -1;
    }
    initializeStack(stack, 10);
    printf("stack is empty? %s\n", stackIsEmpty(stack) ? "Yes": "No");
    for (int i = 0; i < 10; i++) {
        push(stack, i+1);
    }
    printf("stack is full? %s\n", stackIsFull(stack) ? "Yes": "No");
    for (int i = 0; i < 3; i++) {
        pop(stack);
    }
    for (int i = 10; i < 14; i++) {
        push(stack, i+1);
    }
    emptyStack(stack);
    printf("stack is empty? %s\n", stackIsEmpty(stack) ? "Yes": "No");
}