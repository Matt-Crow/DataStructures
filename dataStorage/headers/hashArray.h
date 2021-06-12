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

/*
The capacity of the hash array MUST BE A PRIME NUMBER for most hashing 
techniques to work. This prevents techniques such as double hashing from 
cycling between a finite series of values when trying to find an open address.
For example, given H(x, i) = (h(x) + i*g(x)) % 10, suppose h(n) = 0 and g(n) = 5.
If the indeces 0 and 5 are already occupied, n cannot be inserted into the table,
as the range for H(n, i) = {0, 5}. Choosing H(x, i) = (h(x) + i*g(x)) % 11 resolves
this issue, as H(n, i) would then output the series (0, 5, 10, 4, 9, 3, ...)
*/
HashArray* newHashArray(int capacity);

void deleteHashArray(HashArray** deleteThis);
void deleteSearchResult(SearchResult** deleteThis);

SearchResult* putInHashArray(HashArray* intoHere, int val);
SearchResult* getFromHashArray(HashArray* fromHere, int val);

void printHashArray(HashArray* printMe);
void printSearchResult(SearchResult* printMe);

int testHashArray();

#endif
