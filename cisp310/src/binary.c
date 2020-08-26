#include "binary.h"
#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>

int testBinary(){
    int ip1;
    int ip2;
    char* binStr1 = 0;
    char* binStr2 = 0;
    char* result = 0;

    printf("%s", "Enter a decimal integer: ");
    scanf("%d", &ip1);
    printf("%s", "Now enter another: ");
    scanf("%d", &ip2);
    printf("%d + %d = %d (in decimal)\n", ip1, ip2, ip1 + ip2);

    binStr1 = decimalIntToBase(ip1, 2);
    binStr2 = decimalIntToBase(ip2, 2);
    result = binaryAdd(binStr1, binStr2);
    printf("%s + %s = %s (in binary)\n", binStr1, binStr2, result);

    if(binStr1){
        free(binStr1);
        binStr1 = 0;
    }
    if(binStr2){
        free(binStr2);
        binStr2 = 0;
    }
    if(result){
        free(result);
        result = 0;
    }
    return 0;
}

char* binaryAdd(char* binString1, char* binString2){
    // probably create function for this later
    char* ret = (char*)malloc(sizeof(char) * (MAX_DIGITS + 1));
    memset(ret, ALPHABET[0], MAX_DIGITS);
    ret[MAX_DIGITS] = '\0';

    int sumBit = 0;
    int carryBit = 0;
    int val1;
    int val2;
    int sum;
    for(int i = MAX_DIGITS; i >= 0; i--){
        val1 = (binString1[i] == '0') ? 0 : 1;
        val2 = (binString2[i] == '0') ? 0 : 1;
        sum = val1 + val2 + carryBit;
        sumBit = sum % 2;
        carryBit = sum / 2;
        ret[i] = ALPHABET[sumBit];
    }

    if(carryBit == 1){
        printf("%s\n", "Carry bit is 1, so the sum is incorrect: not enough room!");
    }

    return ret;
}
