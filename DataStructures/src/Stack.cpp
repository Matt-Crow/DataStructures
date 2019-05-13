#include "Stack.h"

using namespace std;

template <class T>
Stack<T>::Stack()
{
    this->top = 0;
}

template <class T>
Stack<T>::~Stack()
{
    this->top = 0;
    delete top;
    delete this;
}



template class Stack<int>; //need this. O...K...
