#include <stdio.h>
#include <stdlib.h>
#include "heap.h"

bool leftIsBigger(int a, int b){
    return a > b;
}
bool rightIsBigger(int a, int b){
    return a < b;
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
    return newHeap(capacity, leftIsBigger); // might be swapped
}
Heap* newMaxHeap(int capacity){
    return newHeap(capacity, rightIsBigger);
}

void deleteHeap(Heap** deleteMe){
    if(deleteMe && *deleteMe){
        free((*deleteMe)->values);
        free(*deleteMe);
        *deleteMe = 0;
    }
}

bool siftUp(Heap* heap, int value){
    return false;
}
bool isHeapEmpty(Heap* heap){
    return false;
}
int siftDown(Heap* heap){
    return 0;
}

void printHeap(Heap* heap){

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
