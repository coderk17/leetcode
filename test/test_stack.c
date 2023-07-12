#include "stack.h"

int main()
{
    Stack *stack = (Stack *) malloc(sizeof(Stack));
    if (NULL == stack) {
        printf("malloc memory failed!");
        return -1;
    }
    initialize(stack, 10);
    printf("stack is empty? %s\n", isEmpty(stack) ? "Yes": "No");
    for (int i = 0; i < 10; i++) {
        push(stack, i+1);
    }
    printf("stack is full? %s\n", isFull(stack) ? "Yes": "No");
    for (int i = 0; i < 3; i++) {
        pop(stack);
    }
    for (int i = 10; i < 14; i++) {
        push(stack, i+1);
    }
    empty(stack);
    printf("stack is empty? %s\n", isEmpty(stack) ? "Yes": "No");
}