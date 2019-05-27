#include "StackNode.h"

template <class T>
StackNode<T>::StackNode(T value)
{
    this->data = value;
    this->next = 0;
}

template <class T>
T StackNode<T>::getData(){
    return this->data;
}
