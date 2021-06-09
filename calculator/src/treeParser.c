#include "treeParser.h"
#include "common.h"
#include "treeCommon.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdbool.h>

/*
Private function prototypes
*/

typedef struct TreeStack {
    PostfixTree* value;
    struct TreeStack* next;
} TreeStack;

PostfixTree* newPostfixTree(char* token);

TreeStack* newTreeStack(PostfixTree* value);
void deleteTreeStack(TreeStack** top);
void pushTreeStack(TreeStack** top, PostfixTree* tree);
PostfixTree* popTreeStack(TreeStack** top);


/*
Public functions
*/
PostfixTree* toPostfixTree(char* postfix){
    PostfixTree* root = 0;
    TreeStack* stack = 0;
    StringBuilder* sb = newStringBuilder(16);

    char token;
    bool inNumber = false;

    PostfixTree* left = 0;
    PostfixTree* right = 0;
    PostfixTree* curr = 0;
    char tokenTemp[2] = {' ', '\0'};
    for(int offset = 0; offset < strlen(postfix); ++offset){
        token = postfix[offset];
        if(isdigit(token)){
            inNumber = true;
            appendStringBuilderChar(sb, token);
        } else {
            if(inNumber){
                pushTreeStack(&stack, newPostfixTree(build(sb)));
                clearStringBuilder(sb);
                inNumber = false;
            } else {
                tokenTemp[0] = token;
                right = popTreeStack(&stack);
                left = popTreeStack(&stack);
                curr = newPostfixTree(tokenTemp);
                curr->left = left;
                curr->right = right;
                pushTreeStack(&stack, curr);
            }
        }
    }

    root = popTreeStack(&stack);

    deleteStringBuilder(&sb);

    return root;
}



/*
Private function implementations
*/



PostfixTree* newPostfixTree(char* token){
    PostfixTree* tree = (PostfixTree*)malloc(sizeof(PostfixTree));
    int n = strlen(token);
    tree->token = (char*)malloc(sizeof(char) * (n + 1));
    strncpy(tree->token, token, n);
    tree->token[n] = '\0';
    tree->left = 0;
    tree->right = 0;
    return tree;
}

TreeStack* newTreeStack(PostfixTree* value){
    TreeStack* frame = (TreeStack*)malloc(sizeof(TreeStack));
    frame->value = value;
    frame->next = 0;
    return frame;
}

void deleteTreeStack(TreeStack** top){
    if(top){
        PostfixTree* tree = 0;
        while(*top){
            tree = popTreeStack(top);
            deletePostfixTree(&tree);
        }
    }
}

void pushTreeStack(TreeStack** top, PostfixTree* tree){
    if(top){
        TreeStack* newTop = newTreeStack(tree);
        newTop->next = *top;
        *top = newTop;
    }
}

PostfixTree* popTreeStack(TreeStack** top){
    PostfixTree* value = 0;
    if(top && *top){
        TreeStack* oldTop = *top;
        *top = oldTop->next;
        value = oldTop->value;
        free(oldTop);
    }
    return value;
}
