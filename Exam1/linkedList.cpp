#include <iostream>

using namespace std;

//TODO: make this use templates / classes
struct Node {
    Node* prev;
    Node* next;
    string data;
};

struct LinkedList {
    Node* head;
    Node* tail;
};

Node* newNode(string data);
LinkedList* newLinkedList();

void push(LinkedList* ll, string data);
void print(LinkedList* ll);
bool deleteNode(LinkedList* ll, string data);
bool deleteXNodes(LinkedList* ll, int x);

int useLinkedList(){
    LinkedList* ll = newLinkedList();

    char option = ' ';
    string ip = "";
    int num = 0;

    while(option != 'q'){
        cout << "=================" << endl;
        cout << "a: add node" << endl;
        cout << "l: list nodes" << endl;
        cout << "d: delete a node" << endl;
        cout << "x: delete many nodes" << endl;
        cout << "q: quit" << endl;
        cout << "=================" << endl;
        cin >> option;
        switch(option){
        case 'a':
            cout << "Enter node data: ";
            cin >> ip;
            push(ll, ip);
            cout << "Pushed " << ip << endl;
            break;
        case 'l':
            print(ll);
            break;
        case 'd':
            cout << "Enter node to delete: ";
            cin >> ip;
            if(deleteNode(ll, ip)){
                cout << "deleted " << ip << endl;
            } else {
                cout << ip << " is not in the list" << endl;
            }
            break;
        case 'x':
            cout << "Enter how many nodes to delete: ";
            cin >> num;
            if(deleteXNodes(ll, num)){
                cout << num << " nodes were deleted" << endl;
            } else {
                cout << "There aren't " << num << " nodes in the list, so I just deleted all of them" << endl;
            }
            break;
        case 'q':
            cout << "Byeeee" << endl;
            break;
        }
    }

    return 0;
}

Node* newNode(string data){
    Node* nn = new Node;
    nn->prev = 0;
    nn->next = 0;
    nn->data = data;
    return nn;
}

LinkedList* newLinkedList(){
    LinkedList* ll = new LinkedList;
    ll->head = 0;
    ll->tail = 0;
    return ll;
}

void push(LinkedList* ll, string data){
    Node* nn = newNode(data);
    if(ll->head && ll->tail){
        //has head and tail, so append to end
        ll->tail->next = nn;
        nn->prev = ll->tail;
        ll->tail = nn;
        //now make it circular
        ll->tail->next = ll->head;
        ll->head->prev = ll->tail;
    } else {
        //either no head, or no tail.
        //in this implementation, that means no elements.
        ll->head = nn;
        ll->tail = nn;
        nn->next = nn;
    }
}

void print(LinkedList* ll){
    Node* current = ll->head;
    bool looped = false;
    int i = 1;
    /*
    since this is circular,
    we need to know when we are on head
    if it has been processed yet
    */
    while(current && !looped){
        cout << i << ": " << current->data << endl;
        current = current->next;
        if(current == ll->head){
            looped = true;
        }
        i++;
    }
}

bool deleteNode(LinkedList* ll, string data){
    bool found = false;
    bool looped = false;
    Node* current = ll->head;
    while(current && !looped && !found){
        if(current->data == data){
            found = true;
            if(current == ll->head && ll->head == ll->tail){
                //one node
                ll->head = 0;
                ll->tail = 0;
            } else if(current == ll->head){
                //change head
                ll->head = ll->head->next;
                ll->head->prev = ll->tail;
                ll->tail->next = ll->head;
            } else if(current == ll->tail){
                //change tail
                ll->tail = ll->tail->prev;
                ll->tail->next = ll->head;
                ll->head->prev = ll->tail;
            } else {
                //somewhere in between
                current->next->prev = current->prev;
                current->prev->next = current->next;
            }
        }
        current = current->next;
        if(current == ll->head){
            looped = true;
        }
    }

    return found;
}

/*
Awesome recursive delete.
deletes the last x Nodes from the LinkedList,
deletes until either x Nodes have been deleted,
or the LinkedList is empty,
returning whether or not it could delete the specified amount.
*/
bool deleteXNodes(LinkedList* ll, int x){
    if(x <= 0){
        return true;
    } else if(ll->head != ll->tail){
        //at least 2 nodes
        ll->tail = ll->tail->prev;
        ll->tail->next = ll->head;
        ll->head->prev = ll->tail;
        return deleteXNodes(ll, x - 1);
    } else if(ll->head){
        //only one node
        ll->head = 0;
        ll->tail = 0;
        return deleteXNodes(ll, x - 1);
    } else {
        //no nodes
        return false;
    }
}
