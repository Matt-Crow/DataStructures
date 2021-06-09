#include "treeCommon.h"
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

/*
Private prototypes
*/


/*
Public
*/

void printPostfixTree(PostfixTree* root){
    if(root){
        printf("%c", '(');
        printPostfixTree(root->left);
        printf(" %s ", root->token);
        printPostfixTree(root->right);
        printf("%c", ')');
    }
}

void deletePostfixTree(PostfixTree** root){
    if(root && *root){
        PostfixTree* tree = *root;
        deletePostfixTree(&(tree->left));
        deletePostfixTree(&(tree->right));
        free(tree->token);
        free(tree);
        *root = 0;
    }
}



/*
Private definitions
*/
