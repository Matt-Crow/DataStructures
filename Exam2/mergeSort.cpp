#include <iostream>

using namespace std;

struct Node {
    Node* prev;
    Node* next;
    int data;
};

struct LinkedList {
    Node* head;
    Node* tail;
};

Node* newNode(int data);
LinkedList* newLinkedList();
void push(LinkedList* ll, int data);
void print(LinkedList* ll);
void print(Node* n);
int length(LinkedList* ll);
int length(Node* n);

LinkedList** split(Node* head);
LinkedList* merge(LinkedList* a, LinkedList* b);
void mergeSort(LinkedList*&ll);



int useMergeSort(){
    LinkedList* ll = newLinkedList();
    for(int i = 0; i < 10; i++){
        push(ll, (i - 3) * (i -5));
    }
    cout << "Before: " << endl;
    print(ll);

    mergeSort(ll);
    cout << "After merge: " << endl;
    print(ll);

    return 0;
}

void mergeSort(LinkedList*&ll){
    if(ll && ll->head && length(ll) > 1){
        LinkedList** parts = split(ll->head);
        mergeSort(parts[0]);
        mergeSort(parts[1]);
        ll = merge(parts[0], parts[1]);
    }
}

LinkedList** split(Node* head){
    LinkedList** ret = new LinkedList*;
    ret[0] = newLinkedList();
    ret[1] = newLinkedList();
    int numItems = length(head);
    int mid = numItems / 2;

    Node* current = head;
    int i = 0;
    for(; i < mid; i++){
        push(ret[0], current->data);
        current = current->next;
    }
    for(; i < numItems; i++){
        push(ret[1], current->data);
        current = current->next;
    }
    /*
    cout << "List 1: " << endl;
    print(ret[0]);
    cout << "List 2: " << endl;
    print(ret[1]);
    */
    return ret;
}

LinkedList* merge(LinkedList* a, LinkedList* b){
    LinkedList* ret = newLinkedList();
    Node* h1 = a->head;
    Node* h2 = b->head;
    while(h1 || h2){
        //cout << "Merging..." << endl;
        if(h1 && h2){
            if(h1->data > h2->data){
                push(ret, h2->data);
                h2 = h2->next;
            } else {
                push(ret, h1->data);
                h1 = h1->next;
            }
        } else {
            if(h1){
                push(ret, h1->data);
                h1 = h1->next;
            } else {
                push(ret, h2->data);
                h2 = h2->next;
            }
        }
        //print(h1);
        //print(h2);
    }
    return ret;
}

Node* newNode(int data){
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

void push(LinkedList* ll, int data){
    Node* nn = newNode(data);
    if(ll->head && ll->tail){
        //has head and tail, so append to end
        ll->tail->next = nn;
        nn->prev = ll->tail;
        ll->tail = nn;
    } else {
        //either no head, or no tail.
        //in this implementation, that means no elements.
        ll->head = nn;
        ll->tail = nn;
    }
}

void print(LinkedList* ll){
    print(ll->head);
}

void print(Node* n){
    Node* current = n;
    int i = 1;

    while(current){
        cout << i << ": " << current->data << endl;
        current = current->next;
        i++;
    }
}

int length(LinkedList* ll){
    return length(ll->head);
}

int length(Node* n){
    if(!n){
        return 0;
    } else {
        return 1 + length(n->next);
    }
}
