#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include "travelInfo.h"
#include "pathStack.h"
#include "pathHeap.h"
#include "graph.h"

Graph* createDefaultGraph();
void printPath(PathStack* stack);

int main(){
    // todo read graph from a file
    Graph* g = createDefaultGraph();
    printGraph(g);

    // set up everything
    TravelInfo* t = 0;
    PathStack* travelLog = 0;
    //                                    worst case: each vertex connects to every other vertex
    PathHeap* travelOptions = newPathHeap(g->numVertices * (g->numVertices - 1));
    bool visited[g->numVertices];
    memset(visited, false, g->numVertices * sizeof(bool));
    int numVisited = 0;
    int start = 0; // maybe get user input
    int end = g->numVertices - 1;

    // visit the start
    int curr = start;
    visited[curr] = true;
    t = newTravelInfo(curr, curr, 0);
    pushToPathStack(&travelLog, t);
    ++numVisited;
    int totalDist;
    while(numVisited < g->numVertices || curr != end){
        // get edges from the current node
        for(int to = 0; to < g->numVertices; ++to){
            if(isAdjacent(g, curr, to) && !visited[to]){
                // get the cumulative weight from "start" to "curr" and then to "to"
                //                                   weight it took to get to curr
                totalDist = getWeight(g, curr, to) + travelLog->value->weight;
                t = newTravelInfo(curr, to, totalDist);
                siftUpPathHeap(travelOptions, t);
            }
        }

        // find the best path to check next
        do {
            t = siftDownPathHeap(travelOptions);
            if(visited[t->to]){
                freeTravelInfo(&t);
            }
        } while(!t); // loop until we find a path

        pushToPathStack(&travelLog, t);
        ++numVisited;
        curr = t->to;
        visited[curr] = true;
    }

    // backtrack to get path
    totalDist = travelLog->value->weight;
    PathStack* path = 0;
    while(travelLog && curr != start){
        t = popFromPathStack(&travelLog);
        if(t->to == curr && t->weight == totalDist){
            totalDist -= getWeight(g, t->from, t->to);
            pushToPathStack(&path, t);
            curr = t->from;
        } else {
            freeTravelInfo(&t);
        }
    }

    printPath(path);

    freePathStack(&path);
    freePathHeap(&travelOptions);
    freePathStack(&travelLog);
    freeGraph(&g);

    return 0;
}

Graph* createDefaultGraph(){
    /*

    (0)-2-(2)
     |     |
     4     2
     |     |
    (1)-1-(3)-3-(5)
           |     |
           7     4
           |     |
          (4)-1-(6)

    */
    Graph* g = newGraph(7);
    Vertex* vs[7];
    vs[0] = createVertex(g, 0, 0);
    vs[1] = createVertex(g, 0, 1);
    vs[2] = createVertex(g, 1, 0);
    vs[3] = createVertex(g, 1, 1);
    vs[4] = createVertex(g, 1, 2);
    vs[5] = createVertex(g, 2, 1);
    vs[6] = createVertex(g, 2, 2);

    createUndirectedEdge(g, vs[0], vs[1], 4);
    createUndirectedEdge(g, vs[0], vs[2], 2);
    createUndirectedEdge(g, vs[1], vs[3], 1);
    createUndirectedEdge(g, vs[2], vs[3], 2);
    createUndirectedEdge(g, vs[3], vs[5], 3);
    createUndirectedEdge(g, vs[3], vs[4], 7);
    createUndirectedEdge(g, vs[4], vs[6], 1);
    createUndirectedEdge(g, vs[5], vs[6], 4);

    return g;
}

void printPath(PathStack* stack){
    PathStack* curr = stack;
    while(curr){
        printf("%d, ", curr->value->from);
        if(!curr->prev) {
            printf("%d\n", curr->value->to);
        }
        curr = curr->prev;
    }
}
