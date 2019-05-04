#include <iostream>
#include <fstream>

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


void siftUp(int heap[], int length, int firstEmptyIdx, int i);

Node* newNode(int data);
LinkedList* newLinkedList();
void enq(LinkedList* ll, int);
int deq(LinkedList* ll);
void breadthPrint(int heap[], int length, ostream &output);
//temp
void print(int a[], int len);


int main(){
    int heap[10] = {0};
    for(int i = 1; i < 13; i++){
        siftUp(heap, 10, i - 1, 11 - i);
        //print(heap, 10);
        cout << "After inserting " << i << ":" << endl;
        breadthPrint(heap, 10, cout);
    }
    //Insert 10 values into a min-heap from a file.
    //Display the data, level by level.
    //Then delete 5 items.
    //After each delete, display the heap, level by level.
    return 0;
}

void siftUp(int heap[], int length, int firstEmptyIdx, int i){
    //insert into the heap, keep moving up so that the new element is in its proper place
    if(firstEmptyIdx < length){
        heap[firstEmptyIdx] = i;
        int idx = firstEmptyIdx;
        int parentIdx = (idx - 1) / 2;
        int temp;

        //min heap, so each element's children are larger than it
        while(parentIdx >= 0 && idx != 0 && heap[parentIdx] > heap[idx]){
            temp = heap[idx];
            heap[idx] = heap[parentIdx];
            heap[parentIdx] = temp;
            idx = parentIdx;
            parentIdx = (idx - 1) / 2;
            //print(heap, length);
        }
    } else {
        cout << "Invalid index: " << firstEmptyIdx << endl;
    }
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

void enq(LinkedList* ll, int data){
    Node* nn = newNode(data);
    nn->prev = ll->tail;
    if(ll->head){
        ll->tail->next = nn;
    } else {
        ll->head = nn;
    }
    ll->tail = nn;
    nn = 0;
    delete nn;
}
int deq(LinkedList* ll){
    int ret = 0;
    if(ll->head){
        ret = ll->head->data;
        ll->head = ll->head->next;
        if(ll->head){
            ll->head->prev = 0;
        }
    }
    return ret;
}

void breadthPrint(int heap[], int length, ostream &output){
    LinkedList* currLv = newLinkedList();
    int curr = 0;
    enq(currLv, curr);
    while(currLv->head){
        LinkedList* nextLv = newLinkedList();
        while(currLv->head){
            curr = deq(currLv);
            output << heap[curr] << " ";
            if(curr * 2 + 1 < length){
                enq(nextLv, curr * 2 + 1);
            }
            if(curr * 2 + 2 < length){
                enq(nextLv, curr * 2 + 2);
            }
        }

        currLv = nextLv;
        output << endl;
    }
}

//temp
void print(int a[], int len){
    for(int i = 0; i < len; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
