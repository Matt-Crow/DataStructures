#include <iostream>

using namespace std;

struct node {
    int data;
    node* prev;
    node* next;
};

struct linkedList {
    node* head;
    node* tail;
};

linkedList* newLinkedList();
void push(linkedList* dll, int val);
bool deleteNode(linkedList* dll, int index);
bool deleteNode(linkedList* dll, int index, bool fromHead);
void print(linkedList* dll);


int main(){
    linkedList* dll = newLinkedList();

    for(int i = 0; i < 10; i++){
        push(dll, i);
    }
    print(dll);

    deleteNode(dll, 1, true);
    print(dll);

    return 0;
}

linkedList* newLinkedList(){
    linkedList* ret = new linkedList;
    ret->head = 0;
    ret->tail = 0;
    return ret;
}

void push(linkedList* dll, int val){
    node* newNode = new node;
    newNode->next = 0;
    newNode->prev = dll->tail;
    newNode->data = val;

    if(dll->tail){
        dll->tail->next = newNode;
    }

    dll->tail = newNode;

    if(!dll->head){
        dll->head = dll->tail;
    }
}

bool deleteNode(linkedList* dll, int index){
    return deleteNode(dll, index, true);
}

bool deleteNode(linkedList* dll, int index, bool fromHead){
    // index starts at 1 ... OK
    bool found = false;
    int i = 1;
    node* current = (fromHead) ? dll->head : dll->tail;
    while(current && !found){
        if(i == index){
            found = true;
            if(current->prev){
                current->prev->next = current->next;
            } else {
                dll->head = current->next;
            }
            if(current->next){
                current->next->prev = current->prev;
            } else {
                dll->tail = current->prev;
            }
        }
        current = (fromHead) ? current->next : current->prev;
        i++;
    }

    return found;
}

void print(linkedList* dll){
    node* current = dll->head;
    while(current){
        cout << current->data << endl;
        current = current->next;
    }
}

