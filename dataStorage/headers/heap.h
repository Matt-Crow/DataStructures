#ifndef HEAP
#define HEAP

#include <stdbool.h>

typedef struct Heap {
    int capacity;
    int firstEmptyIdx;
    int* values;
    bool (*comparitor)(int, int);
} Heap;

Heap* newMinHeap(int capacity);
Heap* newMaxHeap(int capacity);

void deleteHeap(Heap** deleteMe);

bool siftUp(Heap* heap, int value);
bool isHeapEmpty(Heap* heap);
int siftDown(Heap* heap);

void printHeap(Heap* heap);

int testHeap();

#endif
