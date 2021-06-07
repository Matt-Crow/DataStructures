#include "linkedList.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>



/*
Private functions
*/

LinkedListNode* newLinkedListNode(int val){
    LinkedListNode* ret = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    ret->next = 0;
    ret->prev = 0;
    ret->value = val;
    return ret;
}

/*
Does not cascade delete
*/
void deleteLinkedListNode(LinkedListNode** node){
     if(node && *node){
         free(*node);
         *node = 0;
     }
}


/*
Public functions
*/

LinkedList* newLinkedList(){
    LinkedList* ll = (LinkedList*)malloc(sizeof(LinkedList));
    ll->head = 0;
    ll->tail = 0;
    return ll;
}

/*
Deletes the LinkedList and all of it's nodes
*/
void deleteLinkedList(LinkedList** list){
    if(list && *list){
        while((*list)->head){
            popFromFront(*list);
        }
        free(*list);
        *list = 0;
    }
}

void pushToFront(LinkedList* list, int val){
    if(list){ // mustn't be a null pointer
        LinkedListNode* newHead = newLinkedListNode(val);
        newHead->next = list->head;
        if(list->head){ //has at least one node
            list->head->prev = newHead;
        } else { //new node is only node
            list->tail = newHead;
        }
        list->head = newHead;
    }
}

void pushToBack(LinkedList* list, int val){
     if(list){
         LinkedListNode* newTail = newLinkedListNode(val);
         newTail->prev = list->tail;
         if(list->tail){
             list->tail->next = newTail;
         } else {
             list->head = newTail;
         }
         list->tail = newTail;
     }
}

int popFromFront(LinkedList* list){
    int ret = 0;
    if(list && list->head){
        ret = peekFront(list);
        LinkedListNode* oldHead = list->head;
        LinkedListNode* newHead = oldHead->next;
        oldHead->next = 0;
        deleteLinkedListNode(&oldHead);
        if(newHead){
            newHead->prev = 0;
        } else {
            list->tail = 0;
        }
        list->head = newHead;
    }
    return ret;
}

int popFromBack(LinkedList* list){
    int ret = 0;
    if(list && list->tail){
        ret = peekBack(list);
        LinkedListNode* oldTail = list->tail;
        LinkedListNode* newTail = oldTail->prev;
        oldTail->prev = 0;
        deleteLinkedListNode(&oldTail);
        if(newTail){
            newTail->next = 0;
        } else {
            list->head = 0;
        }
        list->tail = newTail;
    }
    return ret;
}

int peekFront(LinkedList* list){
    int ret = 0;
    if(list && list->head){
        ret = list->head->value;
    }
    return ret;
}

int peekBack(LinkedList* list){
    int ret = 0;
    if(list && list->tail){
        ret = list->tail->value;
    }
    return ret;
}

bool deleteNode(LinkedList* list, int withValue){
    bool found = false;
    if(list){
        LinkedListNode* curr = list->head;
        while(curr && !found){
            if(curr->value == withValue){
                found = true;
                if(curr == list->head){
                    popFromFront(list);
                } else if(curr == list->tail){
                    popFromBack(list);
                } else {
                    //in the middle
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = 0;
                    curr->next = 0;
                    deleteLinkedListNode(&curr);
                }
                curr = 0;
            } else {
                curr = curr->next;
            }
        }
    }
    return found;
}

void printLinkedList(LinkedList* list){
    printf("%s\n", "Head of linked list:");
    LinkedListNode* curr = list->head;
    while(curr){
        printf("%d ", curr->value);
        curr = curr->next;
    }
    printf("\n%s\n", "Tail of linked list.");
}

/*
Menu options
*/

LinkedList* asLinkedList(void** dataStructure){
    LinkedList** ptrPtr = (LinkedList**)dataStructure;
    return *ptrPtr;
}

void doPrintLinkedList(void** dataStructure){
    printLinkedList(asLinkedList(dataStructure));
}

void doPushStartLinkedList(void** dataStructure){
    int ip;
    printf("%s", "Enter value to push to the front of the linked list: ");
    scanf("%d", &ip);
    pushToFront(asLinkedList(dataStructure), ip);
}

void doPushEndLinkedList(void** dataStructure){
    int ip;
    printf("%s", "Enter value to push to the back of the linked list: ");
    scanf("%d", &ip);
    pushToBack(asLinkedList(dataStructure), ip);
}

void doPopFirstLinkedList(void** dataStructure){
    LinkedList* list = asLinkedList(dataStructure);
    if(list->head){
        int val = popFromFront(list);
        printf("Popped %d\n", val);
    } else {
        printf("%s", "Nothing to pop\n");
    }
}

void doPopLastLinkedList(void** dataStructure){
    LinkedList* list = asLinkedList(dataStructure);
    if(list->tail){
        int val = popFromBack(list);
        printf("Popped %d\n", val);
    } else {
        printf("%s", "Nothing to pop\n");
    }
}

void doDeleteFromLinkedList(void** dataStructure){
    printf("%s", "Enter number to delete: ");
    int ip;
    scanf("%d", &ip);
    bool success = deleteNode(asLinkedList(dataStructure), ip);
    if(success){
        printf("Deleted %d\n", ip);
    } else {
        printf("%d is not in the linked list\n", ip);
    }
}

int testLinkedList(){
    LinkedList* list = newLinkedList();

    printf("%s\n", "Linked List");

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("print the linked list", &doPrintLinkedList),
        newConsumerMenuOption("push to the start of the linked list", &doPushStartLinkedList),
        newConsumerMenuOption("push to the end of the linked list", &doPushEndLinkedList),
        newConsumerMenuOption("pop the first element of the linked list", &doPopFirstLinkedList),
        newConsumerMenuOption("pop the last element of the linked list", &doPopLastLinkedList),
        newConsumerMenuOption("delete a node with a chosen value", &doDeleteFromLinkedList)
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    doConsumerMenu(options, numOptions, (void**)&list);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteLinkedList(&list);

    return 0;
}
