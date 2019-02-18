#include <iostream>
#include <fstream>

using namespace std;

struct q{
    q* prev;
    int value;
}; //queue is reserved

q* getHead(q* rear);
void enqueue(q* &rear, int val);
q* dequeue(q* &rear);
void printQueue(q* rear);

ifstream file = ifstream("integers.txt");
int main(){
    q* myQ = 0; //need to remember this DON'T DO new q!!!

    int i;
    while(file.good()){
        file >> i;
        enqueue(myQ, i);
    }
    cout << "Before filtering: " << endl;
    printQueue(myQ);
    cout << endl;

    q* newHead = 0;
    //the address of the first element reinserted into myQ.
    //note that I am not using it as a queue, but just as an address.

    int check;
    while(getHead(myQ) != newHead){
        check = dequeue(myQ)->value;

        if(check >= 0){
            enqueue(myQ, check);

            if(!newHead){
                //if this is the first thing reinserted into the queue,
                //set the newHead equal to the end of the queue,
                //as that is where we want to stop
                newHead = myQ;
            }
        }
    }

    cout << "After: " << endl;
    printQueue(myQ);
    cout << endl;

    return 0;
}

q* getHead(q* rear){
    q* ret = rear;

    while(ret && ret->prev){
        ret = ret->prev;
    }

    return ret;
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
        cout << " (" << rear->value << ") <- ";
    }
}
