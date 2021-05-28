#include<stdio.h>
#include "travelInfo.h"
#include "pathStack.h"
#include "graph.h"

int main(){
    // todo read graph from a file
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
    
    printGraph(g);

    TravelInfo* t = 0;
    PathStack* stack = 0;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(i != j){
                t = newTravelInfo(i, j, i * j);
                pushToPathStack(&stack, t);
            }
        }
    }
    printPathStack(stack);
    freePathStack(&stack);
    freeGraph(&g);

    return 0;
}
