#include "common.h"
#include<stdlib.h>
#include<string.h>

/*
Private prototypes
*/

void resize(StringBuilder* sb);

/*
Public
*/

StringBuilder* newStringBuilder(int defaultCapacity){
    StringBuilder* sb = (StringBuilder*)malloc(sizeof(StringBuilder));
    sb->building = (char*)malloc(sizeof(char) * defaultCapacity);
    sb->size = 0;
    sb->capacity = defaultCapacity;
    return sb;
}
void deleteStringBuilder(StringBuilder** sb){
    if(sb && *sb){
        StringBuilder* freeMe = *sb;
        if(freeMe->building){
            free(freeMe->building);
            freeMe->building = 0;
        }
        free(freeMe);
        freeMe = 0;
    }
}
void appendStringBuilder(StringBuilder* sb, char* value){
    int numChars = strlen(value);
    while(sb->capacity < sb->size + numChars){
        resize(sb);
    }
    char* endOfString = sb->building + sb->size;
    strncpy(endOfString, value, numChars);
    sb->size += numChars;
}

void appendStringBuilderChar(StringBuilder* sb, char value){
    char temp[2] = {value, '\0'};
    appendStringBuilder(sb, temp);
}

char* build(StringBuilder* sb){
    char* str = (char*)malloc(sizeof(char) * (sb->size + 1));
    strncpy(str, sb->building, sb->size);
    str[sb->size] = '\0';
    return str;
}

/*
Private definitions
*/

void resize(StringBuilder* sb){
    int newCapacity = sb->capacity * 2;
    char* newBuilding = (char*)malloc(sizeof(char) * newCapacity);
    strncpy(newBuilding, sb->building, sb->size);
    free(sb->building);
    sb->building = newBuilding;
    sb->capacity = newCapacity;
}
