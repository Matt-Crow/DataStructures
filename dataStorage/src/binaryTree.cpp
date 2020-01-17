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
        }
    } while(ip != -1);

    delete tree;
    tree = 0;

    return 0;
}
