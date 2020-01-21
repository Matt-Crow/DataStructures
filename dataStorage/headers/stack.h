#ifndef STACK
#define STACK

struct Stack{
    int value;
    Stack* next;
};

struct Stack* newStack(int val);

void deleteStack(struct Stack* top);

void push(struct Stack** top, int val);
int peek(struct Stack* top);
int pop(struct Stack** top);

void printStack(struct Stack* top);

int testStack();

#endif
