#ifndef SORTING_UTIL
#define SORTING_UTIL

#include<stdbool.h>

#ifndef DEBUG
#define DEBUG 0
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

typedef struct Stack {
    struct Stack* next;
    int value;
} Stack;

void deleteStack(Stack** top);
void push(Stack** top, int value);
int pop(Stack** top);

void printArray(int a[], int length);

#endif
