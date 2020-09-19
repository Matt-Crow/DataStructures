#include "base.h"
#include<ctype.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>

const int SYS_ARCH = 32;

int charToInt(char character, const char* alphabet, int alphabetLength){
    int ret = -1;
    character = toupper(character);
    for(int i = 0; i < alphabetLength && ret == -1; i++){
        if(character == toupper(alphabet[i])){
            ret = i;
        }
    }
    return ret;
}

char intToChar(int decimal, const char* alphabet, int alphabetLength){
    char ret = ' ';
    if(decimal < alphabetLength){
        ret = alphabet[decimal];
    }
    return ret;
}

char* newStr(int length, char defaultChar){
    char* ret = (char*)malloc(sizeof(char) * (length + 1));
    memset(ret, defaultChar, length);
    ret[length] = '\0';
    return ret;
}

int delStr(char** str){
    int wasDel = 0;
    if(str && *str){ // neither the null pointer, nor a pointer to it
        free(*str);
        *str = 0;
        wasDel = 1;
    }
    return wasDel;
}

char* parseStr(char* str, char* initializer(), int charToIdxFunc(char), char intToCharFunc(int)){
    char* ret = initializer();
    int strIdx = strlen(str) - 1; // start at last character of str
    int retIdx = strlen(ret) - 1; // and the end of ret
    int alphabetIdx = -1;
    while(strIdx >= 0 && retIdx >= 0){
        alphabetIdx = charToIdxFunc(str[strIdx]);
        if(alphabetIdx == -1){
            printf("Warning: Invalid character '%c'\n", str[strIdx]);
        } else {
            ret[retIdx] = intToCharFunc(alphabetIdx);
            retIdx--;
        }
        strIdx--;
    }
    return ret;
}

/*
Note that this does not account for negative values: binary.c accounts for that
*/
int strToInt(char* str, int base, int intVal(char)){
    int ret = 0;
    int n = 0;
    int baseToTheN = 1;
    int alphabetIdx = -1;
    int start = strlen(str) - 1;
    for(int idx = start; idx >= 0; idx--){
        alphabetIdx = intVal(str[idx]);
        if(alphabetIdx == -1){
            printf("Warning: invalid character '%c'\n", str[idx]);
        } else {
            ret += baseToTheN * alphabetIdx;
        }
        n++;
        baseToTheN *= base;
    }
    return ret;
}

/*
Note that this does not account for negative values: binary.c accounts for that
*/
char* intToStr(int value, int base, char* initializer(), char intToCharFunc(int)){
    char* ret = initializer();
    int n = 0;
    unsigned int baseToTheN = 1;
    int digits = strlen(ret);
    while(n < digits - 1){
        n++;
        baseToTheN *= base;
        //printf("%d^%d = %ud\n", base, n, baseToTheN);
    }
    //printf("Max is %ud\n", baseToTheN * base - 1); // don't try storing baseToTheN = base^digits: it doesn't work

    if(value > baseToTheN * base - 1){
        printf("Error: value excedes maximum value in base %d (%ud), so I cannot convert it\n", base, baseToTheN * base - 1);
    } else {
        int remainder = value;
        int div = 0;
        while(n >= 0){
            div = remainder / baseToTheN;
            //printf("%d %d\n", digits, n);
            //printf("%d\n", digits - n - 1);
            ret[digits - n - 1] = intToCharFunc(div);
            remainder -= div * baseToTheN;
            baseToTheN /= base;
            n--;
        }
    }
    return ret;
}
