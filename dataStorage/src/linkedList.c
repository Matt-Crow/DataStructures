#include "linkedList.h"
#include "core.h"
#include <stdio.h>
#include <stdlib.h>

void deleteLinkedList(LinkedList** list){
    if(list && *list){
        LinkedListNode* curr = list->head;
        while(curr){
            popFromFront(*list);
        }
        free(*list);
        *list = 0;
    }
}

LinkedListNode* newLinkedListNode(int val){
    LinkedListNode* ret = (LinkedListNode*)malloc(sizeof(LinkedListNode));
    ret->next = 0;
    ret->prev = 0;
    ret->value = val;
    return ret;
}

void deleteLinkedListNode(LinkedListNode** head, LinkedListNode** tail){
     while(*head){
         printf("Delete %i\n", popFromFront(head, tail));
     }
}

void pushToFront(LinkedListNode** head, LinkedListNode** tail, int val){
    if(head && tail){
        LinkedListNode* newHead = newLinkedListNode(val);
        newHead->next = *head;
        if(*head){
            //has at least one node
            (*head)->prev = newHead;
            (*head) = newHead;
        } else {
            //new node is only node
            (*head) = newHead;
            (*tail) = newHead;
        }
    } //can't do anything if they are null pointers
};

void pushToBack(LinkedListNode** head, LinkedListNode** tail, int val){
     if(head && tail){
         LinkedListNode* newTail = newLinkedListNode(val);
         newTail->prev = *tail;
         if(*tail){
             (*tail)->next = newTail;
             (*tail) = newTail;
         } else {
             (*head) = newTail;
             (*tail) = newTail;
         }
     }
}

int popFromFront(LinkedListNode** head, LinkedListNode** tail){
    int ret = 0;
    if(head && tail && *head){
        ret = peekFront(*head);
        LinkedListNode* oldHead = *head;
        LinkedListNode* newHead = oldHead->next;
        oldHead->next = 0;
        free(oldHead);

        if(newHead){
            *head = newHead;
            newHead->prev = 0;
        } else {
            *head = 0;
            *tail = 0;
        }
    }
    return ret;
}

int popFromBack(LinkedListNode** head, LinkedListNode** tail){
    int ret = 0;
    if(head && tail){
        ret = peekBack(*tail);
        LinkedListNode* oldTail = *tail;
        LinkedListNode* newTail = oldTail->prev;
        oldTail->prev = 0;
        free(oldTail);

        if(newTail){
            *tail = newTail;
            newTail->next = 0;
        } else {
            *head = 0;
            *tail = 0;
        }
    }
    return ret;
}

int peekFront(LinkedListNode* head){
    int ret = 0;
    if(head){
        ret = head->value;
    }
    return ret;
}
int peekBack(LinkedListNode* tail){
    int ret = 0;
    if(tail){
        ret = tail->value;
    }
    return ret;
}

bool deleteNode(LinkedListNode** head, LinkedListNode** tail, int withValue){
    bool found = false;
    if(head && tail){
        LinkedListNode* curr = *head;
        while(curr && !found){
            if(curr->value == withValue){
                found = true;
                if(curr == *head){
                    popFromFront(head, tail);
                } else if(curr == *tail){
                    popFromBack(head, tail);
                } else {
                    //in the middle
                    curr->prev->next = curr->next;
                    curr->next->prev = curr->prev;
                    curr->prev = 0;
                    curr->next = 0;
                    free(curr);
                }
                curr = 0;
            } else {
                curr = curr->next;
            }
        }
    }
    return found;
}

void printLinkedListNode(LinkedListNode* head){
    printf("%s", "Head of linked list:\n");
    LinkedListNode* curr = head;
    while(curr){
        printf("%i\n", curr->value);
        curr = curr->next;
    }
    printf("%s", "Tail of linked list.\n");
}

int testLinkedList(){
    LinkedListNode* head = 0;
    LinkedListNode* tail = 0;
    int ip = 0;
    printf("%s", "===LINKED LIST===\n");
    do {
        printf("%s", "~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
        printf("%s", "0: print the linked list\n");
        printf("%s", "1: push to the start of the linked list\n");
        printf("%s", "2: push to the end of the linked list\n");
        printf("%s", "3: pop the first element of the linked list\n");
        printf("%s", "4: pop the last element of the linked list\n");
        printf("%s", "5: delete a node with a given value\n");
        printf("%s", "-1: quit\n");
        printf("%s", "Choose an option: ");
        scanf("%d", &ip);
        switch(ip){
            case 0:
                printLinkedListNode(head);
                break;
            case 1:
                printf("%s", "Enter value to push to the front of the linked list: ");
                scanf("%d", &ip);
                pushToFront(&head, &tail, ip);
                ip = 1;
                break;
            case 2:
                printf("%s", "Enter value to push to the back of the linked list: ");
                scanf("%d", &ip);
                pushToBack(&head, &tail, ip);
                ip = 2;
                break;
            case 3:
                if(head){
                    ip = popFromFront(&head, &tail);
                    printf("Popped %i\n", ip);
                    ip = 3;
                } else {
                    printf("%s", "Nothing to pop\n");
                }
                break;
            case 4:
                if(head){
                    ip = popFromBack(&head, &tail);
                    printf("Popped %i\n", ip);
                    ip = 4;
                } else {
                    printf("%s", "Nothing to pop\n");
                }
                break;
            case 5:
                printf("%s", "Enter number to delete: ");
                scanf("%d", &ip);
                bool success = deleteNode(&head, &tail, ip);
                if(success){
                    printf("Deleted %i\n", ip);
                } else {
                    printf("%i is not in the linked list\n", ip);
                }
                ip = 5;
                break;
        }
    } while(ip != -1);

    deleteLinkedListNode(&head, &tail);
    head = 0;
    tail = 0;

    return 0;
}
