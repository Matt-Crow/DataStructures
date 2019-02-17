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
        cout << "read " << i << endl;
        enqueue(myQ, i);
    }
    printQueue(myQ);
    cout << endl;

    q** last = &myQ;
    int check;

    int j = 0;
    while(getHead(myQ) != *last){
        check = dequeue(myQ)->value;
        cout << last << ":" << myQ->prev << endl;

        cout << "removing " << check << endl;
        if(check >= 0){
            enqueue(myQ, check);
            cout << "shoving it back in" << endl;
        }
        printQueue(myQ);
        cout << endl;
        j++;
        if(j == 15){
            break;
        }
    }

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
