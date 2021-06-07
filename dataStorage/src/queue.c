#include "queue.h"
#include "core.h"
#include<stdio.h>
#include<stdlib.h>



/*
Private functions
*/

QueueNode* newQueueNode(int val){
    QueueNode* ret = (QueueNode*)malloc(sizeof(QueueNode));
    ret->next = 0;
    ret->prev = 0;
    ret->value = val;
    return ret;
}

/*
Does not cascade delete
*/
void deleteQueueNode(QueueNode** node){
    if(node && *node){
        free(*node);
        *node = 0;
    }
}



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
        while((*q)->head){
            printf("Delete %d\n", dequeue(*q));
        }
        free(*q);
        *q = 0;
    }
}

void enqueue(Queue* q, int val){
    if(q){
        QueueNode* newNode = newQueueNode(val);
        if(q->tail){ // at least one other node in the queue
            q->tail->next = newNode;
            newNode->prev = q->tail;
        } else { // no nodes currently in the queue
            q->head = newNode;
        }
        q->tail = newNode;
    }
}
int dequeue(Queue* q){
    int ret = 0;
    if(q && q->head){
        ret = peek(q);
        QueueNode* temp = q->head;
        q->head = temp->next;
        temp->next = 0;
        deleteQueueNode(&temp);
        if(q->head){ // still at least one node
            q->head->prev = 0;
        } else { //just deleted the only node
            q->tail = 0;
        }
    }
    return ret;
}
int peek(Queue* q){
    int ret = 0;
    if(q && q->head){
        ret = q->head->value;
    }
    return ret;
}

void printQueue(Queue* q){
    printf("%s", "Queue: ");
    QueueNode* curr = q->head;
    while(curr){
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("%s", "\n");
}



/*
Menu options
*/

Queue* asQueue(void** dataStructure){
    Queue** ptrPtr = (Queue**)dataStructure;
    return *ptrPtr;
}

void doPrintQueue(void** dataStructure){
    printQueue(asQueue(dataStructure));
}

void doEnqueQueue(void** dataStructure){
    int ip;
    printf("%s", "Enter value to enqueue: ");
    scanf("%d", &ip);
    enqueue(asQueue(dataStructure), ip);
}

void doDequeQueue(void** dataStructure){
    Queue* q = asQueue(dataStructure);
    if(q->head){
        int val = dequeue(q);
        printf("dequeued %d\n", val);
    } else {
        printf("%s\n",  "Nothing to dequeue");
    }
}



int testQueue(){
    Queue* q = newQueue();

    printf("%s\n",  "Queue");

    ConsumerMenuOption* options[] = {
            newConsumerMenuOption("print the queue", &doPrintQueue),
            newConsumerMenuOption("enqueue to the queue", &doEnqueQueue),
            newConsumerMenuOption("dequeue from the queue", &doDequeQueue)
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    doConsumerMenu(options, numOptions, (void**)&q);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteQueue(&q);

    return 0;
}
