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

void deleteLinkedList(LinkedList** list);
LinkedListNode* newLinkedListNode(int val);
void deleteLinkedListNode(LinkedListNode** head, LinkedListNode** tail);
void pushToFront(LinkedListNode** head, LinkedListNode** tail, int val);
void pushToBack(LinkedListNode** head, LinkedListNode** tail, int val);
int popFromFront(LinkedListNode** head, LinkedListNode** tail);
int popFromBack(LinkedListNode** head, LinkedListNode** tail);
int peekFront(LinkedListNode* head);
int peekBack(LinkedListNode* tail);
bool deleteNode(LinkedListNode** head, LinkedListNode** tail, int withValue);
void printLinkedListNode(LinkedListNode* head);

int testLinkedList();

#endif
