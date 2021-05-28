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

int getWeight(PathHeap* heap, int i){
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

        while(parent >= 0 && getWeight(heap, parent) > getWeight(heap, curr)){
            swap(heap, parent, curr);
            curr = parent;
            parent = (curr - 1) / 2;
        }
    }
}

//TODO siftDownPathHeap
TravelInfo* siftDownPathHeap(PathHeap* heap);

//TODO printPathHeap
void printPathHeap(PathHeap* heap);
