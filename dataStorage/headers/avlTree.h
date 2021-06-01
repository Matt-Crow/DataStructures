#ifndef AVL_TREE
#define AVL_TREE

#include<stdbool.h>

typedef struct AvlTreeNode {
    int value;
    struct AvlTreeNode* left;
    struct AvlTreeNode* right;
    int height;
} AvlTreeNode;

AvlTreeNode* newAvlTree(int val);

/*
Recursively deletes the entire Avl Tree
*/
void deleteAvlTree(AvlTreeNode** root);

bool isInAvlTree(AvlTreeNode* root, int val);
bool insertIntoAvlTree(AvlTreeNode** root, int val);
bool removeFromAvlTree(AvlTreeNode** root, int val);

int getAvlHeight(AvlTreeNode* root);

void preOrderAvl(AvlTreeNode* root);
void inOrderAvl(AvlTreeNode* root);
void postOrderAvl(AvlTreeNode* root);
void breadthPrintAvl(AvlTreeNode* root);

int testAvlTree();

#endif
