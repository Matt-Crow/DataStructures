#include <iostream>

using namespace std;

struct node {
    int value;
    node* next;
};
node* spawnNode(node* prev, int val);
void print(node* head);
void del(node* head);

int main(){
    int ip = 1;
    node* head = new node;
    head->next = nullptr;
    head->value = -1;
    node* current = head;
    while(ip > 0){
        cout << "Enter a positive number: ";
        cin >> ip;
        if(ip > 0){
            current = spawnNode(current, ip);
        }
    }
    print(head);
    del(head);

    return 0;
}

node* spawnNode(node* prev, int i){
    node* ret = new node;
    ret->next = 0;
    ret->value = i;
    prev->next = ret;
    return ret;
}

void print(node* head){
    node* current = head;
    while(current){
        cout << current->value << endl;
        current = current->next;
    }
    delete current;
}

void del(node* head){
    if(head->next){
        del(head->next);
    }
    cout << "Deleting " << head->value << endl;
    delete head;
}
