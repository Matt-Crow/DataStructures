#ifndef TREE
#define TREE

#include<stdbool.h>

/*
Binary Tree != Binary Search Tree (BT does not have ordering)

Advantages of BST:
- log(n) searching (height of tree) (but O(n) if isn't balanced)

Terms:
- Depth:  number of edges in path from root to a given node (depth of root is 0)
- Height: number of edges in path from a node to the furthest leaf node (height of a leaf is 0). Height of null is -1.
*/

// Binary Search Tree
/*
Every node in the left subtree of this node is less than it,
whereas every node in the right subtree is greater than it
*/
typedef struct BinaryTree{
    int value;
    struct BinaryTree* left; // use a list of trees for non-binary, non-search trees
    struct BinaryTree* right;
} BinaryTree;

BinaryTree* newBinaryTree(int val);
void deleteBinaryTree(BinaryTree** root);

bool isInTree(BinaryTree* root, int val);
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
