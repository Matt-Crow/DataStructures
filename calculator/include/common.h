#ifndef COMMON
#define COMMON

#define ERROR '#'
#define END_OF_NUMBER '|'

typedef struct StringBuilder {
    char* building;
    int size;
    int capacity;
} StringBuilder;

StringBuilder* newStringBuilder(int defaultCapacity);
void deleteStringBuilder(StringBuilder** sb);
void appendStringBuilder(StringBuilder* sb, char* value);
void appendStringBuilderChar(StringBuilder* sb, char value);
char* build(StringBuilder* sb);

int charToInt(char ch);

#endif
