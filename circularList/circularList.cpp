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
bool deleteNode(linkedList* dll, int num);
void print(linkedList* dll);

int main(){
    linkedList* dll = newLinkedList();
    ifstream in = ifstream("input.txt");
    string ip;
    while(in >> ip){
        push(dll, ip);
    }
    in.close();

    print(dll);
    cout << "=====" << endl;
    deleteNode(dll, 1);
    print(dll);

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
    newNode->next = dll->head;
    newNode->prev = dll->tail;
    newNode->data = val;

    if(!dll->head){
        dll->head = newNode;
        dll->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        dll->head->prev = newNode;
        dll->tail->next = newNode;
        dll->tail = newNode;
    }
}

bool deleteNode(linkedList* dll, int num){
    //recursive
    if(num <= 0){
        //done deleting
        return true;
    }else if(dll->head != dll->tail){
        //at least 2 nodes
        dll->head = dll->head->next;
        dll->head->prev = dll->tail;
        dll->tail->next = dll->head;
        return deleteNode(dll, num - 1);
    }else if(dll->head){
        //only one node
        dll->head = 0;
        dll->tail = 0;
        return deleteNode(dll, num - 1);
    }else{
        //no nodes
        return false;
    }
}

void print(linkedList* dll){
    node* current = dll->head;
    int i = 1;
    bool printedHead = false;
    //how print last one?
    while(current && !(current == dll->head && printedHead)){
        printedHead = true;
        cout << i << ": " << current->data << endl;
        current = current->next;
        i++;
    }
}
