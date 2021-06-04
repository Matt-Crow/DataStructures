#include "stack.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>

Stack* newStack(int val){
    Stack* ret = (Stack*)malloc(sizeof(Stack));
    ret->value = val;
    ret->next = 0;
    return ret;
}

void deleteStack(Stack** top){
    while(top && *top){
        pop(top);
    }
}

void push(Stack** top, int val){
    if(top){
        //cannot be null pointer.
        Stack* newTop = newStack(val);
        newTop->next = *top; //if nothing on the stack, *top is null, which is fine
        *top = newTop;
    }
}

int peekStack(Stack* top){
    int ret = 0;
    if(top){
        ret = top->value;
    }
    return ret;
}

int pop(Stack** top){
    int ret = 0;
    if(top && *top){
        //top isn't null pointer, and has at least 1 item in the stack
        Stack* oldTop = *top;
        Stack* newTop = oldTop->next;
        ret = oldTop->value;
        free(oldTop);
        *top = newTop;
    }
    return ret;
}

void printStack(Stack* top){
    Stack* curr = top;
    printf("%s", "Top of the stack\n");
    while(curr){
        printf("%i\n", curr->value);
        curr = curr->next;
    }
    printf("%s", "Bottom of the stack\n");
}

Stack* asStackPtr(void** dataStructure){
    Stack** ptrPtr = (Stack**)dataStructure;
    return *ptrPtr;
}

void doPrintStack(void** dataStructure){
    printStack(asStackPtr(dataStructure));
}

void doPushStack(void** dataStructure){
    Stack** topPtr = (Stack**)dataStructure;
    int ip;
    printf("%s", "Enter value to push: ");
    scanf("%d", &ip);
    push(topPtr, ip);
}

void doPopStack(void** dataStructure){
    if(*dataStructure){
        int ip = pop((Stack**)dataStructure);
        printf("Popped %i\n", ip);
    } else {
        printf("%s", "Nothing to pop\n");
    }
}

void doDeleteStack(void** dataStructure){
    deleteStack((Stack**)dataStructure);
}

int testStack(){
    Stack* top = 0;

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("Print the stack", &doPrintStack),
        newConsumerMenuOption("Push to the stack", &doPushStack),
        newConsumerMenuOption("Pop from the stack", &doPopStack),
        newConsumerMenuOption("Delete the stack", &doDeleteStack)
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    doConsumerMenu(options, numOptions, (void**)&top);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteStack(&top);

    return 0;
}
