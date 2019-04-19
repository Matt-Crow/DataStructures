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

NumTreeNode* findTreeNode(NumTreeNode* root, int num);

void preOrder(NumTreeNode* root);
void inOrder(NumTreeNode* root);
void postOrder(NumTreeNode* root);
//###########################################################
//           END PROTOTYPES
//###########################################################

//useTreeDelete
int main(){
    NumTreeNode* root = 0;
    string ip;
    int num;
    ifstream in = ifstream("input.txt");

    while(getline(in, ip)){
        if(containsDelete(ip)){
            num = extractNum(ip);
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
    cout << "Pre-order: ";
    preOrder(root);
    cout << endl;

    cout << "In-order: ";
    inOrder(root);
    cout << endl;

    cout << "Post-order: ";
    postOrder(root);
    cout << endl;

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
            } else if(parent->leftChild == deleteMe){
                if(deleteMe->leftChild){
                    parent->leftChild = deleteMe->leftChild;
                } else {
                    parent->leftChild = deleteMe->rightChild;
                }
            } else {
                if(deleteMe->leftChild){
                    parent->rightChild = deleteMe->leftChild;
                } else {
                    parent->rightChild = deleteMe->rightChild;
                }
            }
        } else {
            //2 children
            NumTreeNode* curr = deleteMe->rightChild;
            while(curr->leftChild){
                curr = curr->leftChild;
            }
            deleteNode(curr, curr->data); //recursive

            deleteMe->data = curr->data;

            curr = 0;
            delete curr;
        }
    }
    deleteMe = 0;
    delete deleteMe;
    parent = 0;
    delete parent;
}

NumTreeNode* findTreeNode(NumTreeNode* root, int val){
    NumTreeNode* ret = 0; //not found
    if(root){
        if(root->data == val){
            ret = root;
        } else if(root->data > val){
            if(root->leftChild){
                ret = findTreeNode(root->leftChild, val);
            } else {
                //no left child, not found
            }
        } else {
            if(root->rightChild){
                ret = findTreeNode(root->rightChild, val);
            } else {
                //no right child, not found
            }
        }
    } else {
        //no more nodes, not found
    }
    return ret;
}

void preOrder(NumTreeNode* root){
    if(root){
        cout << root->data << " ";
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}
void inOrder(NumTreeNode* root){
    if(root){
        inOrder(root->leftChild);
        cout << root->data << " ";
        inOrder(root->rightChild);
    }
}
void postOrder(NumTreeNode* root){
    if(root){
        postOrder(root->leftChild);
        postOrder(root->rightChild);
        cout << root->data << " ";
    }
}
