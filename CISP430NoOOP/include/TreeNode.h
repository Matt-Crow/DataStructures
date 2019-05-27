#ifndef TREENODE_H
#define TREENODE_H

template <class T>
class TreeNode
{
    public:
        TreeNode(T data);
        T getData();
        TreeNode<T>* left;
        TreeNode<T>* right;
    private:
        T data;
};

template class TreeNode<char>;

#endif // TREENODE_H
