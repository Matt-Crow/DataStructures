#include "graph.h"
#include<stdio.h>
#include<stdlib.h>

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
        for(int i = 0; i < s; ++i){
            for(int j = 0; j < 3; ++j){
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

Graph* newGraph(int numVertices);
void freeGraph(Graph** g);

Vertex* createVertex(Graph* g, int x, int y);
void createEdge(Graph* g, Vertex* v1, Vertex* v2, int weight);

void printGraph(Graph* g);
