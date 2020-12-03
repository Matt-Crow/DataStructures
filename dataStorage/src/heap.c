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
    return 0;
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

int testHeap(){
    Heap* h = 0;
    int ip = 0;
    do {
        printf("%s", "HEAP\n");
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the heap\n");
        printf("%s", "1: allocate a new min heap\n");
        printf("%s", "2: allocate a new max heap\n");
        printf("%s", "3: free the heap\n");
        printf("%s", "4: sift up\n");
        printf("%s", "5: sift down\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);

        switch(ip){
            case 0:
                if(h){
                    printHeap(h);
                } else {
                    printf("%s", "No heap to print.\n");
                }
                break;
            case 1:
                if(h){
                    printf("%s", "Heap already allocated.\n");
                } else {
                    printf("Enter heap capacity: ");
                    scanf("%d", &ip);
                    h = newMinHeap(ip);
                    ip = 1;
                }
                break;
            case 2:
                if(h){
                    printf("%s", "Heap already allocated.\n");
                } else {
                    printf("Enter heap capacity: ");
                    scanf("%d", &ip);
                    h = newMaxHeap(ip);
                    ip = 2;
                }
                break;
            case 3:
                if(h){
                    deleteHeap(&h);
                    printf("%s", "The heap has been deleted\n");
                } else {
                    printf("%s", "No heap to delete\n");
                }
                break;
            case 4:
                if(h){
                    printf("%s", "Enter value to sift up: ");
                    scanf("%d", &ip);
                    siftUp(h, ip);
                    ip = 4;
                } else {
                    printf("%s", "No heap has been allocated.\n");
                }
                break;
            case 5:
                if(h){
                    if(isHeapEmpty(h)){
                        printf("%s", "Nothing to sift down.\n");
                    } else {
                        ip = siftDown(h);
                        printf("Sifted down %d\n", ip);
                        ip = 5;
                    }
                } else {
                    printf("%s", "No heap has been allocated.\n");
                }
                break;
        }
    } while(ip != -1);

    deleteHeap(&h);

    return 0;
}
