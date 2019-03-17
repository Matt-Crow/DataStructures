#include <iostream>

using namespace std;

struct frame{
    frame* next;
    int value;
};

struct q{
    q* prev;
    int value;
}; //queue is reserved

void push(frame* &top, int val);
frame* pop(frame* &top);
void printFrame(frame* top);

void enqueue(q* &rear, int val);
q* dequeue(q* &rear);
void printQueue(q* rear);

int main(){
    //for stack, need to pass top as node*&
    frame* top = 0;

    for(int i = 0; i < 4; i++){
        cout << "Pushing " << i << endl;
        push(top, i);
        printFrame(top);
    }

    while(top){
        cout << "Pop top " << pop(top)->value << endl;
        printFrame(top);
    }

    //###queues#####################################################

    q* rear = 0; //can have 0 element queue

    for(int i = 0; i < 5; i++){
        enqueue(rear, i);
    }
    printQueue(rear);

    while(rear){
        cout << "Dequeing " << dequeue(rear)->value << endl;
        printQueue(rear);
    }

    return 0;
}

void push(frame* &top, int val){
    frame* newFrame = new frame;
    newFrame->next = top;
    newFrame->value = val;
    top = newFrame;
}

frame* pop(frame* &top){
    frame* ret = top;
    if(top->next){
        top = top->next;
        ret->next = 0;
    } else {
        top = 0;
    }
    return ret;
}

void printFrame(frame* top){
    frame* current = top;

    while(current){
        cout << current->value << endl;
        current = current->next;
    }
}

void enqueue(q* &rear, int val){
    q* newRear = new q;
    newRear->value = val;
    newRear->prev = rear;
    rear = newRear;
}

q* dequeue(q* &rear){
    q* ret = rear;
    q* current = rear;

    if(!rear->prev){
        ret = rear;
        rear = 0;
    }

    while(current->prev){
        if(current->prev->prev == 0){
            ret = current->prev;
            current->prev = 0;
        } else {
            current = current->prev;
        }
    }

    return ret;
}
void printQueue(q* rear){
    //awesome recursive printQueue
    if(rear){
        if(rear->prev){
            printQueue(rear->prev);
        }
        cout << rear->value << " <- ";
    }
}
