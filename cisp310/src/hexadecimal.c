#include "hexadecimal.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

const int HEX_LEN = 8; // need to calculate this based on max integer and system archetecture
const char HEX_ALPHABET[] = {
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'a', 'b',
    'c', 'd', 'e', 'f'
}; // 0-15 in hex

char* newHex(){
    char* ret = (char*)malloc(sizeof(char) * (HEX_LEN + 1));
    memset(ret, HEX_ALPHABET[0], HEX_LEN);
    ret[HEX_LEN] = '\0';
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

int testHex(){
    char* hex = newHex();
    printf("Hex is %s\n", hex);
    deleteHex(&hex);
    printf("Is hex null? %s\n", (hex) ? "No." : "Yes.");
    return 0;
}
