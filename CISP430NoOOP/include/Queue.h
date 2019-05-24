#ifndef QUEUE_H
#define QUEUE_H

#include "QueueNode.h"

template <class T>
class Queue
{
    public:
        Queue();
        ~Queue();
        void enqueue(T value);
        T deque();
        void print();
        bool isEmpty();
    private:
        QueueNode<T>* head;
        QueueNode<T>* tail;
};

template class Queue<int>;

#endif // QUEUE_H
