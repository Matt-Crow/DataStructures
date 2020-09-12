#include "baseConverter.h"
#include "hexadecimal.h"
#include "binary.h"
#include "base.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

//const int MAX_DIGITS = 32; // may change this to a parameter to functions later
//const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
//const int MAX_BASE = sizeof(ALPHABET) / sizeof(char);
const char* HEX_TO_BIN_TABLE[] = {
    "0000",
    "0001",
    "0010",
    "0011",
    "0100",
    "0101",
    "0110",
    "0111",
    "1000",
    "1001",
    "1010",
    "1011",
    "1100",
    "1101",
    "1110",
    "1111"
}; // ew. Don't like this



int testBaseConverter(){
    char ip[100];
    printf("%s", "Enter hex string: ");
    gets(ip);
    char* asHex = toHexStr(ip);
    char* asBin = hexStrToBinStr(asHex);
    printf("%s is %s is %s\n", ip, asHex, asBin);
    deleteHex(&asHex);

    asHex = binStrToHexStr(asBin);
    printf("And back to hex again: %s\n", asHex);
    deleteHex(&asHex);
    free(asBin);
    asBin = 0;



    /*
    char ip[MAX_BASE + 1];
    char* sanitized = 0;
    int from = 10;
    int to = 2;
    char* op = 0;
    bool keepGoing = true;

    while(keepGoing){
        printf("%s", "Enter a number in base 10: "); //printf("%s", "Enter a number in base 2-16: ");
        fgets(ip, MAX_BASE + 1, stdin);
        //printf("%s", "Enter the base this number is in: ");
        //scanf("%d", &from);
        printf("%s", "Enter the base to convert to: ");
        scanf("%d", &to);
        sanitized = sanitize(ip); // change this to toBinStr or toHexStr, based on what base the user chooses to convert from
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

        printf("Enter yes to continue: ");
        fgets(ip, 3, stdin);
        keepGoing = strcmp(ip, "yes") == 0; // doesn't work, likely because of newline character
    }*/
    return 0;
}

/*
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
*/

/*
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

        printf("%s | %lld | %d | %d\n", ret, maxDigitValue, count, decimalValue);
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
        int intValue = calcIntValue(ip, fromBase); // need to move this somewhere else
        // TODO: make sure this does not excede the maximum value. (still need to calculate that)
        //printf("%s in base %d is %d in base 10\n", ip, fromBase, intValue);
        ret = decimalIntToBase(intValue, toBase);
    }
    return ret;
}*/

// don't like this, but I have to, as HEX_TO_BIN_TABLE is const
const char* hexCharToBinStr(char c){
    int idx = hexIdx(c);
    if(idx == -1){
        printf("Warning: Invalid hex character '%c'\n", c);
        return 0;
    } else {
        return HEX_TO_BIN_TABLE[idx];
    }
}
char binChunkToHexChar(char* chunk){
    char ret = ' ';
    // search for chunk in the HEX_TO_BIN_TABLE
    for(int i = 0; i < HEX_ALPHABET_SIZE && ret == ' '; i++){
        if(strcmp(chunk, HEX_TO_BIN_TABLE[i]) == 0){
            ret = HEX_ALPHABET[i];
        }
    }
    return ret;
}

char* hexStrToBinStr(char* hexStr){
    char* ret = newBinStr();

    // process from right to left
    int hexStrIdx = HEX_LEN - 1;
    int binStrIdx = SYS_ARCH - 1;
    int hexI; // hex char idx
    while(hexStrIdx >= 0 && binStrIdx >= 0){
        hexI = hexIdx(hexStr[hexStrIdx]);
        if(hexI == -1){
            printf("Warning: Invalid hex char '%c'\n", hexStr[hexStrIdx]);
        } else {
            const char* copyMeOver = HEX_TO_BIN_TABLE[hexI];
            for(int i = strlen(copyMeOver) - 1; i >= 0; i--){
                ret[binStrIdx] = copyMeOver[i];
                binStrIdx--;
                printf("%s\n", ret);
            }
        }
        hexStrIdx--;
    }
    return ret;
}

char* binStrToHexStr(char* binStr){
    char* hexStr = newHex();
    char chunk[5] = {'0', '0', '0', '0', '\0'};
    int hexStrIdx = HEX_LEN - 1;
    int binStrIdx = SYS_ARCH - 1;

    while(hexStrIdx >= 0 && binStrIdx >= 0){
        // gather the chunks in reverse order.
        memset(chunk, '0', 4); // wipe the previous chunk, setting all bits to 0
        /*
        Gather up to four bits from binStr. Note that
        if binStr is formatted incorrectly as strlen(binStr) % 4 != 0,
        since we set all bits of the chunk to zero, and fill the chunk
        backwards, we'll be fine:
        binStr 01101110 will chunk as 0110 and 1110, as it can be fully chunked properly
        while   1101110 (only 7 digits) will produce it's second chunk first as 1110, but only has 3 bits left: not a whole chunk
        BUT memset sets the chunk to 0000, and each iteration will go as follows: (values are prior to iteration)
        i | binStrIdx | chunk | binStr (from 0 to binStrIdx)
        0 | 2         | 0000  | 110
        1 | 1         | 0000  | 11
        2 | 0         | 0010  | 1
        3 | -1        | 0110  | \0
        So it breaks out of the loop, but, hey look! Complete and correct chunk!
        */
        for(int i = 0; i < 4 && binStrIdx >= 0; i++){ // fill as much as possible. Missing chunk pieces will be '0'
            chunk[3 - i] = binStr[binStrIdx];
            binStrIdx--;
            //printf("Chunk is %s\n", chunk);
        }
        hexStr[hexStrIdx] = binChunkToHexChar(chunk);
        hexStrIdx--;
    }
    return hexStr;
}
