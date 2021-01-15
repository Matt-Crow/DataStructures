#include "core.h"
#include<stdio.h>
#include<stdlib.h>




MenuOption* newMenuOption(char msg[], Runnable runIfSelected){
    MenuOption* ret = (MenuOption*)malloc(sizeof(MenuOption));
    ret->msg = msg;
    ret->runIfSelected = runIfSelected;
    return ret;
}
int freeMenuOption(MenuOption** menuOption){
    int canFree = menuOption && *menuOption;
    if(canFree){
        free(*menuOption);
        *menuOption = 0;
    }
    return canFree;
}

IntMenuOption* newIntMenuOption(char msg[], IntSupplier runIfSelected){
    IntMenuOption* ret = (IntMenuOption*)malloc(sizeof(IntMenuOption));
    ret->msg = msg;
    ret->runIfSelected = runIfSelected;
    return ret;
}
int freeIntMenuOption(IntMenuOption** menuOption){
    int canFree = menuOption && *menuOption;
    if(canFree){
        free(*menuOption);
        *menuOption = 0;
    }
    return canFree;
}

int doMenu(MenuOption** options, int numOptions){
    int ret = 0;
    int ip = 0;
    Runnable selected;
    do {
        for(int optNum = 0; optNum < numOptions; optNum++){
            printf("%d: %s\n", optNum + 1, (options[optNum])->msg);
        }
        printf("%s", "-1: Quit\n");
        printf("%s", "Please choose an option: ");
        scanf("%d", &ip);
        if(ip >= 1 && ip <= numOptions){
            selected = options[ip - 1]->runIfSelected;
            selected();
        }
    } while(ip != -1);

    return ret;
}

int doIntMenu(IntMenuOption** options, int numOptions){
    int ret = 0;
    int ip = 0;
    IntSupplier selected;
    int result;
    do {
        for(int optNum = 0; optNum < numOptions; optNum++){
            printf("%d: %s\n", optNum + 1, (options[optNum])->msg);
        }
        printf("%s", "-1: Quit\n");
        printf("%s", "Please choose an option: ");
        scanf("%d", &ip);
        if(ip >= 1 && ip <= numOptions){
            selected = options[ip - 1]->runIfSelected;
            result = selected();
            printf("Option returned %d.\n", result);
        }
    } while(ip != -1);

    return ret;
}
