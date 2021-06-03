#ifndef CORE
#define CORE

/*
This file contains functions relevant to creating menus in the terminal.
There are two types of menus supported here:
 1. int menus, which are used to select which sub-program to run, each of which
    accepts no argument, but returns their status as an int
 2. consumer menus, which allow the user to choose an option to interact with a
    data structure of some sort

The calling code is responsible for freeing the structures they allocate using
this module.
*/



typedef int (*IntSupplier)();

typedef struct IntMenuOption {
    char* msg;
    IntSupplier runIfSelected;
} IntMenuOption;

IntMenuOption* newIntMenuOption(char msg[], IntSupplier runIfSelected);
void freeIntMenuOption(IntMenuOption** menuOption);

int doIntMenu(IntMenuOption** options, int numOptions);



typedef void (*Consumer)(void** dataStructure);

typedef struct ConsumerMenuOption {
    char* msg;
    Consumer runIfSelected;
} ConsumerMenuOption;

ConsumerMenuOption* newConsumerMenuOption(char* msg, Consumer runIfSelected);
void freeConsumerMenuOption(ConsumerMenuOption** option);

int doConsumerMenu(ConsumerMenuOption** options, int numOptions, void** dataStructure);

#endif
