#include "parser.h"
#include "common.h"
#include<stdlib.h>
#include<ctype.h>

/*
Private function prototypes
*/

typedef struct OperatorStack {
    struct OperatorStack* next;
    char operator;
} OperatorStack;

OperatorStack* newOperatorStack(char operator);
void deleteOperatorStack(OperatorStack** stack);
void push(OperatorStack** stack, char operator);
char pop(OperatorStack** stack);


/*
Public functions
*/
char* toPostfix(char* infix){
    StringBuilder* postfixBuilder = newStringBuilder(16); // default capacity
    OperatorStack* ops = 0;

    // todo: all this

    char* asPostfix = build(postfixBuilder);
    deleteStringBuilder(&postfixBuilder);
    return asPostfix;
}



/*
Private function implementations
*/
OperatorStack* newOperatorStack(char operator){
    OperatorStack* newFrame = (OperatorStack*)malloc(sizeof(OperatorStack));
    newFrame->next = 0;
    newFrame->operator = operator;
    return newFrame;
}

void deleteOperatorStack(OperatorStack** stack){
    while(stack && *stack){
        pop(stack);
    }
}

void push(OperatorStack** stack, char operator){
    if(stack){
        OperatorStack* newTop = newOperatorStack(operator);
        newTop->next = *stack;
        *stack = newTop;
    }
}

char pop(OperatorStack** stack){
    char value = ERROR;
    if(stack && *stack){
        OperatorStack* oldTop = *stack;
        value = oldTop->operator;
        *stack = oldTop->next;
        free(oldTop);
        oldTop = 0;
    }
    return value;
}
