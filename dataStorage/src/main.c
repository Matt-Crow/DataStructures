#include <stdio.h>
#include "core.h"
#include "stack.h"
#include "queue.h"
#include "linkedList.h"
#include "tree.h"
#include "hashArray.h"
#include "heap.h"

int main(){
    IntMenuOption* options[] = {
        newIntMenuOption("test stack", testStack),
        newIntMenuOption("test queue", testQueue),
        newIntMenuOption("test linked list", testLinkedList),
        newIntMenuOption("test binary tree", testBinaryTree),
        newIntMenuOption("test hash array", testHashArray),
        newIntMenuOption("test heap", testHeap)
    };
    int numOptions = sizeof(options) / sizeof(IntMenuOption*);

    doIntMenu(options, numOptions);

    for(int i = 0; i < numOptions; i++){
        freeIntMenuOption(&(options[i]));
    }
}
