#ifndef PATH_HEAP
#define PATH_HEAP

#include "travelInfo.h"

/*
Dijkstra's algorithm requires finding the shortest path as quickly as possible,
so PathHeap is implemented as a min-heap.
*/

typedef struct PathHeap {
    int capacity;
    TravelInfo** values; // array of TravelInfo*
    int size;
} PathHeap;

PathHeap* newPathHeap(int capacity);
void freePathHeap(PathHeap** heap);

void siftUpPathHeap(PathHeap* heap, TravelInfo* value);
TravelInfo* siftDownPathHeap(PathHeap* heap);

void printPathHeap(PathHeap* heap);

#endif
