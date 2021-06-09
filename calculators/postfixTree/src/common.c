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

void deletePostfixTree(PostfixTree** root){
    if(root){
        PostfixTree* tree = *root;
        deletePostfixTree(&(tree->left));
        deletePostfixTree(&(tree->right));
        free(tree->token);
        free(tree);
        *root = 0;
    }
}

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

void clearStringBuilder(StringBuilder* sb){
    sb->building[0] = '\0';
    sb->size = 0;
}

int charToInt(char ch){
    return (int)(ch - '0');
}



/*
Private definitions
*/
