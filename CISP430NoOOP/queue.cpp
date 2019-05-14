#include <iostream>

using namespace std;

template <typename T>
struct queue{
    queue<T>* prev;
    queue<T>* next;
    T value;
};

template <typename T>
void enqueue(queue<T>* &head, queue<T>* &tail, T value);

template <typename T>
T dequeue(queue<T>* &head, queue<T>* &tail);

template <typename T>
void print(queue<T>* head, ostream &out);

int useQueue(){
    queue<int>* head = 0;
    queue<int>* tail = 0;
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
            print(head, cout);
            break;
        case 1:
            cout << "Enter value to enqueue: ";
            cin >> ip;
            enqueue(head, tail, ip);
            ip = 1;
            break;
        case 2:
            if(head == 0){
                cout << "Nothing to dequeue" << endl;
            } else {
                ip = dequeue(head, tail);
                cout << "dequeued " << ip << endl;
                ip = 2;
            }
            break;
        }
    }


    return 0;
}

template <typename T>
void enqueue(queue<T>* &head, queue<T>* &tail, T value){
    queue<T>* newQ = new queue<T>;
    newQ->value = value;
    newQ->prev = tail;
    newQ->next = 0;

    if(tail){
        tail->next = newQ;
    }
    tail = newQ;

    if(!head){
        head = newQ;
    }

    newQ = 0;
    delete newQ;
}

template <typename T>
T dequeue(queue<T>* &head, queue<T>* &tail){
    T ret = 0;
    if(head){
        ret = head->value;
        if(head == tail){
            //only one element
            head = 0;
            tail = 0;
        } else {
            head = head->next;
        }
    }
    return ret;
}

template <typename T>
void print(queue<T>* head, ostream &out){
    queue<T>* curr = head;
    out << "Queue is: ";
    while(curr){
        out << curr->value << " ";
        curr = curr->next;
    }
    out << endl;
    delete curr;
}
