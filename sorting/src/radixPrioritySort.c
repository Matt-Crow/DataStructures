#include "radixPrioritySort.h"
#include<stdio.h>
#include<stdlib.h>



int testRadixPrioritySort(){
    Record* allRecords[] = {
        newRecord("Matt", "Crow", 22),
        newRecord("John", "Doe", 18),
        newRecord("Jane", "Doe", 9999999)
    };
    int numRecords = sizeof(allRecords) / sizeof(Record*);
    enum SortType priorities[] = {
        AGE,
        F_NAME,
        L_NAME
    };
    int numPriorities = sizeof(priorities) / sizeof(enum SortType);

    printRecords(allRecords, numRecords);
    radixPrioritySort(allRecords, numRecords, priorities, numPriorities);
    printf("%s", "After sorting:\n");
    printRecords(allRecords, numRecords);
    for(int i = 0; i < numRecords; i++){
        deleteRecord(allRecords[i]);
        allRecords[i] = 0;
    }
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
void printRecords(Record* records[], int recordCount){
    printf("%s", "RECORDS:");
    for(int i = 0; i < recordCount; i++){
        printf("%s", "\n");
        printRecord(records[i]);
    }
    printf("%s", "\nEND OF RECORDS\n");
}

void radixPrioritySort(Record* records[], int numRecords, enum SortType priorities[], int numPriorities){
    if(numPriorities > 0){
        Record* temp;
        switch(priorities[numPriorities - 1]){
            case F_NAME: // just do bubble sort, as I am tired
                for(int i = 0; i < numRecords - 1; i++){
                    for(int j = 0; j < numRecords - i - 1; j++){
                        if(records[j]->fName > records[j + 1]->fName){
                            temp = records[j + 1];
                            records[j + 1] = records[j];
                            records[j] = temp;
                            temp = 0;
                        }
                    }
                }
                break;
            case L_NAME:
                for(int i = 0; i < numRecords - 1; i++){
                    for(int j = 0; j < numRecords - i - 1; j++){
                        if(records[j]->lName > records[j + 1]->lName){
                            temp = records[j + 1];
                            records[j + 1] = records[j];
                            records[j] = temp;
                            temp = 0;
                        }
                    }
                }
                break;
            case AGE:
                for(int i = 0; i < numRecords - 1; i++){
                    for(int j = 0; j < numRecords - i - 1; j++){
                        if(records[j]->age > records[j + 1]->age){
                            temp = records[j + 1];
                            records[j + 1] = records[j];
                            records[j] = temp;
                            temp = 0;
                        }
                    }
                }
                break;
            default:
                printf("Uncaught SortType in radixPrioritySort: %d", priorities[numPriorities - 1]);
        }
        radixPrioritySort(records, numRecords, priorities, numPriorities - 1);
    }
}
