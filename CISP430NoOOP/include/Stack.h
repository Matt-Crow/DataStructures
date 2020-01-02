#ifndef STACK_H
#define STACK_H

#include "StackNode.h"

using namespace std;


template <class T>
class Stack
{
    public:
        Stack();
        ~Stack();
        void cascadeDelete(StackNode<T>* node);
        bool isEmpty();
        void push(T value);
        T pop();
        void print();
        T peek();
        static int test();
    private:
        StackNode<T>* top;
};

template class Stack<int>;
template class Stack<char>;

#endif // STACK_H
