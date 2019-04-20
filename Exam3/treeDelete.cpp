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

struct Node {
    Node* prev;
    Node* next;
    NumTreeNode* data;
};

struct LinkedList {
    Node* head;
    Node* tail;
};

bool containsDelete(string s);
bool containsNum(string s);
int extractNum(string s);

void insertChild(NumTreeNode* parent, NumTreeNode* child);
void spawnNode(NumTreeNode* &parent, int data);
void deleteNode(NumTreeNode* &root, int data);

NumTreeNode* findTreeNode(NumTreeNode* root, int num);

void preOrder(NumTreeNode* root, ostream &output);
void inOrder(NumTreeNode* root, ostream &output);
void postOrder(NumTreeNode* root, ostream &output);
void breadthPrint(NumTreeNode* root, ostream &output);

Node* newNode(NumTreeNode* data);
LinkedList* newLinkedList();

void enq(LinkedList* ll, NumTreeNode* data);
NumTreeNode* deq(LinkedList* ll);
//###########################################################
//           END PROTOTYPES
//###########################################################

int useTreeDelete(){
    NumTreeNode* root = 0;
    string ip;
    int num;
    ifstream in = ifstream("treeDeleteInput.txt");
    ofstream out = ofstream("treeDeleteOutput.txt");

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
    preOrder(root, cout);
    cout << endl;

    cout << "In-order: ";
    inOrder(root, cout);
    cout << endl;

    cout << "Post-order: ";
    postOrder(root, cout);
    cout << endl;

    cout << "Breadth-order: " << endl;
    breadthPrint(root, cout);
    cout << endl;



    out << "Pre-order: ";
    preOrder(root, out);
    out << endl;

    out << "In-order: ";
    inOrder(root, out);
    out << endl;

    out << "Post-order: ";
    postOrder(root, out);
    out << endl;

    out << "Breadth-order: " << endl;
    breadthPrint(root, out);
    out << endl;

    out.close();

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

void preOrder(NumTreeNode* root, ostream &output){
    if(root){
        output << root->data << " ";
        preOrder(root->leftChild, output);
        preOrder(root->rightChild, output);
    }
}
void inOrder(NumTreeNode* root, ostream &output){
    if(root){
        inOrder(root->leftChild, output);
        output << root->data << " ";
        inOrder(root->rightChild, output);
    }
}
void postOrder(NumTreeNode* root, ostream &output){
    if(root){
        postOrder(root->leftChild, output);
        postOrder(root->rightChild, output);
        output << root->data << " ";
    }
}
void breadthPrint(NumTreeNode* root, ostream &output){
    if(!root){
        return;
    }
    LinkedList* currLv = newLinkedList();
    NumTreeNode* curr = root;
    enq(currLv, curr);
    while(currLv->head){
        LinkedList* nextLv = newLinkedList();
        while(currLv->head){
            curr = deq(currLv);
            output << curr->data << " ";
            if(curr->leftChild){
                enq(nextLv, curr->leftChild);
            }
            if(curr->rightChild){
                enq(nextLv, curr->rightChild);
            }
        }

        currLv = nextLv;
        output << endl;
    }
}

Node* newNode(NumTreeNode* data){
    Node* nn = new Node;
    nn->prev = 0;
    nn->next = 0;
    nn->data = data;
    return nn;
}

LinkedList* newLinkedList(){
    LinkedList* ll = new LinkedList;
    ll->head = 0;
    ll->tail = 0;
    return ll;
}

void enq(LinkedList* ll, NumTreeNode* data){
    Node* nn = newNode(data);
    nn->prev = ll->tail;
    if(ll->head){
        ll->tail->next = nn;
    } else {
        ll->head = nn;
    }
    ll->tail = nn;
    nn = 0;
    delete nn;
}
NumTreeNode* deq(LinkedList* ll){
    NumTreeNode* ret = 0;
    if(ll->head){
        ret = ll->head->data;
        ll->head = ll->head->next;
        if(ll->head){
            ll->head->prev = 0;
        }
    }
    return ret;
}
