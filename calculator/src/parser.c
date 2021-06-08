#include "parser.h"
#include "common.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
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
char popOperatorStack(OperatorStack** stack);


/*
Public functions
*/
char* toPostfix(char* infix){
    StringBuilder* sb = newStringBuilder(16); // default capacity
    OperatorStack* ops = 0;

    char token;
    for(int offset = 0; offset < strlen(infix); ++offset){
        token = infix[offset];
        if(isdigit(token)){
            appendStringBuilderChar(sb, token);
        } else if(token == '('){
            push(&ops, token);
        } else if(token == ')'){
            // pop until it finds the matching '('
            while(token != '('){
                token = popOperatorStack(&ops);
                if(token != '('){
                    appendStringBuilderChar(sb, END_OF_NUMBER);
                    appendStringBuilderChar(sb, token);
                }
            }
        }
        //if the token is an operator, pop until the top is LESS precedence than the token,
        //then push to token.
        else if(token == '+' || token == '-'){
            appendStringBuilderChar(sb, END_OF_NUMBER);
            // mark end of current number

            while(ops && ops->operator != '('){
                appendStringBuilderChar(sb, popOperatorStack(&ops));
            }
            push(&ops, token);
        } else if(token == '*' || token == '/'){
            appendStringBuilderChar(sb, END_OF_NUMBER);
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

    appendStringBuilderChar(sb, END_OF_NUMBER); // where do I need this?
    while(ops){
        appendStringBuilderChar(sb, popOperatorStack(&ops));
    }

    char* asPostfix = build(sb);
    deleteStringBuilder(&sb);
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
        popOperatorStack(stack);
    }
}

void push(OperatorStack** stack, char operator){
    if(stack){
        OperatorStack* newTop = newOperatorStack(operator);
        newTop->next = *stack;
        *stack = newTop;
    }
}

char popOperatorStack(OperatorStack** stack){
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
