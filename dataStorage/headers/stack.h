#ifndef STACK
#define STACK

template<class T>
class StackNode{
    public:
        StackNode(T val);
        ~StackNode();
        void setNext(StackNode<T>* next);
        StackNode<T>* getNext();
        T getValue();
    private:
        StackNode<T>* next;
        T value;
};

template<class T>
class Stack{
    public:
        Stack();
        ~Stack();
        void push(T val);
        T pop();
        T peek();
        void print();
        bool isEmpty();
        static int test();
    private:
        StackNode<T>* top;
};

#endif
