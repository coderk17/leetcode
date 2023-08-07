#ifndef LEETCODE_STACK_H_
#define LEETCODE_STACK_H_

#include <stdio.h>
#include <stdlib.h>

struct Stack {
    int maxSize;
    int top;
    int size;
    int *elements;
};

typedef struct Stack Stack;

int stackIsEmpty(Stack *stack);
int stackIsFull(Stack *stack);
int initializeStack(Stack *stack, int maxSize);
int pop(Stack *stack);
int push(Stack *stack, int val);
int emptyStack(Stack *stack);
int freeStack(Stack *stack);

#endif /* LEETCODE_STACK_H_ */
