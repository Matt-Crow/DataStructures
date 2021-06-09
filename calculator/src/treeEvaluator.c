#include "treeEvaluator.h"
#include "common.h"
#include "treeCommon.h"

int evaluateOperator(char* opString, int left, int right);

int evaluatePostfixTree(PostfixTree* root){
    int value = 0;
    if(root){
        int left = evaluatePostfixTree(root->left);
        int right = evaluatePostfixTree(root->right);
        value = evaluateOperator(root->token, left, right);
    }
    return value;
}

int evaluateOperator(char* opString, int left, int right){
    int value = 0;
    switch (opString[0]) { // check if it's an operator
        case '+': {
            value = left + right;
            break;
        }
        case '-': {
            value = left - right;
            break;
        }
        case '*': {
            value = left * right;
            break;
        }
        case '/': {
            value = left / right;
            break;
        }
        default: {
            // not an operator, so treat it as an int
            value = strToInt(opString);
            break;
        }
    }
    return value;
}
