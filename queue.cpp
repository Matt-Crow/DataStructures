#include <iostream>
#include <fstream>

using namespace std;

struct q{
    q* prev;
    int value;
}; //queue is reserved

void enqueue(q* &rear, int val);
q* dequeue(q* &rear);
void printQueue(q* rear);

ifstream file = ifstream("integers.txt");
int main(){
    q* myQ = new q;
    myQ->prev = 0;

    int i;
    while(file.good()){
        file >> i;
        cout << "read " << i << endl;
        enqueue(myQ, i);
    }
    printQueue(myQ);

    return 0;
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
