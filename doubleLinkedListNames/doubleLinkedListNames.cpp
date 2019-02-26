#include <iostream>
#include <fstream>

using namespace std;

struct node {
    string data;
    node* prev;
    node* next;
};

struct linkedList {
    node* head;
    node* tail;
};

linkedList* newLinkedList();
void push(linkedList* dll, string val);
bool deleteNode(linkedList* dll, string value);

int main(){
    linkedList* dll = newLinkedList();
    ifstream in = ifstream("input.txt");
    string ip;
    bool deleteNext = false;
    while(in >> ip){
        if(ip == "delete"){
            deleteNext = true;
        } else {
            if(deleteNext){
                deleteNode(dll, ip);
                deleteNext = false;
            } else {
                push(dll, ip);
            }
        }
    }
    in.close();

    cout << "Writing to output.txt...";
    ofstream out = ofstream("output.txt");
    node* current = dll->head;
    while(current){
        out << current->data << endl;
        current = current->next;
    }
    out << "=============" << endl;
    current = dll->tail;
    while(current){
        out << current->data << endl;
        current = current->prev;
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

void push(linkedList* dll, string val){
    node* newNode = new node;
    newNode->next = 0; //starts out unconnected
    newNode->prev = 0;
    newNode->data = val;

    if(!dll->head){
        //headless
        dll->head = newNode;
        dll->tail = newNode;
    } else if(dll->head->data > val){
        //less than head
        newNode->next = dll->head;
        dll->head->prev = newNode;
        dll->head = newNode;
    } else if(dll->tail->data < val){
        //bigger than tail
        newNode->prev = dll->tail;
        dll->tail->next = newNode;
        dll->tail = newNode;
    } else {
        node* current = dll->head;
        while(current->data < val){
            current = current->next;
        }

        node* temp = current->prev;
        current->prev = newNode;
        newNode->next = current;
        temp->next = newNode;
        newNode->prev = temp;
    }
}

bool deleteNode(linkedList* dll, string value){
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
