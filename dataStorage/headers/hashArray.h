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



HashArray* newHashArray(int capacity);
SearchResult* newSearchResult(int searchedFor, bool isFound, int foundAt, int collisions);

void deleteHashArray(HashArray** deleteThis);
void deleteSearchResult(SearchResult** deleteThis);

SearchResult* putInHashArray(HashArray* intoHere, int val);
SearchResult* getFromHashArray(HashArray* fromHere, int val);
SearchResult* quadraticProbe(HashArray* probeThis, int startIdx, int searchFor);
SearchResult* qpForEmpty(HashArray* probeThis, int startIdx);
SearchResult* linearProbe(HashArray* probeThis, int startIdx, int searchFor);
SearchResult* lpForEmpty(HashArray* probeThis, int startIdx);
void printHashArray(HashArray* printMe);

int testHashArray();

#endif
