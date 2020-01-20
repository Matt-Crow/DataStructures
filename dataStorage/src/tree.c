#include<stdio.h>
#include<stdlib.h>
#include "tree.h"

struct BinaryTree* newBinaryTree(int val){
    struct BinaryTree* ret = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    ret->value = val;
    ret->left = 0;
    ret->right = 0;
    return ret;
}

void deleteBinaryTree(struct BinaryTree* root){
    if(root){
        deleteBinaryTree(root->left);
        deleteBinaryTree(root->right);
        printf("deleted %i\n", root->value);
        delete root;
        root = 0;
    }
}

bool insertIntoTree(struct BinaryTree* root, int val){
    bool inserted = false;
    if(root){
        if(root->value > val){
            if(root->left){
                inserted = insertIntoTree(root->left, val);
            } else {
                root->left = newBinaryTree(val);
                inserted = true;
            }
        } else if(root->value < val){
            if(root->right){
                inserted = insertIntoTree(root->right, val);
            } else {
                root->right = newBinaryTree(val);
                inserted = true;
            }
        } else {
            //value already in tree, do not insert
        }
    } else {
        *root = *(newBinaryTree(val));
        inserted = true;
    }
    return inserted;
}

void inOrder(struct BinaryTree* root){
    if(root){
        //inOrder(root->left);
        printf("%i ", root->value);
        //inOrder(root->right);
    }
}

int testBinaryTree(){
    struct BinaryTree* root = 0;
    int ip = 0;
    bool success;

    do {
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the binary tree in order\n");
        printf("%s", "1: Insert into the binary tree\n");
        printf("%s", "2: Delete the binary tree\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);

        switch(ip){
            case 0:
                inOrder(root);
                break;
            case 1:
                printf("%s", "enter a value to insert: ");
                scanf("%d", &ip);
                success = insertIntoTree(root, ip);
                if(success){
                    printf("%i %s", ip, "was inserted\n");
                } else {
                    printf("%i %s", ip, "is already in the tree\n");
                }
                ip = 1;
                break;
            case 2:
                deleteBinaryTree(root);
                break;
        }
    } while(ip != -1);

    if(root){
        deleteBinaryTree(root);
        root = 0;
    }

    return 0;
}
