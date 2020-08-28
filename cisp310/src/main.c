#include "main.h"
#include "baseConverter.h"
#include "binary.h"
#include "hexadecimal.h"
#include<stdio.h>

int main(){
    int binaryStatus = testBinary();
    printf("Binary returned %d\n", binaryStatus);
    
    int convertStatus = testBaseConverter();
    printf("Converter returned %d\n", convertStatus);

    //int hexStatus = testHex();
    //printf("Hexadecimal returned %d\n", hexStatus);
    return 0;
}
