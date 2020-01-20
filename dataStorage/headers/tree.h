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

bool insertIntoTree(struct BinaryTree* root, int val);

void inOrder(struct BinaryTree* root);

int testBinaryTree();

#endif
