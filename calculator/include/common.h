#ifndef COMMON
#define COMMON

#define POSTFIX_DELIMINATOR '|'

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

#endif
