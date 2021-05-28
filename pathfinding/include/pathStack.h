#ifndef PATH_STACK
#define PATH_STACK

#include "travelInfo.h"

typedef struct PathStack {
    TravelInfo* value;
    struct PathStack* prev;
} PathStack;

void freePathStack(PathStack** top);

void pushToPathStack(PathStack** top, TravelInfo* value);
TravelInfo* popFromPathStack(PathStack** top);

void printPathStack(PathStack* top);

#endif
