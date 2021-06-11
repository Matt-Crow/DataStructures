#include "util.h"
#include<stdio.h>

void printArray(int a[], int length){
    printf("%c", '[');
    for(int i = 0; i < length; ++i){
        if(i % 10 == 0){ // only 10 elements per line to make it easier to read
            printf("%s", "\n\t");
        }
        if(i == length - 1){ // last element
            printf("%d\n", a[i]);
        } else {
            printf("%d, ", a[i]);
        }
    }
    printf("%s", "]\n");
}
