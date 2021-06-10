#include "util.h"
#include<stdio.h>

void printArray(int a[], int length){
    printf("%c", '[');
    for(int i = 0; i < length; ++i){
        if(i == length - 1){ // last element
            printf("%d", a[i]);
        } else {
            printf("%d, ", a[i]);
        }
    }
    printf("%s", "]\n");
}
