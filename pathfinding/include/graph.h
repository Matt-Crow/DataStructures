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
    // array of vertex pointers
    Vertex** vertices; // todo resizable array of each
    int numVertices;
    AdjacencyMatrix* adjMatrix;
    int nextId; // next empty index of vertices
} Graph; // is there some way of moving the declaration to another file?

Graph* newGraph(int numVertices);
void freeGraph(Graph** g);

// g is responsible for freeing the return value in freeGraph
Vertex* createVertex(Graph* g, int x, int y);
void createEdge(Graph* g, Vertex* v1, Vertex* v2, int weight);
void createUndirectedEdge(Graph* g, Vertex* v1, Vertex* v2, int weight);

void printGraph(Graph* g);

#endif
