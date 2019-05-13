#include "StackFrame.h"

template <class T>
StackFrame<T>::StackFrame(T data)
{
    this->data = data;
    this->prev = 0;
}

template <class T>
T StackFrame<T>::get(){
    return this->data;
}

template <class T>
StackFrame<T>::~StackFrame()
{
    this->prev = 0;
    delete this;
}
