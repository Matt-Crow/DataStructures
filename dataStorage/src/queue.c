#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

Queue* newQueue(int val){
    Queue* ret = (Queue*)malloc(sizeof(Queue));
    ret->next = 0;
    ret->prev = 0;
    ret->value = val;
    return ret;
}
void deleteQueue(Queue** head, Queue** tail){
    while(*head){
        printf("Delete %i\n", dequeue(head, tail));
    }
}

void enqueue(Queue** head, Queue** tail, int val){
    if(head && tail){
        Queue* newNode = newQueue(val);
        if(*tail){
            (*tail)->next = newNode;
            newNode->prev = *tail;
        } else {
            //no nodes
            *head = newNode;
        }
        *tail = newNode;
    }
}
int dequeue(Queue** head, Queue** tail){
    int ret = 0;
    if(head && tail){
        ret = peek(*head);
        if(*head){
            Queue* temp = *head;
            *head = temp->next;
            temp->next = 0;
            delete temp;
            if(*head){
                (*head)->prev = 0;
            } else {
                //just deleted the only node
                *tail = 0;
            }
        }
    }
    return ret;
}
int peek(Queue* head){
    int ret = 0;
    if(head){
        ret = head->value;
    }
    return ret;
}

void printQueue(Queue* head){
    printf("%s", "Queue:\n");
    Queue* curr = head;
    while(curr){
        if(curr->next){
            printf("%i, ", curr->value);
        } else {
            printf("%i", curr->value);
        }
        curr = curr->next;
    }
    printf("%s", "\n");
}

int testQueue(){
    Queue* head = 0;
    Queue* tail = 0;

    int ip = 0;
    printf("%s",  "===QUEUE===" );
    while(ip != -1){
        printf("%s\n", "~~~~~~~~~~~~~~~~~~~~~~~~~~~" );
        printf("%s\n", "Choose an option: ");
        printf("%s\n", "0: print the queue");
        printf("%s\n", "1: enqueue to the queue");
        printf("%s\n", "2: dequeue the queue");
        printf("%s\n", "-1: quit");
        scanf("%d", &ip);
        switch(ip){
        case 0:
            printQueue(head);
            break;
        case 1:
            printf("%s", "Enter value to enqueue: ");
            scanf("%d", &ip);
            enqueue(&head, &tail, ip);
            ip = 1;
            break;
        case 2:
            if(head && tail){
                ip = dequeue(&head, &tail);
                printf("dequeued %i\n", ip);
                ip = 2;
            } else {
                printf("%s\n",  "Nothing to dequeue");
            }
            break;
        }
    }

    deleteQueue(&head, &tail);
    head = 0;
    tail = 0;
    return 0;
}
