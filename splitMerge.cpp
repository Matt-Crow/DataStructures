#include <iostream>
#include <fstream>

using namespace std;

struct node{
    char* data;
    node* next;
};

node* readFile();
void traverse(node* head);
void splitAndMerge(node* head);
node* mergeLists(node* head1, node* head2); //merge is a reserved word

char* cStrToPtr(char cStr[]); //from previous assignment
int length(char cStr[]);

int main(){
    node* head = readFile();
    cout << "Original:" << endl;
    traverse(head);

    splitAndMerge(head);
    return 0;
}

node* readFile(){
    ifstream file = ifstream("input.txt");
    node* head = new node;
    head->data = cStrToPtr({"readFile"});
    head->next = 0;

    node* current = head;

    char data[100];
    while(file.good()){
        file >> data;
        current->next = new node;
        current = current->next;
        current->data = cStrToPtr(data);
        current->next = 0;
    }

    return head;
}

void traverse(node* head){
    node* current = head->next; //don't display head;
    int i = 1;
    while(current != 0){
        cout << i << ": " << current->data << endl;
        i++;
        current = current->next;
    }
}

void splitAndMerge(node* head){
    node* list1Head = new node;
    list1Head->next = 0;
    list1Head->data = cStrToPtr({"List 1"});
    node* list2Head = new node;
    list2Head->next = 0;
    list2Head->data =cStrToPtr({"List 2"});

    int i = 0;
    node* current = head->next;
    node* splitCurrents[2] = {list1Head, list2Head};

    while(current != 0){
        splitCurrents[i%2]->next = current;
        splitCurrents[i%2] = splitCurrents[i%2]->next;
        current = current->next;
        splitCurrents[i%2]->next = 0;
        i++;
    }
    cout << "List 1: " << endl;
    traverse(list1Head);

    cout << "List 2: " << endl;
    traverse(list2Head);

    cout << "Merged: " << endl;
    traverse(mergeLists(list1Head, list2Head));
}

node* mergeLists(node* head1, node* head2){
    node* ret = new node;
    ret->data = cStrToPtr({"merged"});
    ret->next = 0;
    node* retCurrent = ret;
    node* lists[] = {head1->next, head2->next}; //skip heads
    int i = 0;
    while(lists[i%2] != 0){
        retCurrent->next = lists[i%2];
        retCurrent = retCurrent->next;
        lists[i%2] = lists[i%2]->next;
        retCurrent->next = 0;              //this is important!
        i++;
    }

    return ret;
}

char* cStrToPtr(char cStr[]){
    char* ret = (char*)malloc(sizeof(char) * (length(cStr) + 1));

    for(int i = 0; i < length(cStr); i++){
        *(ret + i) = *(cStr + i);
    }
    *(ret + length(cStr)) = '\0';

    return ret;
}

int length(char cStr[]){
    int length = 0;
    while(*(cStr + length) != '\0'){
        length++;
    }
    return length;
}
