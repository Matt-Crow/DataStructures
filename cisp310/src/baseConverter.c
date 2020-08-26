#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>


int testBaseConverter(){
    char ip[MAX_BASE + 1];
    char* sanitized = 0;
    int from = 10;
    int to = 2;
    char* op;
    bool keepGoing = true;

    while(keepGoing){
        printf("%s", "Enter a number in base 10: "); //printf("%s", "Enter a number in base 2-16: ");
        fgets(ip, MAX_BASE + 1, stdin);
        //printf("%s", "Enter the base this number is in: ");
        //scanf("%d", &from);
        //printf("%s", "Enter the base to convert to: ");
        //scanf("%d", &to);
        sanitized = sanitize(ip);
        op = convert(sanitized, from, to);
        printf("%s in base %d is %s in base %d\n", sanitized, from, op, to);
        if(sanitized){
            free(sanitized);
            sanitized = 0;
        }
        if(op){
            free(op);
            op = 0;
        }

        keepGoing = false;
        /*
        printf("Enter yes to continue: ");
        fgets(ip, 3, stdin);
        keepGoing = strcmp(ip, "yes") == 0; // doesn't work, likely because of newline character*/
    }
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

        // currently has issues with more than 31 digits, due to integer limits
        while(ip[digits] != '\0'){
            digits++;
            basePower *= fromBase;
        }
        basePower /= fromBase; // for example, base 10 with 2 digits should have a base power of 10, not 100
        int intValue;
        for(int i = 0; ip[i] != '\0'; i++){
            intValue = intVal(ip[i]);
            //printf("Int value is %d * %d\n", intValue, basePower);
            if(intValue != -1){
                ret += basePower * intValue;
                basePower /= fromBase;
            }
        }
    }
    return ret;
}

char* decimalIntToBase(int decimalValue, int toBase){
    char* ret = 0;
    // create the number string to return, padded with 0s
    ret = (char*)malloc(sizeof(char) * (MAX_DIGITS + 1));
    memset(ret, ALPHABET[0], MAX_DIGITS);
    ret[MAX_DIGITS] = '\0';

    // calculate the digits of the new number string in the new base
    long long maxDigitValue = (long)pow(toBase, MAX_DIGITS - 1); //the largest value of a single digit of a number in base toBase
    int count; // number of maxDigitValues in decimalValue
    for(int place = 0; place < MAX_DIGITS; place++){
        if(maxDigitValue < 0){
            maxDigitValue = -maxDigitValue; // I was having issues with the sign flipping, probably due to integer overflow,
            // but that was when I had another bug, so I'm not sure if this is needed anymore
        }
        count = decimalValue / maxDigitValue; // "how many (toBase)^(MAX_DIGITS - 1 - place) are there in decimalValue?"
        ret[place] = ALPHABET[count]; // I don't think this will pose a problem, so long as nobody enters some number like 16^33
        decimalValue -= count * maxDigitValue; // there are [count] maxDigitValues in decimalValue, so this is (decimalValue / maxDigitValue) * maxDigitValue
        // which gives the whole number of maxDigitValues in decimalValue.
        maxDigitValue /= toBase; // move to the next digit of the output base number system.
    }
    return ret;
}

char* convert(char ip[], int fromBase, int toBase){
    char* ret = 0;
    // may want to move this somewhere else
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
        // first, convert the input number string to a decimal integer so we can do division and other opertations
        int intValue = calcIntValue(ip, fromBase);
        // TODO: make sure this does not excede the maximum value. (still need to calculate that)
        printf("%s in base %d is %d in base 10\n", ip, fromBase, intValue);
        ret = decimalIntToBase(intValue, toBase);
    }
    return ret;
}
