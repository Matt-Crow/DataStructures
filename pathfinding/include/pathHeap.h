#ifndef PATH_HEAP
#define PATH_HEAP

#include "travelInfo.h"

typedef struct PathHeap {
    int capacity;
    TravelInfo** values;
    int size;
} PathHeap;

PathHeap* newPathHeap(int capacity);
void freePathHeap(PathHeap** heap);

void siftUpPathHeap(PathHeap* heap, TravelInfo* value);
TravelInfo* siftDownPathHeap(PathHeap* heap);

void printPathHeap(PathHeap* heap);

#endif
