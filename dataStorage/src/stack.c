#include <stdio.h>
#include <iostream>
#include "stack.h"

struct Stack* newStack(int val){
    struct Stack* ret = (struct Stack*)malloc(sizeof(struct Stack));
    ret->value = val;
    ret->next = 0;
    return ret;
}

void deleteStack(struct Stack* top){
    if(top){
        deleteStack(top->next);
        printf("delete %i\n", top->value);
        delete top;
        top = 0;
    }
}

void push(struct Stack** top, int val){
    if(top){
        //cannot be null pointer.
        struct Stack* newTop = newStack(val);
        newTop->next = *top; //if nothing on the stack, *top is null, which is fine
        *top = newTop;
    }
}

int peek(struct Stack* top){
    int ret = 0;
    if(top){
        ret = top->value;
    }
    return ret;
}

int pop(struct Stack** top){
    int ret = 0;
    if(top && *top){
        //top isn't null pointer, and has at least 1 item in the stack
        struct Stack* oldTop = *top;
        struct Stack* newTop = (*top)->next;
        ret = oldTop->value;
        oldTop->next = 0; //prevent deleteStack from cascading
        deleteStack(oldTop);
        oldTop = 0;
        *top = newTop;
    }
    return ret;
}

void printStack(struct Stack* top){
    struct Stack* curr = top;
    printf("%s", "Top of the stack\n");
    while(curr){
        printf("%i\n", curr->value);
        curr = curr->next;
    }
    printf("%s", "Bottom of the stack\n");
}

int testStack(){
    Stack* top = 0;
    int ip = 0;

    do {
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the stack\n");
        printf("%s", "1: Push to the stack\n");
        printf("%s", "2: Pop from the stack\n");
        printf("%s", "3: Delete the stack\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);

        switch(ip){
            case 0:
                printStack(top);
                break;
            case 1:
                printf("%s", "Enter value to push: ");
                scanf("%d", &ip);
                push(&top, ip);
                ip = 1;
                break;
            case 2:
                if(top){
                    ip = pop(&top);
                    printf("Popped %i\n", ip);
                    ip = 2;
                } else {
                    printf("%s", "Nothing to pop\n");
                }
                break;
            case 3:
                deleteStack(top);
                top = 0;
                break;
        }
    } while(ip != -1);

    deleteStack(top);
    top = 0;

    return 0;
}

/*
template<class T>
Stack<T>::~Stack(){
    StackNode<T>* curr = this->top;
    StackNode<T>* temp;
    while(curr){
        temp = curr->getNext();
        delete curr;
        curr = temp;
        temp = 0;
    }
    this->top = 0;
}
*/
