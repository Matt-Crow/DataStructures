#ifndef STACKNODE_H
#define STACKNODE_H

template <class T>
class StackNode
{
    public:
        StackNode(T value);
        StackNode<T>* next;
        T getData();
    private:
        T data;
};

template class StackNode<int>;

#endif // STACKNODE_H
