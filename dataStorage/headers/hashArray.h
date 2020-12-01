#ifndef HASH_ARRAY
#define HASH_ARRAY

#include<stdbool.h>



typedef struct HashArray {
    int capacity;
    int** contents; // array of pointers to the values stored
} HashArray;

typedef struct SearchResult {
    int searchedFor;
    bool isFound;
    int foundAt;
    int collisions;
} SearchResult;



HashArray* newHashArray(int capacity);
SearchResult* newSearchResult(int searchedFor, bool found, int foundAt, int collisions);

SearchResult* putInHashArray(HashArray* intoHere, int val);
SearchResult* getFromHashArray(HashArray* fromHere, int val);
SearchResult* quadraticProbe(HashArray* probeThis, int startIdx, int searchFor);
SearchResult* qpForEmpty(HashArray* probeThis, int startIdx);
SearchResult* linearProbe(HashArray* probeThis, int startIdx, int searchFor);
SearchResult* lpForEmpty(HashArray* probeThis, int startIdx);
void printHashArray(HashArray* printMe);

int testHashArray();

#endif
