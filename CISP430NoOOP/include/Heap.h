#ifndef HEAP_H
#define HEAP_H

template <class T>
class Heap
{
    public:
        Heap(bool isMinHeap, int size);
        ~Heap();
        bool isEmpty();
        bool siftUp(T data);
        T siftDown();
        void print();
        static int test();
    private:
        bool isMinHeap;
        int size;
        int firstEmptyIdx;
        T* arr;
};

template class Heap<int>;

#endif // HEAP_H
