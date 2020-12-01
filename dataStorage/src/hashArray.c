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
        free((*deleteThis)->contents); // TODO: free int*'s
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
        whereItWasInserted = qpForEmpty(intoHere, 0);
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
SearchResult* quadraticProbe(HashArray* probeThis, int startIdx, int searchFor){
    return 0;
}
SearchResult* qpForEmpty(HashArray* probeThis, int startIdx){
    SearchResult* ret = 0;

    if(probeThis){
        ret = newSearchResult(0, false, -1, 0);
        int newIdx = 0;
        for(int offset = 1; !(ret->isFound) && offset <= 3; offset++){
            // index to check
            newIdx = (startIdx + offset * offset) % probeThis->capacity;
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
SearchResult* linearProbe(HashArray* probeThis, int startIdx, int searchFor){
    return 0;
}
SearchResult* lpForEmpty(HashArray* probeThis, int startIdx){
    return 0;
}
void printHashArray(HashArray* printMe){

}

int testHashArray(){
    HashArray* ha = 0;
    int ip = 0;

    do {
        printf("%s", "HASH ARRAY\n");
        printf("%s", "Choose an option:\n");
        printf("%s", "1: Allocate a new Hash Array\n");
        printf("%s", "2: Free the Hash Array\n");
        printf("%s", "3: Insert into the Hash Array\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);
        switch(ip){
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
                    putInHashArray(ha, ip);
                    ip = 3;
                } else {
                    printf("%s", "No hash array is allocated, so I cannot insert.\n");
                }
                break;
        }
    } while(ip != -1);

    deleteHashArray(&ha);

    return 0;
}
