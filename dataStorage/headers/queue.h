#ifndef QUEUE
#define QUEUE

typedef struct Queue {
    Queue* next;
    Queue* prev;
    int value;
} Queue;

Queue* newQueue(int val);
void deleteQueue(Queue** head, Queue** tail);

void enqueue(Queue** head, Queue** tail, int val);
int dequeue(Queue** head, Queue** tail);
int peek(Queue* head);

void printQueue(Queue* head);

int testQueue();

#endif
