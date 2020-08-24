#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int MAX_DIGITS = 32; // may change this to a parameter to functions later
const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const int MAX_BASE = sizeof(ALPHABET) / sizeof(char);

int testBaseConverter(){
    printf("%s", "Testing base converter...");
    free(convert("0000000000000000000000000000010", 2, 10));
    return 0;
}

int intVal(char c){
    int ret = -1;
    for(int i = 0; i < MAX_BASE && ret == -1; i++){
        if(ALPHABET[i] == c){
            ret = i;
        }
    }
    return ret;
}

int calcIntValue(char ip[], int fromBase){
    int ret = -1;
    if(fromBase <= 1 || fromBase > MAX_BASE){
        printf("Invalid base: %d\n", fromBase);
    } else {
        ret = 0;
        // find the number of digits in the given input
        int digits = 0;
        unsigned int basePower = 1;

        //TODO need to account for spaces in the number
        // probably want a sanitizer
        // currently has issues with more than 31 digits, due to integer limits
        while(ip[digits] != '\0'){
            digits++;
            basePower *= fromBase;
        }
        basePower /= fromBase; // for example, base 10 with 2 digits should have a base power of 10, not 100
        int intValue;
        for(int i = 0; ip[i] != '\0'; i++){
            intValue = intVal(ip[i]);
            printf("Int value is %d * %d\n", intValue, basePower);
            if(intValue != -1){
                ret += basePower * intValue;
                basePower /= fromBase;
            }
        }
    }
    return ret;
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
        int intValue = calcIntValue(ip, fromBase);
        printf("%s in base %d is %d in base 10\n", ip, fromBase, intValue);
    }
    //printf("ret is %s", ret);
    return ret;
}
