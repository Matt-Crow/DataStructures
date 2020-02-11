#ifndef TREE
#define TREE

#include<stdbool.h>

typedef struct BinaryTree{
    int value;
    struct BinaryTree* left;
    struct BinaryTree* right;
} BinaryTree;

BinaryTree* newBinaryTree(int val);
void deleteBinaryTree(BinaryTree** root);

bool insertIntoTree(BinaryTree** root, int val);
bool deleteFromTree(BinaryTree** root, int val);

int getHeight(BinaryTree* root);

int getArraySize(BinaryTree* root);
void populateArray(BinaryTree* root, int* a, int aLen, int idx);
int* toArray(BinaryTree* root);

BinaryTree* fromSortedArrayIdx(int* a, int start, int end);
BinaryTree* fromSortedArray(int* a, int len);
BinaryTree* fromUnsoredArrayIdx(int* a, int len, int idx);
BinaryTree* fromUnsoredArray(int* a, int len);

void inOrder(BinaryTree* root);

int testBinaryTree();

#endif
