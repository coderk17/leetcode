#include "queue.h"

int main()
{
    Queue *q = (Queue *) malloc(sizeof(Queue));
    initializeQueue(q, 10);
    printf("max size: %d\n", q->maxSize);
    printf("queue is empty? %s\n", queueIsEmpty(q) == 1 ? "Yes" : "No");
    int data[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    for (int i = 0; i < 10; i++) {
        enqueue(q, data[i]);
    }
    printf("queue is full? %s\n", queueIsFull(q) == 1 ? "Yes" : "No");
    // enqueue(q, 11);
    dequeue(q);
    enqueue(q, 11);
    for (int i = 0; i < 5; i++) {
        dequeue(q);
    }
    for (int i = 12; i < 20; i++) {
        enqueue(q, i);
    }
    for (int i = 0; i < 13; i++) {
        dequeue(q);
    }
    free(q->elements);
    free(q);
    return 0;
}