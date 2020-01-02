#include <iostream>

using namespace std;

template <typename T>
struct node {
    node<T>* prev;
    node<T>* next;
    T value;
};

template <typename T>
struct linkedList{
    node<T>* head;
    node<T>* tail;
};

template <typename T>
node<T>* newNode(T value);

template <typename T>
linkedList<T>* newLinkedList();

template <typename T>
void push(linkedList<T>* ll, T value);

template <typename T>
void enqueue(linkedList<T>* ll, T value);

template <typename T>
T pop(linkedList<T>* ll);

template <typename T>
T dequeue(linkedList<T>* ll);

template <typename T>
bool deleteNode(linkedList<T>* ll, T withValue);

template <typename T>
void print(linkedList<T>* ll, ostream &out);



int useLinkedList(){
    linkedList<int>* ll = newLinkedList<int>();
    int ip = 0;
    cout << "===LINKED LIST===" << endl;
    while(ip != -1){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Choose an option: " << endl;
        cout << "0: print the linked list" << endl;
        cout << "1: push to the end of the linked list" << endl;
        cout << "2: enqueue to the start of the linked list" << endl;
        cout << "3: pop the last element of the linked list" << endl;
        cout << "4: dequeue the first element of the linked list" << endl;
        cout << "5: delete a node with a given value" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;
        switch(ip){
        case 0:
            print(ll, cout);
            break;
        case 1:
            cout << "Enter value to push to the linked list: ";
            cin >> ip;
            push(ll, ip);
            ip = 1;
            break;
        case 2:
            cout << "Enter value to enqueue to the linked list: ";
            cin >> ip;
            enqueue(ll, ip);
            ip = 2;
            break;
        case 3:
            if(ll->head == 0){
                cout << "Nothing to pop" << endl;
            } else {
                ip = pop(ll);
                cout << "Popped " << ip << endl;
                ip = 3;
            }
            break;
        case 4:
            if(ll->head == 0){
                cout << "Nothing to dequeue" << endl;
            } else {
                ip = dequeue(ll);
                cout << "Dequeued " << ip << endl;
                ip = 4;
            }
            break;
        case 5:
            cout << "Enter number to delete: ";
            cin >> ip;
            bool success = deleteNode(ll, ip);
            if(success){
                cout << "Deleted " << ip << endl;
            } else {
                cout << ip << " is not in the linked list" << endl;
            }
            ip = 5;
            break;
        }
    }

    ll = 0;
    delete ll;

    return 0;
}



template <typename T>
node<T>* newNode(T value){
    node<T>* ret = new node<T>;
    ret->prev = 0;
    ret->next = 0;
    ret->value = value;
    return ret;
}

template <typename T>
linkedList<T>* newLinkedList(){
    linkedList<T>* ret = new linkedList<T>;
    ret->head = 0;
    ret->tail = 0;
    return ret;
}

template <typename T>
void push(linkedList<T>* ll, T value){
    node<T>* nn = newNode(value);
    if(ll->tail){
        ll->tail->next = nn;
        nn->prev = ll->tail;
        ll->tail = nn;
    } else {
        ll->head = nn;
        ll->tail = nn;
    }
    nn = 0;
    delete nn;
}

template <typename T>
void enqueue(linkedList<T>* ll, T value){
    node<T>* nn = newNode(value);
    if(ll->head){
        ll->head->prev = nn;
        nn->next = ll->head;
        ll->head = nn;
    } else {
        ll->head = nn;
        ll->tail = nn;
    }
    nn = 0;
    delete nn;
}

template <typename T>
T pop(linkedList<T>* ll){
    T ret = 0;
    if(ll->head){
        ret = ll->tail->value;
        ll->tail = ll->tail->prev;
        if(ll->tail){
            ll->tail->next = 0;
        } else {
            //popped the only element
            ll->head = 0;
        }
    }
    return ret;
}

template <typename T>
T dequeue(linkedList<T>* ll){
    T ret = 0;
    if(ll->head){
        ret = ll->head->value;
        ll->head = ll->head->next;
        if(ll->head){
            ll->head->prev = 0;
        } else {
            ll->head = 0;
        }
    }
    return ret;
}

template <typename T>
bool deleteNode(linkedList<T>* ll, T withValue){
    bool deleted = false;
    node<T>* curr = ll->head;
    while(curr && !deleted){
        if(curr->value == withValue){
            if(curr == ll->head){
                deleted = true;
                ll->head = ll->head->next;
                if(ll->head){
                    ll->head->prev = 0;
                }
            }
            if(curr == ll->tail){
                deleted = true;
                ll->tail = ll->tail->prev;
                if(ll->tail){
                    ll->tail->next = 0;
                }
            }
            //at this point, if there is only one node, both are set to 0
            if(!deleted){
                //hasn't been deleted yet, as it isn't head nor tail
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                deleted = true;
            }
        } else {
            curr = curr->next;
        }
    }
    curr = 0;
    delete curr;
    return deleted;
}

template <typename T>
void print(linkedList<T>* ll, ostream &out){
    node<T>* curr = ll->head;
    out << "Linked list is: ";
    while(curr){
        out << curr->value << " ";
        curr = curr->next;
    }
    out << endl;
    delete curr;
}
