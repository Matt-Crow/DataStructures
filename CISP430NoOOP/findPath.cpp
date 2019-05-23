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
    set(m, 0, 2, 3);
    set(m, 0, 3, 5);
    set(m, 0, 4, 15);
    set(m, 1, 2, 2);
    set(m, 1, 3, 4);
    set(m, 1, 4, 6);
    set(m, 2, 3, 3);
    set(m, 2, 4, 5);
    set(m, 3, 4, 5);
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
                t->dist += log->value->dist;
                //since this is accumulated distance,
                //I need to add the distance between this new point and the start
                h->siftUp(t);
            }
        }
        cout << "After sifting up: " << endl;
        h->print();

        do {
            t = h->siftDown();
            //find the shortest path to an unvisited node
        } while(visited[t->to]);
        push(log, t);
        curr = t->to;
        visited[curr] = true;
    }

    int totalDist = log->value->dist;
    int currDist = totalDist; //accumulated distance to the current node
    //used for backtracking

    travelLog* reversed = 0;
    while(log && curr != start){
        t = pop(log);
        if(t->to == curr && t->dist == currDist){
            //need to add distance checking
            push(reversed, t);
            curr = t->from;
            currDist -= get(m, t->from, t->to)->dist;
        }
    }
    cout << "From " << start << " to " << end << ": " << endl;
    while(reversed){
        printTravelInfo(pop(reversed));
    }
    cout << "Total distance: " << totalDist << endl;

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
    ret->valid = (from != to && from < m->size && to < m->size && m->matrix[from][to] != 0);
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
