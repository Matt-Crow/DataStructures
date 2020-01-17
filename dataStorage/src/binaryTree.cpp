#include <iostream>
#include "binaryTree.h"

template<class T>
TreeNode<T>::TreeNode(T val){
    this->value = val;
    this->left = 0;
    this->right = 0;
}

template<class T>
TreeNode<T>::~TreeNode(){
    std::cout << "Delete " << this->value << std::endl;
}

template<class T>
void TreeNode<T>::cascadeDelete(){
    if(this->left){
        this->left->cascadeDelete();
    }
    if(this->right){
        this->right->cascadeDelete();
    }
    delete this;
}

template<class T>
void TreeNode<T>::setLeft(TreeNode<T>* left){
    this->left = left;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T>* right){
    this->right = right;
}

template<class T>
TreeNode<T>* TreeNode<T>::getLeft(){
    return this->left;
}

template<class T>
TreeNode<T>* TreeNode<T>::getRight(){
    return this->right;
}

template<class T>
int TreeNode<T>::getHeight(){
    int left = (this->left) ? this->left->getHeight() + 1 : 0;
    int right = (this->right) ? this->right->getHeight() + 1 : 0;
    return (left < right) ? right : left;
}

template<class T>
int TreeNode<T>::getArraySize(){
    int ret = 1;
    int height = getHeight();
    // 2^(height + 1) - 1;
    for(int i = 0; i < height + 1; i++){
        ret *= 2;
    }
    ret--;
    return ret;
}

template<class T>
void TreeNode<T>::populateArray(T* a, int aLen, int idx){
    if(a != 0){
        a[idx] = this->value;
        if(2 * idx + 1 < aLen && this->left){
            this->left->populateArray(a, aLen, 2 * idx + 1);
        }
        if(2 * idx + 2 < aLen && this->right){
            this->right->populateArray(a, aLen, 2 * idx + 2);
        }
    }
}

template<class T>
T TreeNode<T>::getValue(){
    return this->value;
}

template<class T>
void TreeNode<T>::inOrder(){
    if(this->left){
        this->left->inOrder();
    }
    std::cout << this->value << " ";
    if(this->right){
        this->right->inOrder();
    }
}



template<class T>
BinaryTree<T>::BinaryTree(){
    this->root = 0;
}

template<class T>
BinaryTree<T>::~BinaryTree(){
    if(this->root){
        this->root->cascadeDelete();
        this->root = 0;
    }
}

template<class T>
void BinaryTree<T>::put(T val){
    TreeNode<T>* nn = new TreeNode<T>(val);
    if(this->isEmpty()){
        this->root = nn;
    } else {
        TreeNode<T>* curr = this->root;
        bool done = false;
        while(!done){
            if(curr->getValue() > val){
                if(curr->getLeft()){
                    curr = curr->getLeft();
                } else {
                    curr->setLeft(nn);
                    done = true;
                }
            } else {
                if(curr->getRight()){
                    curr = curr->getRight();
                } else {
                    curr->setRight(nn);
                    done = true;
                }
            }
        }
    }
}

template<class T>
bool BinaryTree<T>::isEmpty(){
    return this->root == 0;
}

template<class T>
T* BinaryTree<T>::toArray(){
    T* ret = 0;
    if(!this->isEmpty()){
        int len = this->getArraySize();
        ret = (T*)malloc(sizeof(T) * len);
        this->root->populateArray(ret, len, 0);
    }
    return ret;
}

template<class T>
int BinaryTree<T>::getArraySize(){
    return (this->isEmpty()) ? 0 : this->root->getArraySize();
}

template<class T>
void BinaryTree<T>::print(){
    if(!this->isEmpty()){
        this->root->inOrder();
    }
}

template<class T>
int BinaryTree<T>::test(){
    BinaryTree<int>* tree = new BinaryTree<int>();
    int ip = 0;

    do {
        std::cout << "0: Print the binary tree" << std::endl;
        std::cout << "1: Insert into the binary tree" << std::endl;
        std::cout << "2: Convert the binary tree to an array" << std::endl;
        std::cout << "-1: Quit" << std::endl;
        std::cout << "Choose an option:" << std::endl;
        std::cin >> ip;
        switch(ip){
            case 0:
                tree->print();
                std::cout << std::endl;
                break;
            case 1:
                std::cout << "Enter a value to insert: ";
                std::cin >> ip;
                tree->put(ip);
                ip = 1;
                break;
            case 2:
                int* a = tree->toArray();
                int len = tree->getArraySize();
                std::cout << "Array:" << std::endl;
                for(int i = 0; i < len; i++){
                    std::cout << a[i] << " ";
                }
                std::cout << std::endl;
                delete a;
                break;
        }
    } while(ip != -1);

    delete tree;
    tree = 0;

    return 0;
}
