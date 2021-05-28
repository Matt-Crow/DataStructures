#include<stdio.h>
#include "travelInfo.h"
#include "pathStack.h"

int main(){
    TravelInfo* t = 0;
    PathStack* stack = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i != j){
                t = newTravelInfo(i, j, i * j);
                pushToPathStack(&stack, t);
            }
        }
    }
    printPathStack(stack);
    freePathStack(&stack);

    return 0;
}
