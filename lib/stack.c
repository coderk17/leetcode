#include "stack.h"

int isEmpty(Stack *stack)
{
    if (stack->size == 0) {
        printf("stack is empty!\n");
        return 1;
    }
    return 0;
}

int isFull(Stack *stack)
{
    if (stack->size == stack->maxSize) {
        printf("stack is full!\n");
        return 1;
    }
    return 0;
}

int initialize(Stack *stack, int maxSize)
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
    if (isEmpty(stack))
        return -1;
    int val = stack->elements[stack->top--];
    stack->size--;
    printf("pop stack: %d\n", val);
    return val;
}

int push(Stack *stack, int val)
{
    if (isFull(stack))
        return -1;
    stack->elements[++stack->top] = val;
    stack->size++;
    printf("push stack: %d\n", val);
    return 0;
}

int empty(Stack *stack)
{
    stack->top = -1;
    stack->size = 0;
    printf("stack doing empty!\n");
    return 0;
}
