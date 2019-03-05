#include <iostream>
#include <fstream>

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
bool deleteNode(linkedList* dll, int value);
void print(linkedList* dll);


int main(){
    linkedList* dll = newLinkedList();
    ifstream in = ifstream("input.txt");
    int ip;
    bool success;

    while(in.good()){
        in >> ip;
        push(dll, ip);
    }
    in.close();

    do{
        print(dll);
        cout << "Enter a number to delete: ";
        cin >> ip;
    } while(deleteNode(dll, ip));

    cout << "Writing to output.txt...";
    ofstream out = ofstream("output.txt");
    node* current = dll->head;
    while(current){
        out << current->data << endl;
        current = current->next;
    }
    out.close();

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

bool deleteNode(linkedList* dll, int value){
    bool found = false;
    node* current = dll->head;
    while(current && !found && current->data <= value){
        if(current->data == value){
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
        current = current->next;
    }

    return found;
}

void print(linkedList* dll){
    node* current = dll->head;
    int i = 1;
    while(current){
        cout << i << ": " << current->data << endl;
        current = current->next;
        i++;
    }
}
