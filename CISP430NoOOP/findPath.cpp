#include <iostream>
#include <cstring>
#include "findPath.h"
#include "stack.h"
#include "TravelHeap.h"

using namespace std;

int useFindPath(){
    //set up everything
    adjMatrix* m = newMatrix(5);
    TravelHeap* h = new TravelHeap(25);
    travelLog* log = 0;
    bool visited[5] = {false};
    int start = 0;
    int end = 4;
    int curr = start;

    for(int i = 0; i < 5; i++){
        if(visited[i]){
            cout << "not set to false" << endl;
        }
    }

    set(m, 0, 1, 1);
    set(m, 0, 2, 2);
    set(m, 0, 3, 3);
    set(m, 0, 4, 4);
    set(m, 1, 2, 1);
    set(m, 1, 3, 2);
    set(m, 1, 4, 3);
    set(m, 2, 3, 1);
    set(m, 2, 4, 2);
    set(m, 3, 4, 1);
    print(m);
    //done with setup


    travelInfo* t = get(m, start, start);
    push(log, t);
    visited[start] = true;
    while(curr != end){ //how to check for no path?
        //get everything adjacent to curr
        for(int i = 0; i < 5; i++){
            t = get(m, curr, i);
            if(t->valid){
                h->siftUp(t);
                cout << "After inserting " << i << endl;
                h->print();
            }
        }
        curr = end;
    }

    do {
        t = h->siftDown();
        //find the shortest path to an unvisited node
    } while(visited[t->to]);


    /*
    for(int i = 0; i < 5; i++){
        for(int j = 0; j < 5; j++){
            push(log, get(m, i, j));
        }
    }

    while(log){
        h->siftUp(pop(log));
    }
    */


    return 0;
}



void printTravelInfo(travelInfo* t){
    cout << "From " << t->from << " to " << t->to << ": ";
    if(t->valid){
        cout << t->dist << endl;
    } else {
        cout << "Path does not exist" << endl;
    }
}

adjMatrix* newMatrix(int size){
    adjMatrix* ret = new adjMatrix;
    ret->size = size;
    //first, allocate the "rows"
    ret->matrix = (int**)(malloc(sizeof(int*) * size));
    for(int i = 0; i < size; i++){
        //allocate each "column"
        ret->matrix[i] = (int*)(malloc(sizeof(int) * size));
        memset(ret->matrix[i], 0, sizeof(int) * size);
    }
    return ret;
}
bool set(adjMatrix* m, int from, int to, int dist){
    bool canSet = from < m->size && to < m->size && from != to;
    if(canSet){
        m->matrix[from][to] = dist;
        m->matrix[to][from] = dist;
    }
    return canSet;
}
travelInfo* get(adjMatrix* m, int from, int to){
    travelInfo* ret = new travelInfo;
    ret->from = from;
    ret->to = to;
    ret->dist = 0;
    ret->valid = (from != to && from < m->size && to < m->size);
    if(ret->valid){
        ret->dist = m->matrix[from][to];
    }
    return ret;
}
void print(adjMatrix* m){
    int s = m->size;
    for(int i = 0; i < s; i++){
        for(int j = 0; j < s; j++){
            cout << m->matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void push(travelLog* &top, travelInfo* value){
    travelLog* newFrame = new travelLog;
    newFrame->next = top;
    newFrame->value = value;
    top = newFrame;
    newFrame = 0;
    delete newFrame;
}

travelInfo* pop(travelLog* &top){
    travelInfo* ret = 0;
    if(top){
        ret = top->value;
        if(top->next){
            top = top->next;
        } else {
            top = 0;
        }
    }
    return ret;
}
