#ifndef COMMON
#define COMMON

typedef struct PostfixTree {
    char* token; // string
    struct PostfixTree* left;
    struct PostfixTree* right;
} PostfixTree;

void deletePostfixTree(PostfixTree** root);

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
void clearStringBuilder(StringBuilder* sb);

int charToInt(char ch);

#endif
