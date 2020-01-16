#include<iostream>
#include "queue.h"

template<class T>
QueueNode<T>::QueueNode(T val){
    this->value = val;
    this->prev = 0;
    this->next = 0;
}

template<class T>
QueueNode<T>::~QueueNode(){
    std::cout << "Delete " << this->value << std::endl;
}

template<class T>
void QueueNode<T>::setPrev(QueueNode<T>* prev){
    this->prev = prev;
}

template<class T>
void QueueNode<T>::setNext(QueueNode<T>* next){
    this->next = next;
}

template<class T>
QueueNode<T>* QueueNode<T>::getPrev(){
    return this->prev;
}

template<class T>
QueueNode<T>* QueueNode<T>::getNext(){
    return this->next;
}

template<class T>
T QueueNode<T>::getValue(){
    return this->value;
}



template<class T>
Queue<T>::Queue(){
    this->head = 0;
    this->tail = 0;
}

template<class T>
Queue<T>::~Queue(){
    QueueNode<T>* curr = this->head;
    QueueNode<T>* temp = 0;
    while(curr){
        temp = curr->getNext();
        delete curr;
        curr = temp;
        temp = 0;
    }
}

template<class T>
void Queue<T>::enqueue(T val){
    QueueNode<T>* nn = new QueueNode<T>(val);
    nn->setNext(0);
    nn->setPrev(this->tail);
    if(this->tail){
        this->tail->setNext(nn);
    }
    this->tail = nn;
    if(!this->head){
        this->head = nn;
    }
}

template<class T>
T Queue<T>::dequeue(){
    T ret = 0;
    if(!this->isEmpty()){
        QueueNode<T>* oldHead = this->head;
        ret = oldHead->getValue();
        this->head = oldHead->getNext();
        delete oldHead;
        if(!this->head){
            this->tail = 0;
        }
    }
    return ret;
}

template<class T>
T Queue<T>::peek(){
    T ret = 0;
    if(!this->isEmpty()){
        ret = this->head->getValue();
    }
    return ret;
}

template<class T>
bool Queue<T>::isEmpty(){
    return this->head == 0;
}

template<class T>
void Queue<T>::print(){
    QueueNode<T>* curr = this->head;
    std::cout << "Start of queue: " << std::endl;
    while(curr){
        std::cout << curr->getValue() << std::endl;
        curr = curr->getNext();
    }
    std::cout << "End of queue" << std::endl;
}

template<class T>
int Queue<T>::test(){
    Queue<int>* q = new Queue<int>();

    int ip = 0;
    std::cout << "===QUEUE===" << std::endl;
    while(ip != -1){
        std::cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << std::endl;
        std::cout << "Choose an option: " << std::endl;
        std::cout << "0: print the queue" << std::endl;
        std::cout << "1: enqueue to the queue" << std::endl;
        std::cout << "2: dequeue the queue" << std::endl;
        std::cout << "-1: quit" << std::endl;
        std::cin >> ip;
        switch(ip){
        case 0:
            q->print();
            break;
        case 1:
            std::cout << "Enter value to enqueue: ";
            std::cin >> ip;
            q->enqueue(ip);
            ip = 1;
            break;
        case 2:
            if(q->isEmpty()){
                std::cout << "Nothing to dequeue" << std::endl;
            } else {
                ip = q->dequeue();
                std::cout << "dequeued " << ip << std::endl;
                ip = 2;
            }
            break;
        }
    }

    delete q;
    return 0;
}
