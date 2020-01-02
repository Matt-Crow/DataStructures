#ifndef QUEUENODE_H
#define QUEUENODE_H

template <class T>
class QueueNode
{
    public:
        QueueNode(T val);
        QueueNode* prev;
        QueueNode* next;
        T value;
};

template class QueueNode<int>;

#endif // QUEUENODE_H
