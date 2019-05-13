#include <iostream>

using namespace std;

struct TravelInfo{
    int from;
    int to;
    int dist;
};

struct frame{
    frame* next;
    TravelInfo* value;
};

void push(frame* &top, TravelInfo* val);

frame* pop(frame* &top);

void printFrame(frame* top);

void siftUp(TravelInfo* heap[], int length, int firstEmptyIdx, TravelInfo* i);

TravelInfo* siftDown(TravelInfo* heap[], int firstEmptyIdx);


int main(){
    //forget it, he doesn't give us the algorithm
    int adjMatrix[3][3] = {
        {
            0, 1, 2
        },
        {
            1, 0, 1
        },
        {
            2, 1, 0
        }
    };
    bool visited[3] = {false};
    frame* travelLog = 0;
    int heap[9] = {0};
    int start = 0;
    int end = 2;

    TravelInfo* t = new TravelInfo;
    t->from = start;
    t->to = start;
    t->dist = 0;
    push(travelLog, t);
    //add TravelInfo for each path from 0 to something onto the heap,
    //set visited for 0 to true
    //sift down the heap, put that in travel log
    //something about adding the accumulated distance to each info in heap?
    return 0;
}

void push(frame* &top, TravelInfo* val){
    frame* newFrame = new frame;
    newFrame->next = top;
    newFrame->value = val;
    top = newFrame;
    newFrame = 0;
    delete newFrame;
}

frame* pop(frame* &top){
    frame* ret = top;
    if(top->next){
        top = top->next;
        ret->next = 0;
    } else {
        top = 0;
    }
    return ret;
}

void printFrame(frame* top){
    frame* current = top;

    while(current){
        cout << "from " << current->value->from << " to " << current->value->to << ": " << current->value->dist << endl;
        current = current->next;
    }

    delete current;
}

void siftUp(TravelInfo* heap[], int length, int firstEmptyIdx, TravelInfo* i){
    //insert into the heap, keep moving up until the new element's parent is less than it
    if(firstEmptyIdx < length){
        heap[firstEmptyIdx] = i;
        int idx = firstEmptyIdx;
        int parentIdx = (idx - 1) / 2;
        TravelInfo* temp;

        //min heap, so each element's children are larger than it
        while(parentIdx >= 0 && idx != 0 && heap[parentIdx]->dist > heap[idx]->dist){
            temp = heap[idx];
            heap[idx] = heap[parentIdx];
            heap[parentIdx] = temp;
            idx = parentIdx;
            parentIdx = (idx - 1) / 2;
            //print(heap, length);
        }
        temp = 0;
        delete temp;
    } else {
        cout << "Invalid index: " << firstEmptyIdx << endl;
    }
}

TravelInfo* siftDown(TravelInfo* heap[], int firstEmptyIdx){
    //delete topmost element, move smalest element to top
    TravelInfo* ret = 0;
    if(firstEmptyIdx > 0){
        int heapSize = firstEmptyIdx;
        ret = heap[0];
        heap[0] = heap[heapSize - 1]; //last element becomes first
        heapSize--; //technically just deleted last element
        //next, re-sort
        int currIdx = 0;
        int leftIdx = 1;
        int rightIdx = 2;
        TravelInfo* temp;

        while((leftIdx < heapSize && heap[currIdx]->dist > heap[leftIdx]->dist) || (rightIdx < heapSize && heap[currIdx]->dist > heap[rightIdx]->dist)){
            //breadthPrint(heap, heapSize, cout);
            if(heap[leftIdx]->dist > heap[rightIdx]->dist){
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

        temp = 0;
        delete temp;
    }
    return ret;
}
