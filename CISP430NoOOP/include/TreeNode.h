#ifndef TREENODE_H
#define TREENODE_H

template <class T>
class TreeNode
{
    public:
        TreeNode(T data);
        static TreeNode<T>* fromSortedArray(T a[], int start, int end);
        static TreeNode<T>* fromUnsoredArray(T a[], int len, int idx);
        T getData();
        void setLeft(TreeNode<T>* n);
        void setRight(TreeNode<T>* n);
        TreeNode<T>* getLeft();
        TreeNode<T>* getRight();
        int getHeight();
        void print();
        int getArraySize();
        void populateArray(T a[], int len, int idx);
        static int test();
    private:
        T data;
        TreeNode<T>* left;
        TreeNode<T>* right;
        void updateHeight();
        int height;
};

template class TreeNode<int>;
template class TreeNode<char>;

#endif // TREENODE_H
