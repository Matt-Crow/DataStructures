#include <iostream>
#include <fstream>

using namespace std;

//used for breadthPrint
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
int siftDown(int heap[], int firstEmptyIdx);

//used for breadthPrint
Node* newNode(int data);
LinkedList* newLinkedList();
void enq(LinkedList* ll, int);
int deq(LinkedList* ll);

void breadthPrint(int heap[], int length, ostream &output);


int main(){
    ifstream in = ifstream("input.txt");
    int ip;
    int fileSize = 0;

    while(in >> ip){
        fileSize++;
    }
    in.clear();
    in.seekg(0, ios::beg);

    int maxHeapSize = fileSize;
    int heapSize = 0;
    int heap[maxHeapSize] = {0};

    while(in >> ip){
        siftUp(heap, maxHeapSize, heapSize, ip);
        heapSize++;
        cout << "After inserting " << ip << ":" << endl;
        breadthPrint(heap, maxHeapSize, cout);
    }
    cout << "Heap is: " << endl;
    breadthPrint(heap, maxHeapSize, cout);

    int d;
    for(int i = 0; i < 5; i++){
        d = siftDown(heap, heapSize);
        cout << "After deleting " << d << ":" << endl;
        heapSize--;
        breadthPrint(heap, heapSize, cout);
    }

    return 0;
}


void siftUp(int heap[], int length, int firstEmptyIdx, int i){
    //insert into the heap, keep moving up until the new element's parent is less than it
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
int siftDown(int heap[], int firstEmptyIdx){
    //delete topmost element, move smalest element to top
    int ret = 0;
    if(firstEmptyIdx > 0){
        int heapSize = firstEmptyIdx;
        ret = heap[0];
        heap[0] = heap[heapSize - 1]; //last element becomes first
        heapSize--; //technically just deleted last element
        //next, re-sort
        int currIdx = 0;
        int leftIdx = 1;
        int rightIdx = 2;
        int temp;

        while((leftIdx < heapSize && heap[currIdx] > heap[leftIdx]) || (rightIdx < heapSize && heap[currIdx] > heap[rightIdx])){
            //breadthPrint(heap, heapSize, cout);
            if(heap[leftIdx] > heap[rightIdx]){
                temp = heap[rightIdx];
                heap[rightIdx] = heap[currIdx];
                heap[currIdx] = temp;
                currIdx = rightIdx;
            } else {
                temp = heap[leftIdx];
                heap[leftIdx] = heap[currIdx];
                heap[currIdx] = temp;
                currIdx = leftIdx;
            }
            leftIdx = currIdx * 2 + 1;
            rightIdx = currIdx * 2 + 2;
        }
    }
    return ret;
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
