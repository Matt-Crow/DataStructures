#include "radixPrioritySort.h"
#include<stdio.h>
#include<stdlib.h>



int testRadixPrioritySort(){
    Record* me = newRecord("Matt", "Crow", 22);
    printRecord(me);
    deleteRecord(me);
    me = 0;
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
    return 0;
}
void deleteRecordQueue(RecordQueue** head, RecordQueue** tail){

}
void enqueue(RecordQueue** head, RecordQueue** tail, Record* value){

}
void printRecordQueue(RecordQueue* head){

}
