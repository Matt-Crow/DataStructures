#include "graph.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h> // memset

/*
Private functions
*/
#define NO_EDGE (-1)

Vertex* newVertex(int id, int x, int y){
    Vertex* v = (Vertex*)malloc(sizeof(Vertex));
    v->id = id;
    v->x = x;
    v->y = y;
    return v;
}
void freeVertex(Vertex** v){
    if(v && *v){
        free(*v);
        *v = 0;
    }
}
void printVertex(Vertex* v){
    if(v){
        printf("#%d (%d, %d)", v->id, v->x, v->y);
    }
}

AdjacencyMatrix* newAdjacencyMatrix(int size){
    AdjacencyMatrix* m = (AdjacencyMatrix*)malloc(sizeof(AdjacencyMatrix));
    m->size = size;
    m->weights = (int**)malloc(size * sizeof(int*)); // space for rows
    for(int i = 0; i < size; ++i){
        m->weights[i] = (int*)malloc(size * sizeof(int)); // allocate each row
        for(int j = 0; j < size; ++j){
            m->weights[i][j] = NO_EDGE;
        }
    }
    return m;
}
void freeAdjacencyMatrix(AdjacencyMatrix** m){
    if(m && *m){
        AdjacencyMatrix* freeMe = *m;
        for(int i = 0; i < freeMe->size; ++i){
            free(freeMe->weights[i]);
        }
        free(freeMe->weights);
        free(freeMe);
        *m = 0; // don't do freeMe here
    }
}
void printAdjacencyMatrix(AdjacencyMatrix* m){
    if(m){
        int s = m->size;
        // print header
        printf("%3c  ", ' ');
        for(int v = 0; v < s; ++v){
            printf("%3d ", v);
        }
        printf("%c", '\n');

        for(int i = 0; i < s; ++i){
            // print row prefix
            printf("%3d |", i);
            for(int j = 0; j < s; ++j){
                if(m->weights[i][j] == NO_EDGE){
                    printf("%3c ", 'X');
                } else {
                    printf("%3d ", m->weights[i][j]);
                }
            }
            printf("%c", '\n');
        }
    }
}

/*
Public functions
*/

Graph* newGraph(int numVertices){
    Graph* g = (Graph*)malloc(sizeof(Graph));
    g->numVertices = numVertices;
    g->vertices = (Vertex**)malloc(numVertices * sizeof(Vertex*));
    memset(g->vertices, 0, numVertices * sizeof(Vertex*));
    g->adjMatrix = newAdjacencyMatrix(numVertices);
    g->nextId = 0;
    return g;
}
void freeGraph(Graph** gp){
    if(gp && *gp){
        Graph* g = *gp;
        Vertex* v;
        //                                   vertex has been allocated
        for(int i = 0; i < g->numVertices && g->vertices[i]; ++i){
            v = g->vertices[i];
            freeVertex(&(g->vertices[i]));
        }
        free(g->vertices);
        AdjacencyMatrix* m = g->adjMatrix;
        freeAdjacencyMatrix(&(g->adjMatrix));
        free(g);
        *gp = 0;
    }
}

Vertex* createVertex(Graph* g, int x, int y){
    Vertex* v = newVertex(g->nextId, x, y);
    g->vertices[g->nextId] = v;
    g->nextId++;
    return v;
}
void createEdge(Graph* g, Vertex* v1, Vertex* v2, int weight){
    if(g && v1 && v2){
        AdjacencyMatrix* m = g->adjMatrix;
        m->weights[v1->id][v2->id] = weight;
    }
}
void createUndirectedEdge(Graph* g, Vertex* v1, Vertex* v2, int weight){
    createEdge(g, v1, v2, weight);
    createEdge(g, v2, v1, weight);
}

bool isAdjacent(Graph* g, int from, int to){
    bool theyAreAdj = false;
    if(g){
        theyAreAdj = getWeight(g, from, to) != NO_EDGE;
    }
    return theyAreAdj;
}

int getWeight(Graph* g, int from, int to){
    int weight = NO_EDGE;
    if(g){
        weight = g->adjMatrix->weights[from][to];
    }
    return weight;
}

void printGraph(Graph* g){
    if(g){
        printf("%s\n", "GRAPH:");
        printf("%s\n", "Vertices:");
        for(int i = 0; i < g->numVertices && g->vertices[i]; ++i){
            printVertex(g->vertices[i]);
            printf("%c", '\n');
        }
        printAdjacencyMatrix(g->adjMatrix);
    }
}
