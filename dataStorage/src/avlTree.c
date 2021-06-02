#include "avlTree.h"
#include "core.h"
#include<stdio.h>
#include<stdlib.h>

/*
Private functions
*/
int getBalance(AvlTreeNode* root);
void rebalance(AvlTreeNode** root);
void leftRotate(AvlTreeNode** root);
void rightRotate(AvlTreeNode** root);



/*
Public functions
*/

AvlTreeNode* newAvlTree(int value){
    AvlTreeNode* avl = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));
    avl->value = value;
    avl->left = 0;
    avl->right = 0;
    avl->height = 0;
    return avl;
}
void deleteAvlTree(AvlTreeNode** root){
    if(root && *root){
        AvlTreeNode* node = *root;
        // delete this node post-order so children don't become inaccessable
        deleteAvlTree(&(node->left));
        deleteAvlTree(&(node->right));
        free(node);
        *root = 0;
    }
}

bool isInAvlTree(AvlTreeNode* root, int val);

bool insertIntoAvlTree(AvlTreeNode** root, int val){
    bool notDuplicate = false;
    if(root){ // not passed a null pointer
        AvlTreeNode* node = *root;
        if(!node){ // no root yet
            *root = newAvlTree(val);
            notDuplicate = true;
        } else if(node->value > val){
            notDuplicate = insertIntoAvlTree(&(node->left), val);
            // todo rebalance
        } else if(node->value < val){
            notDuplicate = insertIntoAvlTree(&(node->right), val);
            // todo rebalance
        } else { // node->value == val
            notDuplicate = false;
        }
    }
    return notDuplicate;
}

bool removeFromAvlTree(AvlTreeNode** root, int val);

int getAvlHeight(AvlTreeNode* root);

void preOrderAvl(AvlTreeNode* root){
    if(root){
        printf("%d ", root->value);
        preOrderAvl(root->left);
        preOrderAvl(root->right);
    }
}
void inOrderAvl(AvlTreeNode* root){
    if(root){
        inOrderAvl(root->left);
        printf("%d ", root->value);
        inOrderAvl(root->right);
    }
}
void postOrderAvl(AvlTreeNode* root){
    if(root){
        postOrderAvl(root->left);
        postOrderAvl(root->right);
        printf("%d ", root->value);
    }
}
void breadthPrintAvl(AvlTreeNode* root);

// Conforms to the Consumer standard defined in core.h
void askInsertAvl(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    printf("%s", "Enter value to insert: ");
    int i;
    scanf("%d", &i);
    insertIntoAvlTree(root, i);
}
void doPreOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    preOrderAvl(*root);
    printf("%c", '\n');
}
void doInOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    inOrderAvl(*root);
    printf("%c", '\n');
}
void doPostOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    postOrderAvl(*root);
    printf("%c", '\n');
}

int testAvlTree(){
    AvlTreeNode* alvin = 0;

    printf("%s\n", "AVL Tree");

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("Insert into the AVL Tree", &askInsertAvl),
        newConsumerMenuOption("Print pre-order", &doPreOrder),
        newConsumerMenuOption("Print in-order", &doInOrder),
        newConsumerMenuOption("Print post-order", &doPostOrder)
    };
    int numOptions = 4;

    doConsumerMenu(options, numOptions, (void**)&alvin);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteAvlTree(&alvin);

    return 0;
}
