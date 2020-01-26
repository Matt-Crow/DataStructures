#include <stdio.h>
#include "linkedList.h"

struct LinkedList* newLinkedList(int val){
    struct LinkedList* ret = (struct LinkedList*)malloc(sizeof(struct LinkedList));
    ret->next = 0;
    ret->prev = 0;
    ret->value = val;
}

void deleteLinkedList(struct LinkedList** head, struct LinkedList** tail){
     while(head){
         printf("Delete %i\n", popFromFront(head, tail));
     }
}

void pushToFront(struct LinkedList** head, struct LinkedList** tail, int val){
    if(head && tail){
        struct LinkedList* newHead = newLinkedList(val);
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

void pushToBack(struct LinkedList** head, struct LinkedList** tail, int val){
     if(head && tail){
         struct LinkedList* newTail = newLinkedList(val);
         newHead->prev = *tail;
         if(*tail){
             (*tail)->next = newTail;
             (*tail) = newTail;
         } else {
             (*head) = newTail;
             (*tail) = newTail;
         }
     }
}

int popFromFront(struct LinkedList** head, struct LinkedList** tail){
    int ret = 0;
    if(head && tail){
        ret = peekFront(*head);
        struct LinkedList* oldHead = *head;
        struct LinkedList* newHead = oldHead->next;
        oldHead->next = 0;
        delete oldHead;

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

int popFromBack(struct LinkedList** head, struct LinkedList** tail){
    int ret = 0;
    if(head && tail){
        ret = peekBack(*tail);
        struct LinkedList* oldTail = *tail;
        struct LinkedList* newTail = oldTail->prev;
        oldTail->prev = 0;
        delete oldTail;

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

int peekFront(struct LinkedList* head){
    int ret = 0;
    if(head){
        ret = head->value;
    }
    return ret;
}
int peekBack(struct LinkedList* tail){
    int ret = 0;
    if(tail){
        ret = tail->value;
    }
    return ret;
}

bool deleteNode(struct LinkedList** head, struct LinkedList** tail, int withValue){
    bool found = false;
    if(head && tail){
        struct LinkedList* curr = *head;
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
                    delete curr;
                }
                curr = 0;
            } else {
                curr = curr->next;
            }
        }
    }
    return found;
}

void printLinkedList(struct LinkedList* head){
    printf("%s", "Head of linked list:\n");
    struct LinkedList* curr = head;
    while(curr){
        printf("%i\n", curr->value);
        curr = curr->next;
    }
    printf("%s", "Tail of linked list.\n");
}

int testLinkedList(){
    LinkedList<int>* ll = new LinkedList<int>();
    int ip = 0;
    std::cout << "===LINKED LIST===" << std::endl;
    while(ip != -1){
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Choose an option: " << std::endl;
        std::cout << "0: print the linked list" << std::endl;
        std::cout << "1: push to the start of the linked list" << std::endl;
        std::cout << "2: push to the end of the linked list" << std::endl;
        std::cout << "3: pop the first element of the linked list" << std::endl;
        std::cout << "4: pop the last element of the linked list" << std::endl;
        std::cout << "5: delete a node with a given value" << std::endl;
        std::cout << "-1: quit" << std::endl;
        std::cin >> ip;
        switch(ip){
        case 0:
            ll->print();
            break;
        case 1:
            std::cout << "Enter value to push to the front of the linked list: ";
            std::cin >> ip;
            ll->pushToFront(ip);
            ip = 1;
            break;
        case 2:
            std::cout << "Enter value to push to the back of the linked list: ";
            std::cin >> ip;
            ll->pushToBack(ip);
            ip = 2;
            break;
        case 3:
            if(ll->isEmpty()){
                std::cout << "Nothing to pop" << std::endl;
            } else {
                ip = ll->popFromFront();
                std::cout << "Popped " << ip << std::endl;
                ip = 3;
            }
            break;
        case 4:
            if(ll->isEmpty()){
                std::cout << "Nothing to pop" << std::endl;
            } else {
                ip = ll->popFromBack();
                std::cout << "Popped " << ip << std::endl;
                ip = 4;
            }
            break;
        case 5:
            std::cout << "Enter number to delete: ";
            std::cin >> ip;
            bool success = ll->deleteNode(ip);
            if(success){
                std::cout << "Deleted " << ip << std::endl;
            } else {
                std::cout << ip << " is not in the linked list" << std::endl;
            }
            ip = 5;
            break;
        }
    }

    delete ll;

    return 0;
}
