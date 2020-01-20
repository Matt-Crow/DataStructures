#ifndef TREE
#define TREE

#include<stdbool.h>

struct BinaryTree{
    int value;
    struct BinaryTree* left;
    struct BinaryTree* right;
};

struct BinaryTree* newBinaryTree(int val);
void deleteBinaryTree(struct BinaryTree* root);

bool insertIntoTree(struct BinaryTree** root, int val);

int getHeight(struct BinaryTree* root);
int getArraySize(struct BinaryTree* root);
void populateArray(struct BinaryTree* root, int* a, int aLen, int idx);
int* toArray(struct BinaryTree* root);
struct BinaryTree* fromSortedArrayIdx(int* a, int start, int end);
struct BinaryTree* fromSortedArray(int* a, int len);
struct BinaryTree* fromUnsoredArrayIdx(int* a, int len, int idx);
struct BinaryTree* fromUnsoredArray(int* a, int len);

void inOrder(struct BinaryTree* root);

int testBinaryTree();

#endif
