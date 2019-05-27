#include "Stack.h"
#include "StackNode.h"
#include <iostream>

using namespace std;

template <class T>
Stack<T>::Stack()
{
    top = 0;
}

template <class T>
Stack<T>::~Stack()
{
    cascadeDelete(top);
}

template <class T>
void Stack<T>::cascadeDelete(StackNode<T>* node){
    if(node){
        if(node->next){
            cascadeDelete(node->next);
            delete node;
        }
    }
}

template <class T>
bool Stack<T>::isEmpty(){
    return top == 0;
}

template <class T>
void Stack<T>::push(T value){
    StackNode<T>* nn = new StackNode<T>(value);
    nn->next = top;
    top = nn;
}

template <class T>
T Stack<T>::pop(){
    T ret = 0;
    if(top){
        StackNode<T>* temp = top;
        ret = temp->getData();
        top = temp->next;
        delete temp;
    }
    return ret;
}

template <class T>
void Stack<T>::print(){
    StackNode<T>* curr = top;
    while(curr){
        cout << curr->getData() << " ";
        curr = curr->next;
    }
    cout << endl;
}

template <class T>
T Stack<T>::peek(){
    T ret = 0;
    if(top){
        ret = top->getData();
    }
    return ret;
}

template <class T>
int Stack<T>::test(){
    int ip = 0;
    Stack<int>* myStack = new Stack<int>(); //LoL stack on the heap

    do{
        cout << "===STACK===" << endl;
        cout << "0: Print the stack" << endl;
        cout << "1: Push to the stack" << endl;
        cout << "2: Pop the top" << endl;
        cout << "-1: Quit" << endl;
        cout << "Choose an option: ";
        cin >> ip;
        switch(ip){
        case 0:
            myStack->print();
            break;
        case 1:
            cout << "Enter a value to push: ";
            cin >> ip;
            myStack->push(ip);
            ip = 1;
            break;
        case 2:
            if(myStack->isEmpty()){
                cout << "Nothing to pop" << endl;
            } else {
                ip = myStack->pop();
                cout << "Popped " << ip << endl;
                ip = 2;
            }
            break;
        }
    }while(ip >= 0);

    delete myStack;

    return 1;
}
