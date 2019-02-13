#include <iostream>
#include <fstream>

using namespace std;

struct node{
    char* data;
    node* next;
};

node* last(node* head);
node* addNode(node* head, char* value);
node* insertAfter(node* head, char* value);
bool deleteNode(node* head, char value[]);

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

    cout << "Before: " << endl;
    traverse(head);

    char msg[] = {"Example"};
    addNode(head, cStrToPtr(msg));

    cout << "After: " << endl;
    traverse(head);

    deleteNode(head, msg);
    traverse(head);

    return 0;
}

node* last(node* head){
    node* current = head;
    while(current->next){
        current = current->next;
    }
    return current;
}

node* addNode(node* head, char* value){
    node* newNode = new node;
    newNode->data = value;
    newNode->next = 0;
    last(head)->next = newNode;
}

node* insertAfter(node* head, char* value){
    node* oldNext = head->next;
    node* newNext = new node;
    newNext->data = value;
    newNext->next = oldNext;
    head->next = newNext;
}

bool deleteNode(node* head, char value[]){
    bool found = false;
    node* current = head->next;
    int idx;
    bool sameVal;

    while(current->next && !found){
        idx = 0;
        sameVal = true;
        while(value[idx] != '\0' && sameVal){
            sameVal = value[idx] == current->next->data[idx];
            idx++;
        }
        if(sameVal){
            found = true;
            cout<<"here";
            node* temp = current->next->next;
            cout<<current->next;
            current->next = temp;
        }
        current = current->next;

    }

    delete current;

    return found;
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
