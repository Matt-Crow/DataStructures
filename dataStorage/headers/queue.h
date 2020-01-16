#ifndef QUEUE
#define QUEUE

template<class T>
class QueueNode{
    public:
        QueueNode(T val);
        ~QueueNode();
        void setPrev(QueueNode<T>* prev);
        void setNext(QueueNode<T>* next);
        QueueNode<T>* getPrev();
        QueueNode<T>* getNext();
        T getValue();
    private:
        T value;
        QueueNode<T>* prev;
        QueueNode<T>* next;
};

template<class T>
class Queue{
    public:
        Queue();
        ~Queue();
        void enqueue(T val);
        T dequeue();
        T peek();
        bool isEmpty();
        void print();
        static int test();
    private:
        QueueNode<T>* head;
        QueueNode<T>* tail;
};

template class Queue<int>;

#endif
