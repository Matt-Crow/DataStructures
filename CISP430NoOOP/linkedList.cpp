#include <iostream>

using namespace std;

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



int useLinkedList(){
    return 0;
}



template <typename T>
node<T>* newNode(T value){
    node<T>* ret = new node<T>;
    ret->prev = 0;
    ret->next = 0;
    ret->value = value;
    return ret;
}

template <typename T>
linkedList<T>* newLinkedList(){
    linkedList<T>* ret = new linkedList<T>;
    ret->head = 0;
    ret->tail = 0;
    return ret;
}

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
