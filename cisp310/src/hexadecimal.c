#include "base.h"
#include "hexadecimal.h"
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>

const int HEX_LEN = 8; // this doesn't work SYS_ARCH / 4; // need to calculate this based on max integer and system archetecture
// each hex char takes up 4 bits

const char HEX_ALPHABET[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
}; // 0-15 in hex

const int HEX_ALPHABET_SIZE = sizeof(HEX_ALPHABET) / sizeof(char);

int hexIdx(char c){
    return charToInt(c, HEX_ALPHABET, HEX_ALPHABET_SIZE);
}
char intToHexChar(int i){
    return intToChar(i, HEX_ALPHABET, HEX_ALPHABET_SIZE);
}

char* newHex(){
    return newStr(HEX_LEN, HEX_ALPHABET[0]);
}
int deleteHex(char** hexStr){
    return delStr(hexStr);
}

char* toHexStr(char* str){
    return parseStr(str, &newHex, &hexIdx, &intToHexChar);
}

int hexStrToInt(char* hexStr){
    return strToInt(hexStr, HEX_ALPHABET_SIZE, &hexIdx);
}




int testHex(){
    char* strs[] = {
        "abcdef00",
        "f",
        "I am not hex :("
    };

    char* hex = 0;

    for(int i = 0; i < 3; i++){
        hex = toHexStr(strs[i]);
        printf("Hex is %s\n", hex);
        deleteHex(&hex);
    }
    return 0;
}
