#include <iostream>
#include "Queue.h"

using namespace std;



int useQueue(){
    Queue<int>* q = new Queue<int>();

    int ip = 0;
    cout << "===QUEUE===" << endl;
    while(ip != -1){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Choose an option: " << endl;
        cout << "0: print the queue" << endl;
        cout << "1: enqueue to the queue" << endl;
        cout << "2: dequeue the queue" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;
        switch(ip){
        case 0:
            q->print();
            break;
        case 1:
            cout << "Enter value to enqueue: ";
            cin >> ip;
            q->enqueue(ip);
            ip = 1;
            break;
        case 2:
            if(q->isEmpty()){
                cout << "Nothing to dequeue" << endl;
            } else {
                ip = q->deque();
                cout << "dequeued " << ip << endl;
                ip = 2;
            }
            break;
        }
    }


    return 0;
}
