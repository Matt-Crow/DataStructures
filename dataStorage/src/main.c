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
        newMenuOption("test stack", testStack)
    };
    doMenu(options, 1);

    int ip = 0;
    do{
        printf("%s", "1: test stack\n");
        printf("%s", "2: test queue\n");
        printf("%s", "3: test linked list\n");
        printf("%s", "4: test binary tree\n");
        printf("%s", "5: test hash array\n");
        printf("%s", "6: test heap\n");
        printf("%s", "-1: Quit\n");
        printf("%s", "Please choose an option: ");
        scanf("%d", &ip);
        switch(ip){
            case 1:
                testStack();
                break;
            case 2:
                testQueue();
                break;
            case 3:
                testLinkedList();
                break;
            case 4:
                testBinaryTree();
                break;
            case 5:
                testHashArray();
                break;
            case 6:
                testHeap();
                break;
        }
    } while(ip != -1);
}
