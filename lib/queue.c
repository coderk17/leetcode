// #define DEBUG
#include "queue.h"

int initialize(Queue *queue, int maxSize) {
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

int isEmpty(Queue *queue) {
    return queue->size == 0;
};

int isFull(Queue *queue) {
    return queue->size == queue->maxSize;
};

int dequeue(Queue *queue) {
    if (isEmpty(queue)) {
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
    if (isFull(queue)) {
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

int empty(Queue *queue) {
    queue->size = 0;
    queue->front = 0;
    queue->rear = -1;
    return 0;
};
