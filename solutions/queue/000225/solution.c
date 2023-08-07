/**
 * @file solution.c
 * @author coderk17
 * @brief Implement Stack using Queues
 * @date 2023-07-11
 * 
 * Implement a last-in-first-out (LIFO) stack using only two queues. 
 * The implemented stack should support all the functions of a normal stack (push, top, pop, and empty).
 *
 * Implement the MyStack class:
 * void push(int x) Pushes element x to the top of the stack.
 * int pop() Removes the element on the top of the stack and returns it.
 * int top() Returns the element on the top of the stack.
 * boolean empty() Returns true if the stack is empty, false otherwise.
 * 
 * Notes:
 * You must use only standard operations of a queue, which means that only push to back, 
 * peek/pop from front, size and is empty operations are valid.
 * 
 * Depending on your language, the queue may not be supported natively. 
 * You may simulate a queue using a list or deque (double-ended queue) as long as
 * you use only a queue's standard operations.
 */

#include "queue.h"

typedef struct {
    Queue *queues[2];
    int empty;
} MyStack;


MyStack* myStackCreate() {
    MyStack *myStack = malloc(sizeof(MyStack));
    myStack->queues[0] = malloc(sizeof(Queue));
    myStack->queues[1] = malloc(sizeof(Queue));
    initializeStack(myStack->queues[0], 100);
    initializeStack(myStack->queues[1], 100);
    myStack->empty = 0;
    return myStack;
}

void myStackPush(MyStack* obj, int x) {
    int empty = obj->empty;
    enqueue(obj->queues[empty], x);
    while (!queueIsEmpty(obj->queues[1 - empty])) {
        int val = dequeue(obj->queues[1 - empty]);
        enqueue(obj->queues[empty], val);
    }
    obj->empty = 1 - empty;
}

int myStackPop(MyStack* obj) {
    int val = dequeue(obj->queues[1 - obj->empty]);
    return val;
}

int myStackTop(MyStack* obj) {
    int val = dequeue(obj->queues[1 - obj->empty]);
    myStackPush(obj, val);
    return val;
}

bool myStackEmpty(MyStack* obj) {
    return obj->queues[1 - obj->empty]->size == 0;
}

void myStackFree(MyStack* obj) {
    obj->queues[1 - obj->empty]->size == 0;
    free(obj->queues[0]->elements);
    free(obj->queues[1]->elements);
    free(obj->queues[0]);
    free(obj->queues[1]);
    free(obj);
}

/*
 * run command:
 * $ gcc ./solutions/queue/000225/solution.c ./lib/queue.c -o bin/queue/000225-solution -I ./include
 * $ ./bin/queue/000225-solution
 */
int main()
{
    MyStack *myStack = myStackCreate();
    for (int i = 0; i < 10; i++) {
        myStackPush(myStack, i);
    }
    printf("++++++++++++++++++++++++++++++++\n");
    for (int i = 0; i < 10; i++) {
        printf("stack is empty? %s\n", myStackEmpty(myStack) ? "Yes" : "No");
        myStackPop(myStack);
    }
    printf("stack is empty? %s\n", myStackEmpty(myStack) ? "Yes" : "No");
    myStackFree(myStack);
    return 0;
}

/**
 * Your MyStack struct will be instantiated and called as such:
 * MyStack* obj = myStackCreate();
 * myStackPush(obj, x);
 
 * int param_2 = myStackPop(obj);
 
 * int param_3 = myStackTop(obj);
 
 * bool param_4 = myStackEmpty(obj);
 
 * myStackFree(obj);
*/
 