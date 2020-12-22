#include <stdio.h>
#include "core.h"
#include "stack.h"
#include "queue.h"
#include "linkedList.h"
#include "tree.h"
#include "hashArray.h"
#include "heap.h"

int main(){
    MenuOption* options[] = {
        newMenuOption("test stack", testStack),
        newMenuOption("test queue", testQueue),
        newMenuOption("test linked list", testLinkedList),
        newMenuOption("test binary tree", testBinaryTree),
        newMenuOption("test hash array", testHashArray),
        newMenuOption("test heap", testHeap)
    };
    int numOptions = sizeof(options) / sizeof(MenuOption*);

    doMenu(options, numOptions);

    for(int i = 0; i < numOptions; i++){
        freeMenuOption(&(options[i]));
    }
}
