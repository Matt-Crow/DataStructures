#include "core.h"
#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

bool parentIsBigger(int parent, int child){
    return parent > child;
}
bool childIsBigger(int parent, int child){
    return parent < child;
}
Heap* newHeap(int capacity, bool (*comparitor)(int, int)){
    Heap* ret = (Heap*)malloc(sizeof(Heap));
    ret->capacity = capacity;
    ret->firstEmptyIdx = 0;
    ret->values = (int*)malloc(sizeof(int) * capacity);
    ret->comparitor = comparitor;
    return ret;
}
Heap* newMinHeap(int capacity){
    //                       should swap child if parent is bigger
    return newHeap(capacity, parentIsBigger); // might be swapped
}
Heap* newMaxHeap(int capacity){
    return newHeap(capacity, childIsBigger);
}

void deleteHeap(Heap** deleteMe){
    if(deleteMe && *deleteMe){
        free((*deleteMe)->values);
        free(*deleteMe);
        *deleteMe = 0;
    }
}

bool siftUp(Heap* heap, int value){
    bool canSiftUp = heap->firstEmptyIdx < heap->capacity;
    if(canSiftUp){
        // start by putting the new value at the end of the heap
        heap->values[heap->firstEmptyIdx] = value;
        (heap->firstEmptyIdx)++;

        // identify indeces
        int childIdx = heap->firstEmptyIdx - 1; // since I incremented
        int parentIdx = (childIdx - 1) / 2;
        int temp;
        // swap until the child is in place
        while(parentIdx >= 0 && childIdx != 0 && heap->comparitor(heap->values[parentIdx], heap->values[childIdx])){
            temp = heap->values[childIdx];
            heap->values[childIdx] = heap->values[parentIdx];
            heap->values[parentIdx] = temp;
            temp = 0;
            childIdx = parentIdx;
            parentIdx = (childIdx - 1) / 2;
        }
    }
    return canSiftUp;
}
bool isHeapEmpty(Heap* heap){
    return heap->firstEmptyIdx == 0;
}
int siftDown(Heap* heap){
    int ret = 0;
    if(!isHeapEmpty(heap)){
        ret = heap->values[0]; // return the topmost element
        (heap->firstEmptyIdx)--;
        heap->values[0] = heap->values[heap->firstEmptyIdx]; // overwrite first element with the last
        // a heap is tree-like, so I access children like so
        int parentIdx = 0;
        int leftIdx = 2 * parentIdx + 1;
        int rightIdx = 2 * parentIdx + 2;
        int temp = 0;
        // swap until the parent is in the proper place
        while(
            (leftIdx < heap->firstEmptyIdx && heap->comparitor(heap->values[parentIdx], heap->values[leftIdx]))
         || (rightIdx < heap->firstEmptyIdx && heap->comparitor(heap->values[parentIdx], heap->values[rightIdx]))
        ){
            // now know at least one of them should swap
            // these might be reversed
            if(heap->comparitor(heap->values[rightIdx], heap->values[leftIdx])){
                // parent should swap with left
                temp = heap->values[leftIdx];
                heap->values[leftIdx] = heap->values[parentIdx];
                heap->values[parentIdx] = temp;
                parentIdx = leftIdx;
                temp = 0;
            } else {
                // swap with right
                temp = heap->values[rightIdx];
                heap->values[rightIdx] = heap->values[parentIdx];
                heap->values[parentIdx] = temp;
                parentIdx = rightIdx;
                temp = 0;
            }
            leftIdx = 2 * parentIdx + 1;
            rightIdx = 2 * parentIdx + 2;
        }
    }
    return ret;
}

void printHeap(Heap* heap){
    int row = 0;
    int col = 0;
    int rowWidth = 1;
    printf("%s", "Heap:\n");
    for(int i = 0; i < heap->firstEmptyIdx; i++){
        printf("%d ", heap->values[i]);
        col++;
        if(col >= rowWidth){
            // next row
            printf("%s", "\n");
            rowWidth *= 2;
            col = 0;
            row++;
        }
    }
}

void doPrintHeap(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(*h){
        printHeap(*h);
    } else {
        printf("%s", "No heap to print.\n");
    }
}

void doAllocateMinHeap(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(*h){
        printf("%s", "Heap already allocated.\n");
    } else {
        int ip;
        printf("Enter heap capacity: ");
        scanf("%d", &ip);
        *h = newMinHeap(ip);
    }
}

void doAllocateMaxHeap(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(*h){
        printf("%s", "Heap already allocated.\n");
    } else {
        int ip;
        printf("Enter heap capacity: ");
        scanf("%d", &ip);
        *h = newMaxHeap(ip);
    }
}

void doFreeHeap(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(*h){
        deleteHeap(h);
        printf("%s", "The heap has been deleted\n");
    } else {
        printf("%s", "No heap to delete\n");
    }
}

void doSiftUp(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(*h){
        int ip;
        printf("%s", "Enter value to sift up: ");
        scanf("%d", &ip);
        siftUp(*h, ip);
    } else {
        printf("%s", "No heap has been allocated.\n");
    }
}

void doSiftDown(void** dataStructure){
    Heap** h = (Heap**)dataStructure;
    if(!(*h)){
        printf("%s", "No heap has been allocated.\n");
    } else if(isHeapEmpty(*h)){
        printf("%s", "Nothing to sift down.\n");
    } else {
        int ip = siftDown(*h);
        printf("Sifted down %d\n", ip);
    }
}

int testHeap(){
    Heap* h = 0;

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("Print the heap", &doPrintHeap),
        newConsumerMenuOption("Allocate a new min heap", &doAllocateMinHeap),
        newConsumerMenuOption("Allocate a new max heap", &doAllocateMaxHeap),
        newConsumerMenuOption("Free the heap", &doFreeHeap),
        newConsumerMenuOption("Sift up", &doSiftUp),
        newConsumerMenuOption("Sift down", &doSiftDown)
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    doConsumerMenu(options, numOptions, (void**)&h);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteHeap(&h);

    return 0;
}
