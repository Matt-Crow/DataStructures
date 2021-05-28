#ifndef GRAPH
#define GRAPH

typedef struct Vertex {
    int id;
    int x;
    int y;
} Vertex;

typedef struct AdjacencyMatrix {
    int** weights;
    int size;
} AdjacencyMatrix;

typedef struct Graph {
    Vertex** vertices; // todo resizable array of each
    AdjacencyMatrix adjMatrix;
    int nextId;
} Graph; // is there some way of moving the declaration to another file?

Graph* newGraph(int numVertices);
void freeGraph(Graph** g);

Vertex* createVertex(Graph* g, int x, int y);
void createEdge(Graph* g, Vertex* v1, Vertex* v2, int weight);

void printGraph(Graph* g);

#endif
