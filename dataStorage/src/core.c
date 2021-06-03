#include "core.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>



IntMenuOption* newIntMenuOption(char msg[], IntSupplier runIfSelected){
    IntMenuOption* option = (IntMenuOption*)malloc(sizeof(IntMenuOption));
    int n = strlen(msg);
    option->msg = (char*)malloc(sizeof(char) * (n + 1));
    strncpy(option->msg, msg, n);
    option->msg[n] = '\0';
    option->runIfSelected = runIfSelected;
    return option;
}
void freeIntMenuOption(IntMenuOption** menuOption){
    if(menuOption && *menuOption){
        IntMenuOption* opt = *menuOption;
        free(opt->msg);
        free(opt);
        *menuOption = 0;
    }
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



ConsumerMenuOption* newConsumerMenuOption(char* msg, Consumer runIfSelected){
    ConsumerMenuOption* option = (ConsumerMenuOption*)malloc(sizeof(ConsumerMenuOption));
    int n = strlen(msg);
    option->msg = (char*)malloc(sizeof(char) * (n + 1));
    strncpy(option->msg, msg, n);
    option->msg[n] = '\0';
    option->runIfSelected = runIfSelected;
    return option;
}
void freeConsumerMenuOption(ConsumerMenuOption** option){
    if(option && *option){
        ConsumerMenuOption* opt = *option;
        free(opt->msg);
        free(opt);
        *option = 0;
    }
}
int doConsumerMenu(ConsumerMenuOption** options, int numOptions, void** dataStructure){
    int status = 0;
    int ip = 0;
    Consumer selected;
    do {
        for(int optNum = 0; optNum < numOptions; optNum++){
            printf("%d: %s\n", optNum + 1, (options[optNum])->msg);
        }
        printf("%s", "-1: Quit\n");
        printf("%s", "Please choose an option: ");
        scanf("%d", &ip);
        if(ip >= 1 && ip <= numOptions){
            selected = options[ip - 1]->runIfSelected;
            selected(dataStructure);
        }
    } while(ip != -1);

    return status;
}
