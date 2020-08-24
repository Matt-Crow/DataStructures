#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX_DIGITS = 32; // may change this to a parameter to functions later
const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const int MAX_BASE = sizeof(ALPHABET) / sizeof(char);

int testBaseConverter(){
    printf("%s", "Testing base converter...");
    for(int i = -1; i < 20; i++){
        for(int j = -1; j < 20; j++){
            free(convert(0, i, j));
        }
    }
    return 0;
}

char* convert(char ip[], int fromBase, int toBase){
    char* ret = (char*)malloc(sizeof(char) * (MAX_DIGITS + 1));
    memset(ret, ALPHABET[0], MAX_DIGITS);
    ret[MAX_DIGITS] = '\0';

    if(fromBase <= 1){
        printf("Provided fromBase %d is too low: must be greater than 1\n", fromBase);
    } else if(fromBase > MAX_BASE){
        printf("Provided fromBase %d is to high: must be at most %d\n", fromBase, MAX_BASE);
    } else if(toBase <= 1){
        printf("Provided toBase %d is too low: must be greater than 1\n", toBase);
    } else if(toBase > MAX_BASE){
        printf("Provided toBase %d is to high: must be at most %d\n", toBase, MAX_BASE);
    } else {
        // yay, finally some valid input!
        printf("I can convert from base %d to base %d\n", fromBase, toBase);
    }
    //printf("ret is %s", ret);
    return ret;
}
