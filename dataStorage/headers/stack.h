#ifndef STACK
#define STACK

typedef struct Stack{
    int value;
    struct Stack* next;
} Stack;

Stack* newStack(int val);

void deleteStack(Stack** top);

void push(Stack** top, int val);
int peekStack(Stack* top);
int pop(Stack** top);

void printStack(Stack* top);

int testStack();

#endif
