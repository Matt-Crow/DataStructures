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
void mergeSort(LinkedList* ll);
void print(int a[], int length);

int useMergeSort(){
    LinkedList* ll = newLinkedList();
    for(int i = 0; i < 10; i++){
        push(ll, i);
    }
    cout << "Before: " << endl;
    print(ll);

    mergeSort(ll);
    return 0;
}

void mergeSort(LinkedList* ll){
    if(ll && ll->head && length(ll) > 1){
        cout << "Outside, ret is " << split(ll->head) << endl;
        LinkedList** parts = split(ll->head);
        cout << "Parts[0]:" << endl;
        cout << parts;
        print(parts[0]);
        mergeSort(parts[0]);

        mergeSort(parts[1]);
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

    cout << "List 1: " << endl;
    print(ret[0]);
    cout << "List 2: " << endl;
    print(ret[1]);

    cout << "In function, ret is " << ret << endl;
    return ret;
}

void merge(int a[], int start, int end, int origLength){
    int middle = (end - start) / 2 + start;
    // if I did (start + end) / 2, this could excede max int size

    int b[origLength];
    for(int i = 0; i < origLength; i++){
        b[i] = a[i];
    }
    int i = start; //start of "first array"
    int j = middle + 1; //start of "second array"
    int k = start; //current index of "merged array"

    cout << "Merging " << i << " " << j << " " << k << endl;
    print(a, origLength);
    while(i <= middle && j <= end){

        if(a[i] <= a[j]){
            b[k] = a[i];
            i++;
        } else {
            b[k] = a[j];
            j++;
        }
        k++;
        print(b, origLength);
    }
    while(i <= middle){
        b[k] = a[i];
        i++;
        k++;
    }
    while(j <= end){
        b[k] = a[j];
        j++;
        k++;
    }


    for(int i = start; i < end; i++){
        a[i] = b[i];
    }
}

void mergeSort(int a[], int start, int end, int origLength){
    if(start < end){
        int mid = (end - start) / 2 + start;
        cout << start << " " << end << endl;
        mergeSort(a, start, mid, origLength);
        mergeSort(a, mid + 1, end, origLength);
        merge(a, start, end, origLength);
    }
}

void mergeSort(int a[], int length){
    mergeSort(a, 0, length - 1, length);
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
