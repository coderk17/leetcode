#ifndef LEETCODE_QUEUE_H_
#define LEETCODE_QUEUE_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Queue {
    int front;
    int rear;
    int maxSize;
    int size;
    int *elements;
};

typedef struct Queue Queue;

int queueIsEmpty(Queue *queue);
int queueIsFull(Queue *queue);
int initializeQueue(Queue *queue, int maxSize);
int dequeue(Queue *queue);
int enqueue(Queue *queue, int val);
int emptyQueue(Queue *queue);

#endif /* LEETCODE_QUEUE_H_ */ 
