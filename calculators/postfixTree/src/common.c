#include "common.h"
#include<stdlib.h>
#include<string.h>

/*
Private prototypes
*/



/*
Public
*/

void deletePostfixTree(PostfixTree** root){
    if(root){
        PostfixTree* tree = *root;
        deletePostfixTree(&(tree->left));
        deletePostfixTree(&(tree->right));
        free(tree->token);
        free(tree);
        *root = 0;
    }
}

int charToInt(char ch){
    return (int)(ch - '0');
}



/*
Private definitions
*/
