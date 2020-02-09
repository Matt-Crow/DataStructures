#ifndef LINKED_LIST
#define LINKED_LIST

#include <stdbool.h>

struct LinkedList{
    struct LinkedList* next;
    struct LinkedList* prev;
    int value;
};

struct LinkedList* newLinkedList(int val);
void deleteLinkedList(struct LinkedList** head, struct LinkedList** tail);
void pushToFront(struct LinkedList** head, struct LinkedList** tail, int val);
void pushToBack(struct LinkedList** head, struct LinkedList** tail, int val);
int popFromFront(struct LinkedList** head, struct LinkedList** tail);
int popFromBack(struct LinkedList** head, struct LinkedList** tail);
int peekFront(struct LinkedList* head);
int peekBack(struct LinkedList* tail);
bool deleteNode(struct LinkedList** head, struct LinkedList** tail, int withValue);
void printLinkedList(struct LinkedList* head);

int testLinkedList();

#endif
