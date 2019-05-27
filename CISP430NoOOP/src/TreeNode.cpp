#include "TreeNode.h"

template <class T>
TreeNode<T>::TreeNode(T data)
{
    this->data = data;
    this->left = 0;
    this->right = 0;
}


template <class T>
T TreeNode<T>::getData(){
    return data;
}
