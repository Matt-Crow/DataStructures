#ifndef COMMON
#define COMMON

typedef struct PostfixTree {
    char* token; // string
    struct PostfixTree* left;
    struct PostfixTree* right;
} PostfixTree;

void deletePostfixTree(PostfixTree** root);

int charToInt(char ch);

#endif
