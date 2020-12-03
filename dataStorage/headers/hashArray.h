#ifndef HASH_ARRAY
#define HASH_ARRAY

#include<stdbool.h>



typedef struct HashArray {
    int capacity;
    int** contents; // array of values stored. Null pointer indicates nothing stored there
} HashArray;

typedef struct SearchResult {
    int searchedFor;
    bool isFound;
    int foundAt;
    int collisions;
} SearchResult;

typedef bool (*CheckIfFoundFunction)(HashArray*, int, int);

HashArray* newHashArray(int capacity);

void deleteHashArray(HashArray** deleteThis);
void deleteSearchResult(SearchResult** deleteThis);

SearchResult* putInHashArray(HashArray* intoHere, int val);
SearchResult* getFromHashArray(HashArray* fromHere, int val);

//bool isEmpty(HashArray* checkThis, int idx, int dummyParameter);
//bool containsValue(HashArray* checkThis, int idx, int value);

//SearchResult* singleHash(HashArray* probeThis, int startIdx, int searchFor, CheckIfFoundFunction checkIfFound);
//SearchResult* doubleHash(HashArray* probeThis, int startIdx, int searchFor, CheckIfFoundFunction checkIfFound);
//SearchResult* quadraticProbe(HashArray* probeThis, int startIdx, int searchFor, CheckIfFoundFunction checkIfFound);
//SearchResult* linearProbe(HashArray* probeThis, int startIdx, int searchFor, CheckIfFoundFunction checkIfFound);

void printHashArray(HashArray* printMe);
void printSearchResult(SearchResult* printMe);

int testHashArray();

#endif
