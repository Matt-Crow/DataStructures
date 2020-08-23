#include "radixPrioritySort.h"
#include<stdio.h>
#include<stdlib.h>



int testRadixPrioritySort(){
    //Record* me = newRecord("Matt", "Crow", 22);
    //printRecord(me);
    //deleteRecord(me);
    //me = 0;
    RecordQueue* head = 0;
    RecordQueue* tail = 0;
    enqueueRecordQueue(&head, &tail, newRecord("Matt", "Crow", 22));
    enqueueRecordQueue(&head, &tail, newRecord("John", "Doe", 18));
    enqueueRecordQueue(&head, &tail, newRecord("Jane", "Doe", 9999999));
    printRecordQueue(head);
    deleteRecordQueue(&head, &tail);
    head = 0;
    tail = 0;
    return 0;
}

Record* newRecord(char fName[], char lName[], int age){
    Record* newRec = (Record*)malloc(sizeof(Record));
    newRec->fName = fName;
    newRec->lName = lName;
    newRec->age = age;
    return newRec;
}
void deleteRecord(Record* record){
    free(record);
}
void printRecord(Record* record){
    if(record){
        printf("%s, %s (age %d)", record->lName, record->fName, record->age);
    } else {
        printf("%s", "Record is null");
    }
}

RecordQueue* newRecordQueue(Record* value){
    RecordQueue* q = (RecordQueue*)malloc(sizeof(RecordQueue));
    q->next = 0;
    q->prev = 0;
    q->value = value;
    return q;
}
void deleteRecordQueue(RecordQueue** head, RecordQueue** tail){
    while(*head){
        printf("%s", "deleting ");
        printRecord(dequeueRecordQueue(head, tail));
        printf("%s", "\n");
    }
}
void enqueueRecordQueue(RecordQueue** head, RecordQueue** tail, Record* value){
    if(head && tail){
        RecordQueue* newNode = newRecordQueue(value);
        if(*tail){
            // has at least 1 node, so append to end
            (*tail)->next = newNode;
            newNode->prev = *tail;
        } else {
            // tail points to null pointer, so no nodes exist
            *head = newNode;
        }
        *tail = newNode;
    }
}
Record* dequeueRecordQueue(RecordQueue** head, RecordQueue** tail){
    Record* ret = 0;
    //                 make sure head doesn't point to null pointer
    if(head && tail && *head){
        RecordQueue* temp = *head; // keep track of local head...
        *head = temp->next; // move external head forward...
        temp->prev = 0;
        temp->next = 0; // cut local head off from the other nodes.
        ret = temp->value; // prepare to return the head's value
        temp->value = 0; // prevent its value from being deleted
        free(temp); // deletes the local head
        if(*head){
            // check if there were at least 2 nodes. This is the new head.
            (*head)->prev = 0;
        } else {
            // nope, only had one node
            *tail = 0;
        }
    }
    return ret;
}
void printRecordQueue(RecordQueue* head){
    RecordQueue* curr = head;
    while(curr){
        printRecord(curr->value);
        if(curr->next){
            printf("%s", " => ");
        }
        curr = curr->next;
    }
}
