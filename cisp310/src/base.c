#include "base.h"
#include<ctype.h>
#include<stdio.h>

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
