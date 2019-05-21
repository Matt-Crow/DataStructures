#include <iostream>
#include "misc.h"
#include "avlTree.h"

using namespace std;

struct treeNode{
    int data;
    treeNode* left;
    treeNode* right;
    int height;
};

treeNode* newTreeNode(int data);

void insert(treeNode* &root, int data);

void preOrder(treeNode* root, ostream &output);

void inOrder(treeNode* root, ostream &output);

void postOrder(treeNode* root, ostream &output);

void breadthPrint(treeNode* root, ostream &output);



int useAvlTree(){
    treeNode* root = 0;
    int ip = 0;

    cout << "===AVL TREE===" << endl;
    while(ip != -1){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Choose an option: " << endl;
        cout << "0: print the tree pre-order" << endl;
        cout << "1: print the tree in-order" << endl;
        cout << "2: print the tree post-order" << endl;
        cout << "3: print the tree breadth-print" << endl;
        cout << "4: insert into the tree" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;
        cout << endl;
        switch(ip){
        case 0:
            preOrder(root, cout);
            break;
        case 1:
            inOrder(root, cout);
            break;
        case 2:
            postOrder(root, cout);
            break;
        case 3:
            breadthPrint(root, cout);
            break;
        case 4:
            cout << "Enter value to insert: ";
            cin >> ip;
            insert(root, ip);
            ip = 4;
            break;
        }
    }

    root = 0;
    delete root;

    return 0;
}



treeNode* newTreeNode(int data){
    treeNode* ret = new treeNode;
    ret->left = 0;
    ret->right = 0;
    ret->data = data;
    ret->height = 0;
    return ret;
}

void insert(treeNode* &root, int data){
    if(!root){
        root = newTreeNode(data);
    } else if(data < root->data){
        insert(root->left, data);
    } else {
        insert(root->right, data);
    }

    //rebalance(root);
}

void preOrder(treeNode* root, ostream &output){
    if(root){
        output << root->data << " ";
        preOrder(root->left, output);
        preOrder(root->right, output);
    }
}

void inOrder(treeNode* root, ostream &output){
    if(root){
        inOrder(root->left, output);
        output << root->data << " ";
        inOrder(root->right, output);
    }
}

void postOrder(treeNode* root, ostream &output){
    if(root){
        postOrder(root->left, output);
        postOrder(root->right, output);
        output << root->data << " ";
    }
}

void breadthPrint(treeNode* root, ostream &output){
    linkedList<treeNode>* currLv = newLinkedList<treeNode>();
    treeNode* curr = root;
    enqueue(currLv, root);

    currLv = 0;
    delete currLv;
}
