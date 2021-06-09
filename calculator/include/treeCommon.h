#ifndef TREE_COMMON
#define TREE_COMMON

typedef struct PostfixTree {
    char* token; // string
    struct PostfixTree* left;
    struct PostfixTree* right;
} PostfixTree;

void printPostfixTree(PostfixTree* root);
void deletePostfixTree(PostfixTree** root);

#endif
