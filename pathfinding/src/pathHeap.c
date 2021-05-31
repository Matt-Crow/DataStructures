#include "pathHeap.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
Private functions
*/

void swap(PathHeap* heap, int i, int j){
    TravelInfo* temp = heap->values[i];
    heap->values[i] = heap->values[j];
    heap->values[j] = temp;
}

int getHeapWeight(PathHeap* heap, int i){
    return heap->values[i]->weight;
}



/*
Public functions
*/

PathHeap* newPathHeap(int capacity){
    PathHeap* heap = (PathHeap*)malloc(sizeof(PathHeap));
    heap->capacity = capacity;
    heap->values = (TravelInfo**)malloc(capacity * sizeof(TravelInfo*));
    memset(heap->values, 0, capacity * sizeof(TravelInfo*));
    heap->size = 0;
    return heap;
}
void freePathHeap(PathHeap** heap){
    if(heap && *heap){
        PathHeap* h = *heap;
        TravelInfo* t;
        while(h->size){
            t = siftDownPathHeap(h);
            freeTravelInfo(&t);
        }
        free(h->values);
        free(h);
        *heap = 0;
    }
}

void siftUpPathHeap(PathHeap* heap, TravelInfo* value){
    if(heap && value && heap->capacity != heap->size){
        heap->values[heap->size] = value;
        int curr = heap->size;
        int parent = (curr - 1) / 2;
        heap->size++;

        while(parent >= 0 && getHeapWeight(heap, parent) > getHeapWeight(heap, curr)){
            swap(heap, parent, curr);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
}

TravelInfo* siftDownPathHeap(PathHeap* heap){
    TravelInfo* shortest = NULL;
    if(heap && heap->size > 0){
        shortest = heap->values[0];

        // last becomes first
        --(heap->size);
        swap(heap, 0, heap->size);

        // sift down
        int curr = 0;
        int left = 2 * curr + 1;
        int right= 2 * curr + 2;
        while(
            (left < heap->size && getHeapWeight(heap, curr) > getHeapWeight(heap, left )) ||
            (right< heap->size && getHeapWeight(heap, curr) > getHeapWeight(heap, right))
        ){
            if(right < heap->size && getHeapWeight(heap, right) < getHeapWeight(heap, left)){
                swap(heap, curr, right);
                curr = right;
            } else {
                swap(heap, curr, left);
            }
            left = 2 * curr + 1;
            right= 2 * curr + 2;
        }
    }
    return shortest;
}

void printPathHeap(PathHeap* heap){
    if(heap){
        printf("%s\n", "HEAP:");
        int maxWidth = 1;
        int currWidth = 0;
        for(int i = 0; i < heap->size; ++i){
            printTravelInfo(heap->values[i]);
            ++currWidth;
            if(i == heap->size - 1){ // last item
                printf("%c", '\n');
            } else if(currWidth >= maxWidth){ // end of row
                printf("%c", '\n');
                maxWidth *= 2;
                currWidth = 0;
            } else {
                printf("%s", ", ");
            }
        }
        printf("%s\n", "END OF HEAP");
    }
}
