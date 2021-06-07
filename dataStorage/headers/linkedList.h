#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>

typedef struct LinkedListNode{
    struct LinkedListNode* next;
    struct LinkedListNode* prev;
    int value;
} LinkedListNode;

typedef struct LinkedList {
    LinkedListNode* head;
    LinkedListNode* tail;
} LinkedList;

LinkedList* newLinkedList();
void deleteLinkedList(LinkedList** list);

void pushToFront(LinkedList* list, int val);
void pushToBack(LinkedList* list, int val);
int popFromFront(LinkedList* list);
int popFromBack(LinkedList* list);
int peekFront(LinkedList* list);
int peekBack(LinkedList* list);
bool deleteNode(LinkedList* list, int withValue);
void printLinkedList(LinkedList* list);

int testLinkedList();

#endif
