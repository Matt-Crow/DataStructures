#include "evaluator.h"
#include "common.h"
#include<stdlib.h>
#include<ctype.h>
#include<stdio.h>
#include<string.h>

/*
Private prototypes
*/

typedef struct IntStack {
    struct IntStack* next;
    int value;
} IntStack;

IntStack* newIntStack(int value);
void deleteIntStack(IntStack** stack);
void pushIntStack(IntStack** top, int value);
int popIntStack(IntStack** top);

void processOperator(char operator, IntStack** operandStack);

/*
Public
*/

int evaluatePostfix(char* postfix){
    IntStack* nums = 0;

    int currNum = 0;
    char token;
    for(int offset = 0; offset < strlen(postfix); ++offset){
        token = postfix[offset];
        if(isdigit(token)){
            currNum = currNum * 10 + charToInt(token);
        } else if(token == END_OF_NUMBER){
            pushIntStack(&nums, currNum);
            currNum = 0;
        } else {
            processOperator(token, &nums);
        }
    }

    return popIntStack(&nums);
}

/*
Private definitions
*/

IntStack* newIntStack(int value){
    IntStack* frame = (IntStack*)malloc(sizeof(IntStack));
    frame->next = 0;
    frame->value = value;
    return frame;
}

void deleteIntStack(IntStack** stack){
    while(stack && *stack){
        popIntStack(stack);
    }
}

void pushIntStack(IntStack** top, int value){
    if(top){
        IntStack* newTop = newIntStack(value);
        newTop->next = *top;
        *top = newTop;
    } else {
        printf("%s\n", "Cannot push to null pointer");
    }
}

int popIntStack(IntStack** top){
    int value = 0;
    if(top && *top){
        IntStack* oldTop = *top;
        value = oldTop->value;
        *top = oldTop->next;
        free(oldTop);
    } else {
        printf("%s\n", "No values in int stack");
    }
    return value;
}

void processOperator(char operator, IntStack** operandStack){
    int a = popIntStack(operandStack);
    int b = popIntStack(operandStack);
    switch(operator){
        case '+': {
            pushIntStack(operandStack, b + a);
            break;
        }
        case '-': {
            pushIntStack(operandStack, b - a);
            break;
        }
        case '*': {
            pushIntStack(operandStack, b * a);
            break;
        }
        case '/': {
            pushIntStack(operandStack, b / a);
            break;
        }
        default: {
            printf("Unsupported token: '%c'\n", operator);
            // push back operands
            pushIntStack(operandStack, b);
            pushIntStack(operandStack, a);
            break;
        }
    }
}
