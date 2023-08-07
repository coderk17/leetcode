#include "stack.h"

int stackIsEmpty(Stack *stack)
{
    if (stack->size == 0) {
        printf("stack is empty!\n");
        return 1;
    }
    return 0;
}

int stackIsFull(Stack *stack)
{
    if (stack->size == stack->maxSize) {
        printf("stack is full!\n");
        return 1;
    }
    return 0;
}

int initializeStack(Stack *stack, int maxSize)
{
    stack->top = -1;
    stack->size = 0;
    stack->maxSize = maxSize;
    int *tmp = malloc(sizeof(int) * maxSize);
    if (NULL == tmp) {
        printf("malloc memory failed!\n");
        return -1;
    }
    stack->elements = tmp;
    return 0;
}

int pop(Stack *stack)
{
    if (stackIsEmpty(stack))
        return -1;
    int val = stack->elements[stack->top--];
    stack->size--;
    printf("pop stack: %d\n", val);
    return val;
}

int push(Stack *stack, int val)
{
    if (stackIsFull(stack))
        return -1;
    stack->elements[++stack->top] = val;
    stack->size++;
    printf("push stack: %d\n", val);
    return 0;
}

int emptyStack(Stack *stack)
{
    stack->top = -1;
    stack->size = 0;
    printf("stack doing empty!\n");
    return 0;
}

int freeStack(Stack *stack)
{
    free(stack->elements);
    free(stack);
    return 0;
}
