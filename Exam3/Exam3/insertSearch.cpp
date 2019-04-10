#include <iostream>
#include <fstream>

using namespace std;

struct NameTreeNode{
    string data;
    NameTreeNode* parent;
    NameTreeNode* leftChild;
    NameTreeNode* rightChild;
};

void insertChild(NameTreeNode* parent, NameTreeNode* child);
NameTreeNode* spawnNode(NameTreeNode* &parent, string data);
void printTree(NameTreeNode* root);

int useInsertSearch(){
    NameTreeNode* root = 0;
    string name;
    ifstream in = ifstream("insertSearchIp.txt");
    while(in >> name){
        cout << name << endl;
        spawnNode(root, name);
    }
    printTree(root);

    return 0;
}


void insertChild(NameTreeNode* parent, NameTreeNode* child){
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

NameTreeNode* spawnNode(NameTreeNode* &parent, string data){
    NameTreeNode* ret = new NameTreeNode;
    ret->parent = parent;
    ret->data = data;
    ret->leftChild = 0;
    ret->rightChild = 0;

    if(parent){
        insertChild(parent, ret);
    } else {
        parent = ret;
    }

    return ret;
}

void printTree(NameTreeNode* root){
    cout << "Node " << root << endl;
    cout << "Left child: " << root->leftChild;
    if(root->leftChild){
        cout << " (" << root->leftChild->data << ")";
    }
    cout << endl;
    cout << "Right child: " << root->rightChild;
    if(root->rightChild){
        cout << " (" << root->rightChild->data << ")";
    }
    cout << endl;
    cout << "Data: " << root->data << endl;
    cout << endl;
    if(root->leftChild){
        printTree(root->leftChild);
    }
    if(root->rightChild){
        printTree(root->rightChild);
    }
}
