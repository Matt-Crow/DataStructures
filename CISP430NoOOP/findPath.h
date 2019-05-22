#ifndef FINDPATH_H_INCLUDED
#define FINDPATH_H_INCLUDED

struct travelInfo{
    int from;
    int to;
    int dist;
    bool valid;
};

struct adjMatrix{
    int size;
    int** matrix;
};

struct travelLog{
    travelInfo* value;
    travelLog* next;
};

void print(travelInfo* t);

adjMatrix* newMatrix(int size);
bool set(adjMatrix* m, int from, int to, int dist);
travelInfo* get(adjMatrix* m, int from, int to);
void print(adjMatrix* m);



void push(travelLog* &top, travelInfo* value);
travelInfo* pop(travelLog* &top);

#endif // FINDPATH_H_INCLUDED
