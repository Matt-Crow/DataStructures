#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>

typedef struct LinkedList{
    struct LinkedList* next;
    struct LinkedList* prev;
    int value;
} LinkedList;

LinkedList* newLinkedList(int val);
void deleteLinkedList(LinkedList** head, LinkedList** tail);
void pushToFront(LinkedList** head, LinkedList** tail, int val);
void pushToBack(LinkedList** head, LinkedList** tail, int val);
int popFromFront(LinkedList** head, LinkedList** tail);
int popFromBack(LinkedList** head, LinkedList** tail);
int peekFront(LinkedList* head);
int peekBack(LinkedList* tail);
bool deleteNode(LinkedList** head, LinkedList** tail, int withValue);
void printLinkedList(LinkedList* head);

int testLinkedList();

#endif
