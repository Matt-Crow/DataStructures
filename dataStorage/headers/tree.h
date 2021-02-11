#ifndef TREE
#define TREE

#include<stdbool.h>

/*
Advantages:
- log(n) searching

Terms:
- Depth:  number of edges in path from root to a given node (depth of root is 0)
- Height: number of edges in path from a node to the furthest leaf node (height of a leaf is 0). Height of null is -1.
*/

typedef struct BinaryTree{
    int value;
    struct BinaryTree* left; // use a list of trees for non-binary trees
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
void preOrder(BinaryTree* root);
void postOrder(BinaryTree* root);

int testBinaryTree();

#endif
