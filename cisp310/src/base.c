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
