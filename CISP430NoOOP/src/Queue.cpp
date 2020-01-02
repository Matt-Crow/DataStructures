#include "Queue.h"
#include <iostream>

using namespace std;

template <class T>
Queue<T>::Queue()
{
    head = 0;
    tail = 0;
}

template <class T>
Queue<T>::~Queue()
{
    while(head){
        deque();
    }
}

template <class T>
void Queue<T>::enqueue(T value){
    QueueNode<T>* newNode = new QueueNode<T>(value);
    newNode->prev = tail;
    if(!head){
        //have no node
        head = newNode;
    } else {
        tail->next = newNode;
    }
    tail = newNode;
}

template <class T>
T Queue<T>::deque(){
    T ret = 0;
    if(head){
        ret = head->value;
        QueueNode<T>* temp = head;
        head = head->next;
        delete temp;

        if(!head){
            //deleted only node
            tail = 0;
        }
    }
    return ret;
}

template <class T>
void Queue<T>::print(){
    QueueNode<T>* curr = head;
    while(curr){
        cout << curr->value << " ";
        curr = curr->next;
    }
}

template <class T>
bool Queue<T>::isEmpty(){
    return head == 0;
}
