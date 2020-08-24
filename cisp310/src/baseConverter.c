#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

const int MAX_DIGITS = 32; // may change this to a parameter to functions later
const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
const int MAX_BASE = sizeof(ALPHABET) / sizeof(char);

int testBaseConverter(){
    char ip[MAX_BASE + 1];
    char* sanitized = 0;
    int from;
    int to;
    char* op;
    bool keepGoing = true;

    while(keepGoing){
        printf("%s", "Enter a number in base 2-16: ");
        fgets(ip, MAX_BASE + 1, stdin);
        printf("%s", "Enter the base this number is in: ");
        scanf("%d", &from);
        printf("%s", "Enter the base to convert to: ");
        scanf("%d", &to);
        sanitized = sanitize(ip);
        op = convert(sanitized, from, to);
        printf("%s in base %d is %s in base %d", sanitized, from, op, to);
        if(sanitized){
            free(sanitized);
            sanitized = 0;
        }
        free(op);
        op = 0;
        printf("Enter yes to continue: ");
        fgets(ip, 3, stdin);
        keepGoing = strcmp(ip, "yes") == 0;
    }
    /*
    printf("%s", "Testing base converter...");
    free(convert("11111111", 2, 10));
    free(convert("00001111", 2, 10));
    free(convert("00000000", 2, 10));*/
    return 0;
}

char* sanitize(char* src){
    int validChars = 0;
    // count valid chars
    for(int i = 0; src[i] != '\0'; i++){
        if(intVal(src[i]) != -1){
            validChars++;
        }
    }

    char* ret = (char*)malloc(sizeof(char) * (validChars + 1));
    // copy valid chars over
    int newStrIdx = 0;
    for(int oldStrIdx = 0; src[oldStrIdx] != '\0'; oldStrIdx++){
        if(intVal(src[oldStrIdx]) != -1){
            ret[newStrIdx] = src[oldStrIdx];
            newStrIdx++;
        }
    }
    ret[validChars] = '\0';
    return ret;
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
        long maxDigitValue = (long)pow(fromBase, MAX_DIGITS - 1); //the largest value of a single digit of a number in base fromBase
        printf("%d^(%d-1) = %ld\n", fromBase, MAX_DIGITS, maxDigitValue);
        for(int place = 0; place < MAX_DIGITS; place++){
            ret[place] = ALPHABET[intValue / maxDigitValue];
            intValue -= (intValue / maxDigitValue) * maxDigitValue;
            maxDigitValue /= fromBase;
        }
    }
    printf("ret is %s\n", ret);
    return ret;
}
