#include <iostream>

using namespace std;

struct TreeNode{
    int data;
    TreeNode* parent;
    TreeNode* leftChild;
    TreeNode* rightChild;
};

void insertChild(TreeNode* parent, TreeNode* child){
    if(parent->data < child->data){
        if(parent->rightChild){
            insertChild(parent->rightChild, child);
        } else {
            parent->rightChild = child;
            child->parent = parent;
        }
    } else {
        //duplicates are placed on left
        if(parent->leftChild){
            insertChild(parent->leftChild, child);
        } else {
            parent->leftChild = child;
            child->parent = parent;
        }
    }
}

TreeNode* spawnNode(TreeNode* parent, int data){
    TreeNode* ret = new TreeNode;
    ret->parent = parent;
    ret->data = data;
    ret->leftChild = 0;
    ret->rightChild = 0;

    if(parent){
        insertChild(parent, ret);
    }

    return ret;
}

void printTree(TreeNode* root){
    cout << "Node " << root << endl;
    cout << "Left child: " << root->leftChild << endl;
    cout << "Right child: " << root->rightChild << endl;
    cout << "Data: " << root->data << endl;
    cout << endl;
    if(root->leftChild){
        printTree(root->leftChild);
    }
    if(root->rightChild){
        printTree(root->rightChild);
    }
}

int useTreeNode(){
    TreeNode* root = spawnNode(0, 100);
    int ip = 0;

    do{
        cout << "Input positive number to add it to the tree: ";
        cin >> ip;
        if(ip > 0){
            spawnNode(root, ip);
            printTree(root);
        }
    } while(ip > 0);

    return 0;
}
