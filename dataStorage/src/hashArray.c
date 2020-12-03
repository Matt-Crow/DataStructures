#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashArray.h"

bool isPrime(int num){
    bool ret = true;
    ret = !(num%2 == 0); //get rid of evens
    //doesn't enter loop with 1, but defaults to true
    for(int i = 3; ret && i < num; i+=2){
        ret = !(num%i == 0);
    }
    return ret;
}

int prevPrime(int num){
    int ret = num - 1;
    while(ret > 1 && !isPrime(ret)){
        ret--;
    }
    return ret;
}

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

// private to this file
SearchResult* newSearchResult(int searchedFor){
    SearchResult* ret = (SearchResult*)malloc(sizeof(SearchResult));
    ret->searchedFor = searchedFor;
    ret->isFound = false;
    ret->foundAt = -1;
    ret->collisions = 0;
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

bool isEmpty(HashArray* checkThis, int idx, int dummyParameter){
    return checkThis && !(checkThis->contents[idx]);
}
bool containsValue(HashArray* checkThis, int idx, int value){
    return checkThis && checkThis->contents[idx] && *(checkThis->contents[idx]) == value;
}

void singleHash(HashArray* probeThis, SearchResult* previousResult, CheckIfFoundFunction checkIfFound){
    int searchFor = previousResult->searchedFor;
    if(probeThis){
        int newIdx = searchFor % probeThis->capacity;
        if(checkIfFound(probeThis, newIdx, searchFor)){
            previousResult->foundAt = newIdx;
            previousResult->isFound = true;
        } else {
            previousResult->collisions++;
        }
    }
}

void doubleHash(HashArray* probeThis, SearchResult* previousResult, CheckIfFoundFunction checkIfFound){
    if(probeThis){
        int searchFor = previousResult->searchedFor;
        int p = prevPrime(probeThis->capacity);
        int newIdx = p - searchFor % p;
        if(checkIfFound(probeThis, newIdx, searchFor)){
            previousResult->foundAt = newIdx;
            previousResult->isFound = true;
        } else {
            previousResult->collisions++;
        }
    }
}

void quadraticProbe(HashArray* probeThis, SearchResult* previousResult, CheckIfFoundFunction checkIfFound){
    if(probeThis){
        int searchFor = previousResult->searchedFor;
        int startIdx = searchFor % probeThis->capacity;
        int newIdx = 0;
        for(int offset = 1; !(previousResult->isFound) && offset <= 3; offset++){
            // index to check
            newIdx = (startIdx + offset * offset) % probeThis->capacity;
            if(checkIfFound(probeThis, newIdx, searchFor)){
                previousResult->foundAt = newIdx;
                previousResult->isFound = true;
            } else {
                previousResult->collisions++;
            }
        }
    }
}

void linearProbe(HashArray* probeThis, SearchResult* previousResult, CheckIfFoundFunction checkIfFound){
    if(probeThis){
        int searchFor = previousResult->searchedFor;
        int startIdx = searchFor % probeThis->capacity;
        int newIdx = 0;
        for(int offset = 0; !(previousResult->isFound) && offset < probeThis->capacity; offset++){
            // index to check
            newIdx = (startIdx + offset) % probeThis->capacity;
            if(checkIfFound(probeThis, newIdx, searchFor)){
                previousResult->foundAt = newIdx;
                previousResult->isFound = true;
            } else {
                previousResult->collisions++;
            }
        }
    }
}

SearchResult* hashingImpl(HashArray* forThis, int valueToHash, CheckIfFoundFunction checker){
    SearchResult* result = 0;
    if(forThis){
        result = newSearchResult(valueToHash);
        int numSearchStrategies = 4;
        void (*searchStrategies[])(HashArray*, SearchResult*, CheckIfFoundFunction) = {&singleHash, &doubleHash, &linearProbe, &quadraticProbe};
        for(int i = 0; i < numSearchStrategies && !result->isFound; i++){
            searchStrategies[i](forThis, result, &isEmpty);
        }
    }
    return result;
}

SearchResult* putInHashArray(HashArray* intoHere, int val){
    SearchResult* whereItWasInserted = hashingImpl(intoHere, val, &isEmpty);
    if(whereItWasInserted && whereItWasInserted->isFound){
        intoHere->contents[whereItWasInserted->foundAt] = (int*)malloc(sizeof(int));
        *(intoHere->contents[whereItWasInserted->foundAt]) = val;
    }
    return whereItWasInserted;
}
SearchResult* getFromHashArray(HashArray* fromHere, int val){
    SearchResult* whereItWasFound = hashingImpl(fromHere, val, &containsValue);
    return whereItWasFound;
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
        printf("%s", "4: Search for a value in the Hash Array\n");
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
            case 4:
                if(ha){
                    printf("%s", "Enter value to search for: ");
                    scanf("%d", &ip);
                    sr = getFromHashArray(ha, ip);
                    printSearchResult(sr);
                    deleteSearchResult(&sr);
                    ip = 4;
                } else {
                    printf("%s", "No hash array is allocated, so I cannot search.\n");
                }
                break;
        }
    } while(ip != -1);

    deleteHashArray(&ha);
    deleteSearchResult(&sr);

    return 0;
}
