#include "TreeNode.h"
#include "../misc.h"
#include <iostream>
#include <algorithm>

using namespace std;

template <class T>
TreeNode<T>::TreeNode(T data)
{
    this->data = data;
    this->left = 0;
    this->right = 0;
    height = 0;
}

template <class T>
TreeNode<T>* TreeNode<T>::fromSortedArray(T a[], int start, int end){
    TreeNode<T>* ret = 0;
    if(start <= end){
        int mid = (start + end) / 2;
        ret = new TreeNode<T>(a[mid]);
        ret->setLeft(TreeNode<T>::fromSortedArray(a, start, mid - 1));
        ret->setRight(TreeNode<T>::fromSortedArray(a, mid + 1, end));
    }
    return ret;
}

template <class T>
TreeNode<T>* TreeNode<T>::fromUnsoredArray(T a[], int len, int idx){
    TreeNode<T>* ret = new TreeNode<T>(a[idx]);
    if(idx * 2 + 1 < len){
        ret->setLeft(TreeNode<T>::fromUnsoredArray(a, len, idx * 2 + 1));
    }
    if(idx * 2 + 2 < len){
        ret->setRight(TreeNode<T>::fromUnsoredArray(a, len, idx * 2 + 2));
    }
    return ret;
}

template <class T>
T TreeNode<T>::getData(){
    return data;
}

template <class T>
void TreeNode<T>::setLeft(TreeNode<T>* n){
    if(n != this){
        left = n;
        updateHeight();
    }
}

template <class T>
void TreeNode<T>::setRight(TreeNode<T>* n){
    if(n != this){
        right = n;
        updateHeight();
    }
}

template <class T>
TreeNode<T>* TreeNode<T>:: getLeft(){
    return left;
}

template <class T>
TreeNode<T>* TreeNode<T>::getRight(){
    return right;
}

template <class T>
int TreeNode<T>::getHeight(){
    return height;
}

template <class T>
void TreeNode<T>::updateHeight(){
    if(this->left){
        this->left->updateHeight();
    }
    if(this->right){
        this->right->updateHeight();
    }
    int leftH = (this->left) ? this->left->getHeight() : -1;
    int rightH = (this->right) ? this->right->getHeight() : -1;
    height = max(leftH, rightH) + 1;
}

template <class T>
void TreeNode<T>::print(){
    cout << "Node " << this << endl;
    cout << "   Data is " << data << endl;
    cout << "   Height is " << height << endl;
    if(left){
        cout << "   Left is " << left << "(" << left->getData() << ")" << endl;
    }
    if(right){
        cout << "   Right is " << right << "(" << right->getData() << ")" << endl;
    }
    if(left){
        left->print();
    }
    if(right){
        right->print();
    }
}

template <class T>
int TreeNode<T>::getArraySize(){
    int size = 1;

    //size = 2^(root->height + 1) - 1
    for(int i = 0; i < height + 1; i++){
        size *= 2;
    }
    size--;

    return size;
}

template <class T>
void TreeNode<T>::populateArray(T a[], int len, int idx){
    a[idx] = data;
    if(2 * idx + 1 < len && left){
        left->populateArray(a, len, 2 * idx + 1);
    }
    if(2 * idx + 2 < len && right){
        right->populateArray(a, len, 2 * idx + 2);
    }
}

template <class T>
int TreeNode<T>::test(){
    int ip = 0;
    TreeNode<int>* tree = 0;
    int size = 0;
    int idx = 0;

    do{
        cout << "===TREE===" << endl;
        cout << "0: Print the tree" << endl;
        cout << "1: Convert a sorted array to a tree" << endl;
        cout << "2: Convert an unsorted array to a tree" << endl;
        cout << "3: Convert the tree to an array" << endl;
        cout << "-1: Quit" << endl;
        cout << "Choose an option: ";
        cin >> ip;
        switch(ip){
        case 0:
            if(!tree){
                cout << "No tree to print" << endl;
            } else {
                tree->print();
            }
            break;
        case 1:
            {
            cout << "How many elements in the array?";
            cin >> ip;
            size = ip;
            idx = 0;
            int a1[size] = {0};

            cout << "Enter the element IN ORDER" << endl;
            while(idx < size){
                cout << "Element #" << idx << ": ";
                cin >> ip;
                a1[idx] = ip;
                idx++;
            }
            delete tree;
            tree = TreeNode<int>::fromSortedArray(a1, 0, size - 1);
            ip = 1;
            }
            break;
        case 2: {
            cout << "How many elements in the array?";
            cin >> ip;
            size = ip;
            idx = 0;
            int a2[size] = {0};

            while(idx < size){
                cout << "Element #" << idx << ": ";
                cin >> ip;
                a2[idx] = ip;
                idx++;
            }
            delete tree;
            tree = TreeNode<int>::fromUnsoredArray(a2, size, 0);
            ip = 2;
            } break;
        case 3: {
            if(!tree){
                cout << "No tree to convert" << endl;
            } else {
                size = tree->getArraySize();
                int a3[size] = {0};
                tree->populateArray(a3, size, 0);

                //c++ can't find print in misc.h
                for(int i = 0; i < size; i++){
                    cout << a3[i] << " ";
                }
                cout << endl;
            }
            }
            break;
        }
    } while(ip >= 0);

    delete tree;

    return 0;
}
