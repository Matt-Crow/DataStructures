#ifndef QUEUE
#define QUEUE

typedef struct QueueNode {
    struct QueueNode* next;
    struct QueueNode* prev;
    int value;
} QueueNode;

typedef struct Queue {
    QueueNode* head;
    QueueNode* tail;
} Queue;

Queue* newQueue();

/*
Deletes the given Queue and each node in it
*/
void deleteQueue(Queue** q);

void enqueue(Queue* q, int val);
int dequeue(Queue* q);
int peek(Queue* q);

void printQueue(Queue* q);

int testQueue();

#endif
