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

char* cStrToPtr(char cStr[]); //from previous assignment
int length(char cStr[]);

int main(){
    node* head = readFile();
    traverse(head);

    splitAndMerge(head);
    return 0;
}

node* readFile(){
    ifstream file = ifstream("input.txt");
    node* head = new node;
    head->next = 0;

    node* current = head;

    char data[100];
    while(file.good()){
        file >> data;
        current->data = cStrToPtr(data);
        if(file.good()){
            current->next = new node;
            current = current->next;
            current->next = 0;
        }
    }

    return head;
}

void traverse(node* head){
    node* current = head;
    int i = 1;
    while(current->next != 0){
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
    node* current = head;
    node* splitCurrents[2] = {list1Head, list2Head};

    while(current->next != 0){
        splitCurrents[i%2]->next = current;
        current = current->next;
        splitCurrents[i%2] = splitCurrents[i%2]->next;
        i++;
    }
    traverse(list1Head);
    traverse(list2Head);
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
