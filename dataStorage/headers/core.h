#ifndef CORE
#define CORE

/**
A Runnable is a function which
accepts no arguments, and returns
a status code. Used for creating menus.
*/
typedef int (*Runnable)();

typedef struct MenuOption {
    char* msg;
    Runnable runIfSelected;
} MenuOption;
MenuOption* newMenuOption(char msg[], Runnable runIfSelected);
int freeMenuOption(MenuOption** menuOption);

int doMenu(MenuOption** options, int numOptions);

int testCore();

#endif
