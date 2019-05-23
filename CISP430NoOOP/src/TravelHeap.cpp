#include <iostream>
#include "TravelHeap.h"
#include "../findPath.h"

using namespace std;

/*
This is a min-heap, so the smallest element is at the top
*/

TravelHeap::TravelHeap(int capacity)
{
    this->capacity = capacity;
    this->firstEmptyIdx = 0;
    this->heap = (travelInfo**)(malloc(sizeof(travelInfo*) * capacity));
}

TravelHeap::~TravelHeap()
{
    cout << "Heap deleted" << endl;
}

bool TravelHeap::siftUp(travelInfo* t){
    bool canSiftUp = t->valid && this->firstEmptyIdx < this->capacity;

    if(canSiftUp){
        this->heap[this->firstEmptyIdx] = t;
        this->firstEmptyIdx++;

        //swap it into place
        int currIdx = this->firstEmptyIdx - 1;
        /*
        Since the heap is a tree,
        if the parent is at index X,
        then each of its children are
        at indexes 2X + 1 and 2X + 2,
        so integer division can reverse
        that calculation
        */
        int parentIdx = (currIdx - 1) / 2;
        travelInfo* temp = 0;
        while(parentIdx >= 0 && currIdx != 0 && this->heap[parentIdx]->dist > this->heap[currIdx]->dist){
            temp = this->heap[parentIdx];
            this->heap[parentIdx] = this->heap[currIdx];
            this->heap[currIdx] = temp;
            currIdx = parentIdx;
            parentIdx = (currIdx - 1) / 2;
        }
    }
    return canSiftUp;
}

travelInfo* TravelHeap::siftDown(){
    travelInfo* ret = 0;
    if(this->firstEmptyIdx > 0){
        ret = this->heap[0];
        this->heap[0] = this->heap[firstEmptyIdx - 1]; //last element becomes first;
        this->firstEmptyIdx--;

        //re-sort
        int curr = 0;
        int left = 2 * curr + 1;
        int right = 2 * curr + 2;
        travelInfo* temp = 0;
        while((left < this->firstEmptyIdx && this->heap[curr]->dist > this->heap[left]->dist) || (right < this->firstEmptyIdx && this->heap[curr]->dist > this->heap[right]->dist)){
            if(this->heap[left]->dist < this->heap[right]->dist){
                //left is smaller, so swap with that
                temp = this->heap[left];
                this->heap[left] = this->heap[curr];
                this->heap[curr] = temp;
                curr = left;
            } else {
                temp = this->heap[right];
                this->heap[right] = this->heap[curr];
                this->heap[curr] = temp;
                curr = right;
            }
            left = 2 * curr + 1;
            right = 2 * curr + 2;
        }
    }
    return ret;
}

void TravelHeap::print(){
    int height = 0;
    int column = 0;
    int colWidth = 1;

    cout << "HEIGHT " << height << endl;
    for(int i = 0; i < this->firstEmptyIdx; i++){

        printTravelInfo(this->heap[i]);
        cout << endl;
        column++;
        if(column >= colWidth){
            colWidth *= 2;
            column = 0;
            height++;
            cout << "HEIGHT " << height << endl;
        }
    }
}
