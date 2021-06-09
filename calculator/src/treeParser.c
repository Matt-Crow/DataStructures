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
PostfixTree* toPostfixTree(char* infix){
    PostfixTree* root = 0;
    TreeStack* stack = 0;
    StringBuilder* sb = newStringBuilder(16);

    char token;
    bool inNumber = false;
    for(int offset = 0; offset < strlen(infix); ++offset){
        token = infix[offset];
        if(isdigit(token)){
            inNumber = true;
            appendStringBuilderChar(sb, token);
        } else {
            if(inNumber){
                pushTreeStack(&stack, newPostfixTree(build(sb)));
                clearStringBuilder(sb);
                inNumber = false;
            } else {

            }
            if(token == '('){
                push(&ops, token);
            } else if(token == ')'){
                // pop until it finds the matching '('
                while(token != '('){
                    token = popOperatorStack(&ops);
                    if(token != '('){
                        appendStringBuilderChar(sb, token);
                    }
                }
            }
            //if the token is an operator, pop until the top is LESS precedence than the token,
            //then push to token.
            else if(token == '+' || token == '-'){
                while(ops && ops->operator != '('){
                    appendStringBuilderChar(sb, popOperatorStack(&ops));
                }
                push(&ops, token);
            } else if(token == '*' || token == '/'){
                while(
                    ops &&
                    ops->operator != '(' &&
                    ops->operator != '+' &&
                    ops->operator != '-'
                ){
                    appendStringBuilderChar(sb, popOperatorStack(&ops));
                }
                push(&ops, token);
            } else if(token == ' '){
                // do nothing
            } else {
                printf("Unsupported token: '%c'\n", token);
            }
        }
    }

    if(inNumber){
        appendStringBuilderChar(sb, END_OF_NUMBER);
        // mark end of current number
        inNumber = false;
    }
    while(ops){
        appendStringBuilderChar(sb, popOperatorStack(&ops));
    }

    // keep this
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
