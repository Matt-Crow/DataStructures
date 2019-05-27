#ifndef ABSTRACTTREE_H
#define ABSTRACTTREE_H

#include "TreeNode.h"

template <class T>
class AbstractTree
{
    public:
        AbstractTree();
        ~AbstractTree();
    private:
        TreeNode<T>* root;
};

#endif // ABSTRACTTREE_H
