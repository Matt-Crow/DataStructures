#include <stdio.h>
#include <iostream>
#include "stack.h"

template<class T>
StackNode<T>::StackNode(T val){
    this->next = 0;
    this->value = val;
}

template<class T>
StackNode<T>::~StackNode(){
    std::cout << "Delete " << this->value << std::endl;
}

template<class T>
void StackNode<T>::setNext(StackNode<T>* next){
    this->next = next;
}

template<class T>
StackNode<T>* StackNode<T>::getNext(){
    return this->next;
}

template<class T>
T StackNode<T>::getValue(){
    return this->value;
}



template<class T>
Stack<T>::Stack(){
    this->top = 0;
}

template<class T>
Stack<T>::~Stack(){
    StackNode<T>* curr = this->top;
    StackNode<T>* temp;
    while(curr){
        temp = curr->getNext();
        delete curr;
        curr = temp;
        temp = 0;
    }
    this->top = 0;
}

template<class T>
void Stack<T>::push(T val){
    StackNode<T>* newTop = new StackNode<T>(val);
    newTop->setNext(this->top);
    this->top = newTop;
}

template<class T>
T Stack<T>::pop(){
    if(this->isEmpty()){
        return 0;
    }
    StackNode<T>* oldTop = this->top;
    T ret = oldTop->getValue();
    this->top = oldTop->getNext();
    oldTop->setNext(0);
    delete oldTop;

    return ret;
}

template<class T>
T Stack<T>::peek(){
    if(this->isEmpty()){
        return 0;
    }
    return this->top->getValue();
}

template<class T>
void Stack<T>::print(){
    StackNode<T>* curr = this->top;
    std::cout << "Top of the stack:" << std::endl;
    while(curr){
        std::cout << curr->getValue() << std::endl;
        curr = curr->getNext();
    }
    std::cout << "Bottom of the stack" << std::endl;
}

template<class T>
bool Stack<T>::isEmpty(){
    return this->top == 0;
}

template <class T>
int Stack<T>::test(){
    int ip = 0;
    Stack<int>* myStack = new Stack<int>(); //LoL stack on the heap

    do{
        std::cout << "===STACK===" << std::endl;
        std::cout << "0: Print the stack" << std::endl;
        std::cout << "1: Push to the stack" << std::endl;
        std::cout << "2: Pop the top" << std::endl;
        std::cout << "-1: Quit" << std::endl;
        std::cout << "Choose an option: ";
        std::cin >> ip;
        switch(ip){
        case 0:
            myStack->print();
            break;
        case 1:
            std::cout << "Enter a value to push: ";
            std::cin >> ip;
            myStack->push(ip);
            ip = 1;
            break;
        case 2:
            if(myStack->isEmpty()){
                std::cout << "Nothing to pop" << std::endl;
            } else {
                ip = myStack->pop();
                std::cout << "Popped " << ip << std::endl;
                ip = 2;
            }
            break;
        }
    }while(ip >= 0);

    delete myStack;

    return 0;
}

template class Stack<int>;
