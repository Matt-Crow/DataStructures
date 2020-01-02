#ifndef TRAVELHEAP_H
#define TRAVELHEAP_H

#include "../findPath.h"

class TravelHeap
{
    public:
        TravelHeap(int capacity);
        ~TravelHeap();
        bool siftUp(travelInfo* t);
        travelInfo* siftDown();
        void print();

    private:
        travelInfo** heap;
        int firstEmptyIdx;
        int capacity;
};

#endif // TRAVELHEAP_H
