#include "main.h"
#include "baseConverter.h"
#include<stdio.h>

int main(){
    int convertStatus = testBaseConverter();
    printf("Converter returned %d\n", convertStatus);
    return 0;
}
