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

bool containsDelete(string s);
bool containsNum(string s);
int extractNum(string s);

void insertChild(NumTreeNode* parent, NumTreeNode* child);
void spawnNode(NumTreeNode* &parent, int data);
void deleteNode(NumTreeNode* &root, int data);
void printTree(NumTreeNode* root);
NumTreeNode* findTreeNode(NumTreeNode* root, int num, bool showPath);
NumTreeNode* findTreeNode(NumTreeNode* root, int num);
//###########################################################
//           END PROTOTYPES
//###########################################################

int useTreeDelete(){
    NumTreeNode* root = 0;
    string ip;
    int num;
    ifstream in = ifstream("input.txt");

    while(getline(in, ip)){
        if(containsDelete(ip)){
            num = extractNum(ip);
            cout << "Delete " << num << endl;
            if(findTreeNode(root, num)){
                deleteNode(root, num);
            } else {
                spawnNode(root, num);
            }
        }else if(containsNum(ip)){
            spawnNode(root, extractNum(ip));
        }else{
            cout << "Invalid input: " << ip << endl;
        }
    }
    printTree(root);

    return 0;
}



//###########################################################
//           BEGIN DEFINITIONS
//###########################################################
bool containsDelete(string s){
    bool ret = false;
    string checking = "delete";
    int onChar = 0;

    if(s.length() < checking.length()){
        return false;
    }

    //                 something is going wrong with this part
    for(int i = 0; i < s.length() - checking.length() && !ret; i++){
        if(s[i] == checking[0]){
            ret = true;
            for(int j = i; j < s.length() && onChar < checking.length() && ret; j++){
                ret = s[j] == checking[onChar];
                onChar++;
            }
        }
    }

    return ret;
}

bool containsNum(string s){
    bool ret = false;
    for(int i = 0; i < s.length() && !ret; i++){
        ret = isdigit(s[i]);
    }
    return ret;
}

int extractNum(string s){
    int ret = 0;
    for(int i = 0; i < s.length(); i++){
        if(isdigit(s[i])){
            ret *= 10;
            ret += s[i] - 48; //account for ASCII conversion
        }
    }
    return ret;
}

//called by spawnNode
void insertChild(NumTreeNode* parent, NumTreeNode* child){
    if(parent->data < child->data){
        if(parent->rightChild){
            insertChild(parent->rightChild, child);
        } else {
            parent->rightChild = child;
            child->parent = parent;
        }
    } else if(parent->data > child->data){
        if(parent->leftChild){
            insertChild(parent->leftChild, child);
        } else {
            parent->leftChild = child;
            child->parent = parent;
        }
    } else {
        cout << "Something went wrong: I'm supposed to catch duplicates before this" << endl;
    }
}

void spawnNode(NumTreeNode* &parent, int data){
    if(!findTreeNode(parent, data)){

        NumTreeNode* nn = new NumTreeNode;
        nn->data = data;
        nn->leftChild = 0;
        nn->rightChild = 0;

        if(parent){
            insertChild(parent, nn);
        } else {
            parent = nn;
        }
    }
}

void deleteNode(NumTreeNode* &root, int data){
    NumTreeNode* deleteMe = findTreeNode(root, data);
    NumTreeNode* parent;
    if(deleteMe){
        parent = deleteMe->parent;
        if(!deleteMe->leftChild && !deleteMe->rightChild){
            //no children
            if(!parent){
                //is root
                root = 0;
            }else if(parent->leftChild == deleteMe){
                parent->leftChild = 0;
            } else {
                parent->rightChild = 0;
            }
        } else if(!deleteMe->leftChild || !deleteMe->rightChild){
            //one child
            if(!parent){
                //is root
                if(deleteMe->leftChild){
                    root = deleteMe->leftChild;
                } else {
                    root = deleteMe->rightChild;
                }
            } else if(deleteMe->leftChild){
                if(parent->leftChild == deleteMe){
                    parent->leftChild = deleteMe->leftChild;
                } else {
                    parent->rightChild = deleteMe->leftChild;
                }
            } else {
                if(parent->leftChild == deleteMe){
                    parent->leftChild = deleteMe->rightChild;
                } else {
                    parent->rightChild = deleteMe->rightChild;
                }
            }
        }
    }
    deleteMe = 0;
    delete deleteMe;
    parent = 0;
    delete parent;
}

void printTree(NumTreeNode* root){
    cout << "Node " << root << endl;

    if(root == 0){
        return;
    }

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
        } else if(root->data > val){
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
