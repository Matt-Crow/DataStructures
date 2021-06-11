#ifndef SORTING_UTIL
#define SORTING_UTIL

#include<stdbool.h>

#ifndef DEBUG
#define DEBUG 1
#endif

typedef struct QueueNode {
    int value;
    struct QueueNode* prev;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;

Queue* newQueue();
void deleteQueue(Queue** q);
void enqueue(Queue* q, int value);
int dequeue(Queue* q);
bool isQueueEmpty(Queue* q);

void printArray(int a[], int length);

#endif
