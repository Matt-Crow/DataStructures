#include "base.h"
#include "binary.h"
#include "baseConverter.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const char BIN_ALPHABET[] = {'0', '1'};
const int BIN_ALPHABET_SIZE = sizeof(BIN_ALPHABET) / sizeof(char);

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
    printf("%d - %d = %d (in decimal)\n", ip1, ip2, ip1 - ip2);

    binStr1 = intToBinStr(ip1);
    binStr2 = intToBinStr(ip2);
    result = binarySub(binStr1, binStr2);
    printf("   %s\n - %s\n = %s (in binary)\n", binStr1, binStr2, result);

    char* negated = negate(binStr1);
    printf("-%s = %s\n", binStr1, negated);
    char* sum = binaryAdd(binStr1, negated);
    printf("%s + %s = %s\n", binStr1, negated, sum);

    deleteBinStr(&binStr1);
    deleteBinStr(&binStr2);
    deleteBinStr(&result);
    deleteBinStr(&sum);
    deleteBinStr(&negated);

    return 0;
}

int binCharToInt(char binChar){
    return charToInt(binChar, BIN_ALPHABET, BIN_ALPHABET_SIZE);
}
char intToBinChar(int i){
    return intToChar(i, BIN_ALPHABET, BIN_ALPHABET_SIZE);
}

char* newBinStr(){
    return newStr(SYS_ARCH, BIN_ALPHABET[0]);
}
int deleteBinStr(char** binStr){
    return delStr(binStr);
}

// how to account for negative?
// this just checks the first character
char* toBinStr(char* cString){
    char* ret;
    int isNegative = cString[0] == '-';
    if(isNegative){
        char* temp = parseStr(cString, &newBinStr, &binCharToInt, &intToBinChar);
        ret = negate(temp);
        deleteBinStr(&temp);
    } else {
        ret = parseStr(cString, &newBinStr, &binCharToInt, &intToBinChar);
    }

    return ret;
}


// need some way of seeing if the user wants this signed vs unsigned
int binStrToInt(char* binStr){
    return strToInt(binStr, BIN_ALPHABET_SIZE, &binCharToInt);
}


char* intToBinStr(int val){
    char* ret;
    if(val < 0){
        char* temp = intToStr(-val, BIN_ALPHABET_SIZE, &newBinStr, &intToBinChar);
        ret = negate(temp);
        deleteBinStr(&temp);
    } else {
        ret = intToStr(val, BIN_ALPHABET_SIZE, &newBinStr, &intToBinChar);
    }
    return ret;
}

char* negate(char* binString){
    char* temp = newBinStr();
    char* one = intToBinStr(1);
    char* ret = 0;
    //printf("Negating %s...\n", binString);
    for(int i = 0; i < SYS_ARCH; i++){
        //flip all the bits
        temp[i] = (binString[i] == '0') ? '1' : '0';
        //printf("%c Temp is now %s\n", binString[i], temp);
    }
    // add 1
    ret = binaryAdd(temp, one);

    // free temporary variables
    deleteBinStr(&temp);
    deleteBinStr(&one);

    return ret;
}

char* binaryAdd(char* binString1, char* binString2){
    char* ret = newBinStr();

    int sumBit = 0;
    int carryBit = 0;
    int val1;
    int val2;
    int sum;
    for(int i = SYS_ARCH - 1; i >= 0; i--){
        val1 = (binString1[i] == '0') ? 0 : 1;
        val2 = (binString2[i] == '0') ? 0 : 1;
        sum = val1 + val2 + carryBit;
        sumBit = sum % 2;
        carryBit = sum / 2;
        printf("%c + %c + %d = sum %d, carry %d\n", binString1[i], binString2[i], carryBit, sumBit, carryBit);
        ret[i] = BIN_ALPHABET[sumBit];
    }

    if(carryBit == 1){
        printf("%s\n", "Carry bit is 1, so the sum is incorrect: not enough room!");
    }

    return ret;
}

char* binarySub(char* binString1, char* binString2){
    char* temp = negate(binString2);
    char* ret = binaryAdd(binString1, temp);
    deleteBinStr(&temp);
    return ret;
}
