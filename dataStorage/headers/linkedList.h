#ifndef LINKED_LIST
#define LINKED_LIST

template<class T>
class LinkedListNode{
    public:
        LinkedListNode(T val);
        ~LinkedListNode();
        void setNext(LinkedListNode<T>* next);
        void setPrev(LinkedListNode<T>* prev);
        LinkedListNode<T>* getNext();
        LinkedListNode<T>* getPrev();
        T getValue();
    private:
        T value;
        LinkedListNode<T>* next;
        LinkedListNode<T>* prev;
};

template<class T>
class LinkedList{
    public:
        LinkedList();
        ~LinkedList();
        void pushToFront(T val);
        void pushToBack(T val);
        T popFromFront();
        T popFromBack();
        T peekFront();
        T peekBack();
        bool deleteNode(T withValue);
        bool isEmpty();
        void print();
        static int test();
    private:
        LinkedListNode<T>* head;
        LinkedListNode<T>* tail;
};

template class LinkedList<int>;

#endif
