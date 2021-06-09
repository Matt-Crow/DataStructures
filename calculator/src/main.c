#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "parser.h"
#include "treeParser.h"
#include "treeCommon.h"
#include "evaluator.h"

void nextExpression(char ip[], int maxIp);
void evaluateInfix(char ip[]);

int main(){
    int maxIp = 50;
    char ip[maxIp];
    ip[0] = '\0';

    while(ip[0] != 'q'){
        nextExpression(ip, maxIp);
        if(ip[0] != 'q'){
            evaluateInfix(ip);
        }
    }

    return 0;
}

void nextExpression(char ip[], int maxIp){
    printf("%s", "Enter a math expression, or 'q' to quit: ");
    fgets(ip, maxIp, stdin);
    char* nl = strchr(ip, '\n');
    if(nl){
        *nl = '\0';
    }

    printf("You entered \"%s\"\n", ip);
}

void evaluateInfix(char ip[]){
    char* postfix = toPostfix(ip);
    printf("As postfix: \"%s\"\n", postfix);

    printf("%s = %d\n\n", ip, evaluatePostfix(postfix));

    PostfixTree* tree = toPostfixTree(postfix);
    printPostfixTree(tree);
    printf("%c", '\n');
    deletePostfixTree(&tree);

    free(postfix);
    postfix = 0;
}
