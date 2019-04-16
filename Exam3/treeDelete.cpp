#include <iostream>
#include <fstream>

using namespace std;

//###########################################################
//           BEGIN PROTOTYPES
//###########################################################
struct NumTreeNode{
    int data;
    NumTreeNode* parent;
    NumTreeNode* leftChild;
    NumTreeNode* rightChild;
};

void insertChild(NumTreeNode* parent, NumTreeNode* child);
void spawnNode(NumTreeNode* &parent, int data);
//void printTree(NumTreeNode* root);
NumTreeNode* findTreeNode(NumTreeNode* root, int num, bool showPath);
NumTreeNode* findTreeNode(NumTreeNode* root, int num);
//###########################################################
//           END PROTOTYPES
//###########################################################

int useTreeDelete(){
    NumTreeNode* root = 0;
    string ip;
    ifstream in = ifstream("input.txt");

    while(in >> ip){
        //if is just number, insert
        if(true){
            spawnNode(root, num);
        }
        //if contains "delete", delete
        //else nothing
    }
    //printTree(root);
    /*
    cout << "Enter a name to search for: ";
    cin >> name;
    cout << "Searching..." << endl;

    found = findTreeNode(root, name, true);
    count = (found) ? length(found->data) : 0;
    cout << count << " instances of the name " << name << " were found." << endl;
    */
    return 0;
}



//###########################################################
//           BEGIN DEFINITIONS
//###########################################################

//called by spawnNode
void insertChild(NumTreeNode* parent, NumTreeNode* child){
    if(parent->data > child->data){
        if(parent->rightChild){
            insertChild(parent->rightChild, child);
        } else {
            parent->rightChild = child;
            child->parent = parent;
        }
    } else if(parent->data < child->data){
        if(parent->leftChild){
            insertChild(parent->leftChild, child);
        } else {
            parent->leftChild = child;
            child->parent = parent;
        }
    } else {
        cout << "Something went wrong" << endl;
    }
}

void spawnNode(NumTreeNode* &parent, int data){
    if(!findTreeNode(parent, data)){
        cout << "insert " << data << endl;
        return;
        /*
        ret = new NameTreeNode;
        ret->parent = parent;
        ret->data = newLinkedList();
        push(ret->data, data);
        ret->leftChild = 0;
        ret->rightChild = 0;
        if(parent){
            insertChild(parent, ret);
        } else {
            parent = ret;
        }
        */
    } else {
        cout << "don't insert " << data << endl;
    }
}
/*
void printTree(NameTreeNode* root){
    cout << "Node " << root << endl;

    if(root == 0){
        return;
    }

    cout << "Left child: " << root->leftChild;
    if(root->leftChild){
        cout << " (" << root->leftChild->data->head->data << ")";
    }
    cout << endl;
    cout << "Right child: " << root->rightChild;
    if(root->rightChild){
        cout << " (" << root->rightChild->data->head->data << ")";
    }
    cout << endl;
    cout << "Data: " << root->data->head->data << " x" << length(root->data) << endl;
    cout << endl;
    if(root->leftChild){
        printTree(root->leftChild);
    }
    if(root->rightChild){
        printTree(root->rightChild);
    }
}
*/
NumTreeNode* findTreeNode(NumTreeNode* root, int val, bool showPath){
    NumTreeNode* ret = 0; //not found
    if(root){
        //every linked list in this program has at least one element
        //so this is safe
        if(showPath){
            cout << root->data;
        }
        if(root->data == val){
            if(showPath){
                cout << endl;
            }
            ret = root;
        } else if(root->data < val){
            if(root->leftChild){
                if(showPath){
                    cout << " -> ";
                }
                ret = findTreeNode(root->leftChild, val, showPath);
            } else {
                //no left child, not found
                if(showPath){
                    cout << endl;
                }
            }
        } else {
            if(root->rightChild){
                if(showPath){
                    cout << " -> ";
                }
                ret = findTreeNode(root->rightChild, val, showPath);
            } else {
                //no right child, not found
                if(showPath){
                    cout << endl;
                }
            }
        }
    } else {
        //no more nodes, not found
        if(showPath){
            cout << endl;
        }
    }
    return ret;
}

NumTreeNode* findTreeNode(NumTreeNode* root, int val){
    return findTreeNode(root, val, false);
}
