#ifndef MISC_H_INCLUDED
#define MISC_H_INCLUDED

#include <iostream>
using namespace std;

char toChar(int i);
template <typename T>
struct node {
    node<T>* prev;
    node<T>* next;
    T value;
};

template <typename T>
struct linkedList{
    node<T>* head;
    node<T>* tail;
};

template <typename T>
node<T>* newNode(T value);

template <typename T>
linkedList<T>* newLinkedList();

template <typename T>
void push(linkedList<T>* ll, T value);

template <typename T>
void enqueue(linkedList<T>* ll, T value);

template <typename T>
T pop(linkedList<T>* ll);

template <typename T>
T dequeue(linkedList<T>* ll);

template <typename T>
bool deleteNode(linkedList<T>* ll, T withValue);

template <typename T>
void print(linkedList<T>* ll, ostream &out);

#endif // MISC_H_INCLUDED
