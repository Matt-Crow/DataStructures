#include <iostream>
#include "linkedList.h"

template<class T>
LinkedListNode<T>::LinkedListNode(T val){
    this->value = val;
    this->next = 0;
    this->prev = 0;
}

template<class T>
LinkedListNode<T>::~LinkedListNode(){
    std::cout << "Delete " << this->value << std::endl;
}

template<class T>
void LinkedListNode<T>::setNext(LinkedListNode<T>* next){
    this->next = next;
}

template<class T>
void LinkedListNode<T>::setPrev(LinkedListNode<T>* prev){
    this->prev = prev;
}

template<class T>
LinkedListNode<T>* LinkedListNode<T>::getNext(){
    return this->next;
}

template<class T>
LinkedListNode<T>* LinkedListNode<T>::getPrev(){
    return this->prev;
}

template<class T>
T LinkedListNode<T>::getValue(){
    return this->value;
}



template<class T>
LinkedList<T>::LinkedList(){
    this->head = 0;
    this->tail = 0;
}

template<class T>
LinkedList<T>::~LinkedList(){
    while(!this->isEmpty()){
        this->popFromFront();
    }
}

template<class T>
void LinkedList<T>::pushToFront(T val){
    LinkedListNode<T>* nn = new LinkedListNode<T>(val);
    if(this->isEmpty()){
        this->head = nn;
        this->tail = nn;
    } else {
        nn->setNext(this->head);
        this->head->setPrev(nn);
        this->head = nn;
    }
}

template<class T>
void LinkedList<T>::pushToBack(T val){
    LinkedListNode<T>* nn = new LinkedListNode<T>(val);
    if(this->isEmpty()){
        this->head = nn;
        this->tail = nn;
    } else {
        nn->setPrev(this->tail);
        this->tail->setNext(nn);
        this->tail = nn;
    }
}

template<class T>
T LinkedList<T>::popFromFront(){
    T ret = 0;
    if(!this->isEmpty()){
        LinkedListNode<T>* oldHead = this->head;
        ret = oldHead->getValue();
        this->head = oldHead->getNext();
        delete oldHead;
        if(this->head){
            this->head->setPrev(0);
        } else {
            this->tail = 0;
        }
    }
    return ret;
}

template<class T>
T LinkedList<T>::popFromBack(){
    T ret = 0;
    if(!this->isEmpty()){
        LinkedListNode<T>* oldTail = this->tail;
        ret = oldTail->getValue();
        this->tail = oldTail->getPrev();
        delete oldTail;
        if(this->tail){
            this->tail->setNext(0);
        } else {
            this->head = 0;
        }
    }
    return ret;
}

template<class T>
T LinkedList<T>::peekFront(){
    T ret = 0;
    if(!this->isEmpty()){
        ret = this->head->getValue();
    }
    return ret;
}

template<class T>
T LinkedList<T>::peekBack(){
    T ret = 0;
    if(!this->isEmpty()){
        ret = this->tail->getValue();
    }
    return ret;
}

template<class T>
bool LinkedList<T>::deleteNode(T withValue){
    bool found = false;
    LinkedListNode<T>* curr = this->head;
    while(curr && !found){
        if(curr->getValue() == withValue){
            found = true;
            if(curr == this->head){
                this->popFromFront();
            } else if(curr == this->tail){
                this->popFromBack();
            } else {
                //has both prev and next
                curr->getPrev()->setNext(curr->getNext());
                curr->getNext()->setPrev(curr->getPrev());
                delete curr;
            }
        } else {
            curr = curr->getNext();
        }
    }
    return found;
}

template<class T>
bool LinkedList<T>::isEmpty(){
    return this->head == 0;
}

template<class T>
void LinkedList<T>::print(){
    LinkedListNode<T>* curr = this->head;
    std::cout << "Start of linked list:" << std::endl;
    while(curr){
        std::cout << curr->getValue() << std::endl;
        curr = curr->getNext();
    }
    std::cout << "End of linked list." << std::endl;
}

template<class T>
int LinkedList<T>::test(){
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
