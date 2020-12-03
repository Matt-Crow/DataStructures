#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashArray.h"

HashArray* newHashArray(int capacity){
    HashArray* ret = 0;
    if(capacity < 0){
        printf("Hash Array cannot have negative capacity: %d\n", capacity);
    } else {
        ret = (HashArray*)malloc(sizeof(HashArray));
        ret->capacity = capacity;
        ret->contents = (int**)malloc(sizeof(int*) * capacity);
        memset(ret->contents, 0, capacity); // set contents to array of null pointers to ints
    }
    return ret;
}

SearchResult* newSearchResult(int searchedFor, bool isFound, int foundAt, int collisions){
    SearchResult* ret = (SearchResult*)malloc(sizeof(SearchResult));
    ret->searchedFor = searchedFor;
    ret->isFound = isFound;
    ret->foundAt = foundAt;
    ret->collisions = collisions;
    return ret;
}

void deleteHashArray(HashArray** deleteThis){
    if(deleteThis && *deleteThis){ // not null pointer or pointer to null pointer
        // free contents pointers
        int* ptr = 0;
        for(int i = 0; i < (*deleteThis)->capacity; i++){
            ptr = (*deleteThis)->contents[i];
            if(ptr){
                printf("Deleting %d\n", *ptr);
                free(ptr);
                ptr = 0;
            }
        }
        free((*deleteThis)->contents);
        free(*deleteThis);
        *deleteThis = 0;
    }
}
void deleteSearchResult(SearchResult** deleteThis){
    if(deleteThis && *deleteThis){
        free(*deleteThis);
        *deleteThis = 0;
    }
}

SearchResult* putInHashArray(HashArray* intoHere, int val){
    SearchResult* whereItWasInserted = 0;
    if(intoHere){
        int numSearchStrategies = 2;
        SearchResult* (*searchStrategies[])(HashArray*, int) = {&lpForEmpty, &qpForEmpty};
        for(int i = 0; i < numSearchStrategies && !whereItWasInserted; i++){
            whereItWasInserted = searchStrategies[i](intoHere, val);
            if(whereItWasInserted && !whereItWasInserted->isFound){
                deleteSearchResult(&whereItWasInserted);
            }
        }

        if(whereItWasInserted && whereItWasInserted->isFound){
            intoHere->contents[whereItWasInserted->foundAt] = (int*)malloc(sizeof(int));
            *(intoHere->contents[whereItWasInserted->foundAt]) = val;
        }
    }
    return whereItWasInserted;
}
SearchResult* getFromHashArray(HashArray* fromHere, int val){
    return 0;
}

bool isEmpty(HashArray* checkThis, int idx, int dummyParameter){
    return checkThis && !(checkThis->contents[idx]);
}
bool containsValue(HashArray* checkThis, int idx, int value){
    return checkThis && checkThis->contents[idx] && *(checkThis->contents[idx]) == value;
}


SearchResult* qpNew(HashArray* probeThis, int startIdx, int searchFor, bool (*checkIfFound)(HashArray*, int, int)){
    SearchResult* ret = 0;

    if(probeThis){
        ret = newSearchResult(searchFor, false, -1, 0);
        int newIdx = 0;
        for(int offset = 1; !(ret->isFound) && offset <= 3; offset++){
            // index to check
            newIdx = (startIdx + offset * offset) % probeThis->capacity;
            if(checkIfFound(probeThis, newIdx, searchFor)){
                ret->foundAt = newIdx;
                ret->isFound = true;
            } else {
                ret->collisions++;
            }
        }
    }

    return ret;
}

SearchResult* quadraticProbe(HashArray* probeThis, int startIdx, int searchFor){
    return qpNew(probeThis, startIdx, searchFor, &containsValue);
}
SearchResult* qpForEmpty(HashArray* probeThis, int startIdx){
    return qpNew(probeThis, startIdx, 0, &isEmpty);
}



SearchResult* linearProbe(HashArray* probeThis, int startIdx, int searchFor){
    return 0;
}
SearchResult* lpForEmpty(HashArray* probeThis, int startIdx){
    SearchResult* ret = 0;

    if(probeThis){
        ret = newSearchResult(0, false, -1, 0);
        int newIdx = 0;
        for(int offset = 0; !(ret->isFound) && offset < probeThis->capacity; offset++){
            // index to check
            newIdx = (startIdx + offset) % probeThis->capacity;
            if(probeThis->contents[newIdx] == 0){ // null pointer means nothing there
                ret->foundAt = newIdx;
                ret->isFound = true;
            } else {
                ret->collisions++;
            }
        }
    }

    return ret;
}


void printHashArray(HashArray* printMe){
    if(printMe){
        printf("%s", "Contents of Hash Array:\n");
        int* ptr = 0;
        for(int i = 0; i < printMe->capacity; i++){
            ptr = printMe->contents[i];
            if(ptr){
                printf("%d: %d\n", i, *ptr);
            } else {
                printf("%d: NULL\n", i);
            }
        }
    }
}
void printSearchResult(SearchResult* printMe){
    if(printMe){
        printf("%s", "Search Result:\n");
        printf("Searched for %d.\n", printMe->searchedFor);
        if(printMe->isFound){
            printf("It was found at index %d.\n", printMe->foundAt);
        } else {
            printf("%s", "It was not found.\n");
        }
        printf("The search collided %d times.\n", printMe->collisions);
    }
}

int testHashArray(){
    HashArray* ha = 0;
    SearchResult* sr = 0;
    int ip = 0;

    do {
        printf("%s", "HASH ARRAY\n");
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the Hash Array\n");
        printf("%s", "1: Allocate a new Hash Array\n");
        printf("%s", "2: Free the Hash Array\n");
        printf("%s", "3: Insert into the Hash Array\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);
        switch(ip){
            case 0:
                printHashArray(ha);
                break;
            case 1:
                if(ha){
                    printf("%s","Cannot allocate: one already exists\n");
                } else {
                    printf("%s", "Enter capacity: ");
                    scanf("%d", &ip);
                    ha = newHashArray(ip);
                    ip = 1;
                }
                break;
            case 2:
                if(ha){
                    deleteHashArray(&ha);
                    printf("%s", "The hash array was deleted\n");
                } else {
                    printf("%s", "No hash array is allocated, so nothing is deleted\n");
                }
                break;
            case 3:
                if(ha){
                    printf("%s", "Enter value to insert: ");
                    scanf("%d", &ip);
                    sr = putInHashArray(ha, ip);
                    printSearchResult(sr);
                    deleteSearchResult(&sr);
                    ip = 3;
                } else {
                    printf("%s", "No hash array is allocated, so I cannot insert.\n");
                }
                break;
        }
    } while(ip != -1);

    deleteHashArray(&ha);
    deleteSearchResult(&sr);

    return 0;
}
