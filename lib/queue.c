// #define DEBUG
#include "queue.h"

int initializeQueue(Queue *queue, int maxSize) {
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    queue->maxSize = maxSize;
    int *tmp = (int *) malloc(sizeof(int) * maxSize);
    if (tmp == NULL) {
        printf("Malloc failed!\n");
        return -1;
    }
    queue->elements = tmp;
    return 0;
}

int queueIsEmpty(Queue *queue) {
    return queue->size == 0;
};

int queueIsFull(Queue *queue) {
    return queue->size == queue->maxSize;
};

int dequeue(Queue *queue) {
    if (queueIsEmpty(queue)) {
        printf("Queue is empty!\n");
        return -1;
    }
    int val = queue->elements[queue->front++ % queue->maxSize];
    queue->size--;
#ifdef DEBUG
    printf("dequeue: %d, size: %d \n", val, queue->size);
#endif
    return val;
};

int enqueue(Queue *queue, int val) {
    if (queueIsFull(queue)) {
        printf("Queue is full!\n");
        return -1;
    }
    queue->rear++;
    queue->elements[queue->rear % queue->maxSize] = val;
    queue->size++;
#ifdef DEBUG
    printf("enqueue: %d, size: %d \n", queue->elements[queue->rear % queue->maxSize], queue->size);
#endif
    return 0;
};

int emptyQueue(Queue *queue) {
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    return 0;
};

int freeQueue(Queue *queue)
{
    free(queue->elements);
    queue->elements = NULL;
    free(queue);
    queue = NULL;
}
