#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

/*
Private prototypes
*/

QueueNode* newQueueNode(int value);

Stack* newStack(int value);


/*
Public functions
*/

Queue* newQueue(){
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->head = 0;
    q->tail = 0;
    return q;
}

void deleteQueue(Queue** q){
    if(q && *q){
        Queue* emptyMe = *q;
        while(!isQueueEmpty(emptyMe)){
            dequeue(emptyMe);
        }
        free(emptyMe);
        *q = 0;
    }
}

void enqueue(Queue* q, int value){
    QueueNode* nn = newQueueNode(value);
    nn->prev = q->tail;
    if(q->head){ // at least one node prior to this
        q->tail->next = nn;
    } else { // nn is now the only node
        q->head = nn;
    }
    q->tail = nn;
}

int dequeue(Queue* q){
    // will purposely crash if nothing in the queue
    int value = q->head->value;
    QueueNode* oldHead = q->head;
    q->head = q->head->next;
    free(oldHead);
    return value;
}

bool isQueueEmpty(Queue* q){
    return q->head == 0;
}

void deleteStack(Stack** top){
    if(top && *top){
        while(*top){
            pop(top);
        }
    }
}

void push(Stack** top, int value){
    Stack* newTop = newStack(value);
    newTop->value = value;
    newTop->next = *top;
    *top = newTop;
}

int pop(Stack** top){
    // purposely crashes if the stack is empty
    Stack* oldTop = *top;
    int value = oldTop->value;
    *top = oldTop->next;
    free(oldTop);
    return value;
}

void printArray(int a[], int length){
    printf("%c", '[');
    for(int i = 0; i < length; ++i){
        if(i % 10 == 0){ // only 10 elements per line to make it easier to read
            printf("%s", "\n\t");
        }
        if(i == length - 1){ // last element
            printf("%d\n", a[i]);
        } else {
            printf("%d, ", a[i]);
        }
    }
    printf("%s", "]\n");
}



/*
Private function implementations
*/


QueueNode* newQueueNode(int value){
    QueueNode* nn = (QueueNode*)malloc(sizeof(QueueNode));
    nn->next = 0;
    nn->prev = 0;
    nn->value = value;
    return nn;
}

Stack* newStack(int value){
    Stack* frame = (Stack*)malloc(sizeof(Stack));
    frame->next = 0;
    frame->value = value;
    return frame;
}
