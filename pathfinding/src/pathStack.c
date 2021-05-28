#include "pathStack.h"
#include "travelInfo.h"
#include<stdio.h>
#include<stdlib.h>

void freePathStack(PathStack** top){
    TravelInfo* temp;
    while(top && *top){ // while not empty
        temp = popFromPathStack(top);
        freeTravelInfo(&temp);
    }
}

void pushToPathStack(PathStack** top, TravelInfo* value){
    if(top){
        PathStack* newTop = (PathStack*)malloc(sizeof(PathStack));
        newTop->value = value;
        newTop->prev = *top;
        *top = newTop;
    }
}
TravelInfo* popFromPathStack(PathStack** top){
    TravelInfo* popped = NULL;
    if(top && *top){
        PathStack* freeMe = *top;
        popped = freeMe->value;
        *top = freeMe->prev;
        free(freeMe); // don't call freePathStack here
    }
    return popped;
}

void printPathStack(PathStack* top){
    PathStack* curr = top;
    printf("%s\n", "Top of the stack");
    while(curr){
        printf("%c", '[');
        printTravelInfo(curr->value);
        printf("%s", "]\n");
        curr = curr->prev;
    }
    printf("%s\n", "Bottom of the stack");
}
