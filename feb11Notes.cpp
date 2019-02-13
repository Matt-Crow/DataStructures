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

    frame* top = new frame;
    top->next = 0;
    top->value = 0;

    for(int i = 1; i <= 5; i++){
        push(top, i);
    }
    printFrame(top);
    cout << "Top is " << pop(top)->value << endl;
    printFrame(top);

    q* rear = new q;
    rear->prev = 0;
    rear->value = 0;

    for(int i = 5; i < 25; i+=5){
        enqueue(rear, i);
    }
    printQueue(rear);

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
        //prevent deleting base
        frame* ret = top;
        top = top->next;
    }
    return ret; //can't do return top
}

void printFrame(frame* top){
    frame* current = top;
    while(current->next){
        //this way it won't print the base
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

    if(ret->prev){
        //don't delete rear?

    }

    return ret;
}
void printQueue(q* rear){
    q* current = rear;
    cout << "LAST" << endl;
    while(current->prev){
        //skip head
        cout << current->value << endl;
        current = current->prev;
    }
    cout << "FIRST" << endl;
}
