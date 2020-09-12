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
    char* ret = (char*)malloc(sizeof(char) * (HEX_LEN + 1));
    memset(ret, HEX_ALPHABET[0], HEX_LEN);
    ret[HEX_LEN] = '\0';
    return ret;
}
char* toHexStr(char* str){
    char* ret = newHex();
    int rawStrLen = strlen(str);
    //printf("%s is %d long\n", str, rawStrLen);
    int rawStrIdx = rawStrLen - 1; // start at the end of the old string
    int retStrIdx = HEX_LEN - 1; // and at the back of the new string
    int hexI;
    while(rawStrIdx >= 0 && retStrIdx >= 0){
        hexI = hexIdx(str[rawStrIdx]);
        if(hexI == -1){
            printf("Warning: Invalid hex character '%c'\n", str[rawStrIdx]);
        } else {
            ret[retStrIdx] = HEX_ALPHABET[hexI];
            retStrIdx--;
        }
        rawStrIdx--;
    }
    return ret;
}
int deleteHex(char** hexStr){
    int ret = hexStr && *hexStr; // wasn't passed the null pointer, nor a pointer to it
    if(ret){
        free(*hexStr);
        *hexStr = 0;
    }
    return ret;
}

int hexStrToInt(char* hexStr){
    int ret = 0;
    int basePower = 1; // starts at 16^0
    int intVal = -1;
    for(int idx = HEX_LEN - 1; idx >= 0; idx--){
        intVal = hexIdx(hexStr[idx]);
        if(intVal == -1){
            printf("Invalid hexadecimal string character: '%c'\n", hexStr[idx]);
        } else {
            ret += basePower * intVal;
        }
        basePower *= 16; // increase power by 1 as we move to the left by 1 bit
    }
    return ret;
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
