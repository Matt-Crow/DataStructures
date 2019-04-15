#include <iostream>
#include <fstream>

using namespace std;

//###########################################################
//           BEGIN PROTOTYPES
//###########################################################
struct Node {
    Node* prev;
    Node* next;
    string data;
};

struct LinkedList {
    Node* head;
    Node* tail;
};

struct NameTreeNode{
    LinkedList* data;
    NameTreeNode* parent;
    NameTreeNode* leftChild;
    NameTreeNode* rightChild;
};

void insertChild(NameTreeNode* parent, NameTreeNode* child);
NameTreeNode* spawnNode(NameTreeNode* &parent, string data);
void printTree(NameTreeNode* root);
NameTreeNode* findTreeNode(NameTreeNode* root, string name, bool showPath);
NameTreeNode* findTreeNode(NameTreeNode* root, string name);
int numFound(NameTreeNode* root, string name);

//from way back in exam 1...

Node* newNode(string data);
LinkedList* newLinkedList();

void push(LinkedList* ll, string data);
int length(LinkedList* ll);
//###########################################################
//           END PROTOTYPES
//###########################################################

int useInsertSearch(){
    NameTreeNode* root = 0;
    NameTreeNode* found = 0;
    string name;
    int count;
    ifstream in = ifstream("insertSearchIp.txt");

    while(in >> name){
        spawnNode(root, name);
    }
    //printTree(root);
    cout << "Enter a name to search for: ";
    cin >> name;
    cout << "Searching..." << endl;

    found = findTreeNode(root, name, true);
    count = (found) ? length(found->data) : 0;
    cout << count << " instances of the name " << name << " were found." << endl;

    return 0;
}



//###########################################################
//           BEGIN DEFINITIONS
//###########################################################

//called by spawnNode
void insertChild(NameTreeNode* parent, NameTreeNode* child){
    if(parent->data->head->data > child->data->head->data){
        if(parent->rightChild){
            insertChild(parent->rightChild, child);
        } else {
            parent->rightChild = child;
            child->parent = parent;
        }
    } else if(parent->data->head->data < child->data->head->data){
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

NameTreeNode* spawnNode(NameTreeNode* &parent, string data){
    NameTreeNode* ret = 0;
    if(numFound(parent, data) > 0){
        ret = findTreeNode(parent, data);
        push(ret->data, data);
    } else {
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
    }
    return ret;
}

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

NameTreeNode* findTreeNode(NameTreeNode* root, string name, bool showPath){
    NameTreeNode* ret = 0; //not found
    if(root){
        //every linked list in this program has at least one element
        //so this is safe
        if(showPath){
            cout << root->data->head->data;
        }
        if(root->data->head->data == name){
            if(showPath){
                cout << endl;
            }
            ret = root;
        } else if(root->data->head->data < name){
            if(root->leftChild){
                if(showPath){
                    cout << " -> ";
                }
                ret = findTreeNode(root->leftChild, name, showPath);
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
                ret = findTreeNode(root->rightChild, name, showPath);
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
NameTreeNode* findTreeNode(NameTreeNode* root, string name){
    return findTreeNode(root, name, false);
}

int numFound(NameTreeNode* root, string name){
    int ret = 0;
    NameTreeNode* found = findTreeNode(root, name);
    if(found){
        ret = length(found->data);
    }

    return ret;
}

Node* newNode(string data){
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

void push(LinkedList* ll, string data){
    Node* nn = newNode(data);
    if(ll->head && ll->tail){
        //has head and tail, so append to end
        ll->tail->next = nn;
        nn->prev = ll->tail;
        ll->tail = nn;
    } else {
        //either no head, or no tail.
        //in this implementation, that means no elements.
        ll->head = nn;
        ll->tail = nn;
    }
}

int length(LinkedList* ll){
    int ret = 0;
    Node* curr = ll->head;
    while(curr){
        ret++;
        curr = curr->next;
    }
    delete curr;
    return ret;
}
