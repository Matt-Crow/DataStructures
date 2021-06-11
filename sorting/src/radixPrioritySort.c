#include "radixPrioritySort.h"
#include<stdio.h>
#include<stdlib.h>

/*
So basically, here's my idea:
1. Radix sort's primary advantage is it doesn't make any actual comparisons.
2. That got me thinking... What is unique about radix sort?
   Well, it sorts each digit of the numbers it's given, in order of least to most importance.
   (sort numbers by ones place, then tens place, then hundreds, etc.).
   What if radix sort is really about this ascending order of importance, rather than just comparisonless sorting?
3. So radix sort can be expressed as just a series of sorts, ranging from least important sort to most important sort,
   where it is typically doing a "ones place sort", followed by a "tens place sort", then a "hundreds place sort", etc.
4. With that in mind, why does each sort need to be based on the same data type? It doesn't.
   With this idea of "unimportant sort", "moderately important sort", "important sort",
   one could sort different data types with each sort!
5. This is perfect for sorting objects (structs in this case), as normal sorting algorithms can't say
   "is object A greater than object B?" without assigning a comparable value to A and B.
   And rather than simply stating "is object A's property C greater than object B's property C?"
   we can say
   """
   first sort the list by property C,
   then by property D,
   then by property E,
   etc
   """
   So we can sort objects based on how important each property is!
   Cool!
*/

int testRadixPrioritySort(){
    Record* allRecords[] = {
        newRecord("Matt", "Crow", 22),
        newRecord("John", "Doe", 18),
        newRecord("Jane", "Doe", 9999999)
    };
    int numRecords = sizeof(allRecords) / sizeof(Record*);
    enum SortType priorities[] = {
        L_NAME,
        AGE,
        F_NAME
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

bool compareFName(Record* r1, Record* r2){
    return r1->fName > r2->fName;
}
bool compareLName(Record* r1, Record* r2){
    return r1->lName > r2->lName;
}
bool compareAge(Record* r1, Record* r2){
    return r1->age > r2->age;
}

/*
Sorts the given list of records based on the priority array.
The first element of priorities is the most important, with each after it being less and less important
*/
void radixPrioritySort(Record* records[], int numRecords, enum SortType priorities[], int numPriorities){
    if(numPriorities > 0){
        Record* temp;

        /*
        C function pointers.

        returns bool
              function address. Store in variable "comparator"
                           accepts 2 Record pointers
        */
        bool (*comparator)(Record*, Record*);

        switch(priorities[numPriorities - 1]){
            case F_NAME: // just do bubble sort, as I am tired
                comparator = &compareFName;
                break;
            case L_NAME:
                comparator = &compareLName;
                break;
            case AGE:
                comparator = &compareAge;
                break;
            default:
                printf("Uncaught SortType in radixPrioritySort: %d", priorities[numPriorities - 1]);
                comparator = 0;
                break;
        }
        if(comparator){
            for(int i = 0; i < numRecords - 1; i++){
                for(int j = 0; j < numRecords - i - 1; j++){
                    //  comparator function
                    //               pass these arguments
                    if((*comparator)(records[j], records[j + 1])){
                        temp = records[j + 1];
                        records[j + 1] = records[j];
                        records[j] = temp;
                        temp = 0;
                    }
                }
            }
        }
        radixPrioritySort(records, numRecords, priorities, numPriorities - 1);
    }
}
