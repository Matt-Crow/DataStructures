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

void print(TravelInfo* heap[], int len);
void print(TravelInfo* t);
void print(bool a[], int len);

const int MATRIX_SIZE = 5;

int main(){
    /*
    Djdkstra's algorithm:

    Create an adjacency matrix, a 2-d array which records the distance between nodes
    ex. the distance between nodes A and B is adjMatrix[A][B] or adjMatrix[B][A] it doesn't matter which

    create a boolean array that keeps track of which nodes we have visited

    create a stack that keeps track of our path thus far
    create a min heap that keeps track of points adjacent to all point's we've visited thus far

    repeat until we are at the end point:
        push each path from our current point to the heap, adding the distance of the topmost path on the stack to the new paths' distance
        sift down from the heap until we find a path that starts at a place we haven't visited
        push that path to the stack
    */
    int adjMatrix[MATRIX_SIZE][MATRIX_SIZE] = {
        {
            0, 2, 0, 6, 0
        },
        {
            2, 0, 3, 5, 5
        },
        {
            0, 3, 0, 0, 7
        },
        {
            6, 5, 0, 0, 9
        },
        {
            0, 5, 7, 9, 0
        }
    };
    bool visited[MATRIX_SIZE] = {false};
    frame* travelLog = 0;
    TravelInfo* heap[MATRIX_SIZE * MATRIX_SIZE] = {0};
    int start = 0;
    int end = 4;
    int idx = 0;// heap idx

    int currentlyAt = start;
    TravelInfo* t = new TravelInfo;
    t->from = start;
    t->to = start;
    t->dist = 0;
    push(travelLog, t);
    visited[start] = true;

    cout << "At " << currentlyAt << endl;
    while(currentlyAt != end){//better loop condition?
        cout << "Visited thus far: " << endl;
        print(visited, MATRIX_SIZE);

        for(int i = 0; i < MATRIX_SIZE; i++){
            //push everything connection from currentlyAt to the heap
            if(adjMatrix[currentlyAt][i] != 0){
                //assuming we haven't visited the destination yet
                t = new TravelInfo;
                t->from = currentlyAt;
                t->to = i;
                t->dist = adjMatrix[currentlyAt][i] + travelLog->value->dist;
                siftUp(heap, MATRIX_SIZE * MATRIX_SIZE, idx, t);
                idx++;
            }
        }
        cout << "Heap after sifting up is " << endl;
        print(heap, idx);
        do{
            t = siftDown(heap, idx);
            idx--;
        } while(visited[t->to] == true); //do until we find one we haven't visited
        push(travelLog, t); //since this is a min heap, the shortest distance will be the one sifted down
        currentlyAt = travelLog->value->to;
        cout << "Visiting " << currentlyAt << endl;
        visited[currentlyAt] = true;
        cout << "At " << currentlyAt << endl;
        cout << "Travel log is " << endl;
        printFrame(travelLog);
    }
    cout << "Done" << endl;
    while(travelLog){
        t = pop(travelLog)->value;
        if(t->to = currentlyAt){
            t->dist -= adjMatrix[t->from][t->to];
            print(t);
            currentlyAt = t->from;
        }
    }

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

//min heap, so smallest is on top
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

void print(TravelInfo* heap[], int len){
    for(int i = 0; i < len; i++){
        cout << i << ": " << endl;
        print(heap[i]);
    }
}
void print(TravelInfo* t){
    cout << "From " << t->from << " to " << t->to << " is " << t->dist << endl;
}
void print(bool a[], int len){
    for(int i = 0; i < len; i++){
        cout << i << ": " << a[i] << endl;
    }
}
