#include "QueueNode.h"

template <class T>
QueueNode<T>::QueueNode(T val)
{
    value = val;
    prev = 0;
    next = 0;
}
