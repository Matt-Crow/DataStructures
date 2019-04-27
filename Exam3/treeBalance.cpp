#include <iostream>
#include <fstream>

using namespace std;

struct TreeNode{
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;
    int height;
};


struct Node {
    Node* prev;
    Node* next;
    TreeNode* data;
};

struct LinkedList {
    Node* head;
    Node* tail;
};

TreeNode* newTreeNode(int data);

int getBalance(TreeNode* root);

TreeNode* rebalance(TreeNode* root);

void setHeights(TreeNode* root);

TreeNode* insert(TreeNode* root, int data);

TreeNode* leftRotate(TreeNode* root);

TreeNode* rightRotate(TreeNode* root);

void breadthPrint(TreeNode* root, ostream &output);
Node* newNode(TreeNode* data);
LinkedList* newLinkedList();

void enq(LinkedList* ll, TreeNode* data);
TreeNode* deq(LinkedList* ll);



int main(){
    TreeNode* root = 0;
    ifstream in = ifstream("input.txt");
    ofstream out = ofstream("output.txt");
    int num;
    while(in >> num){
        root = insert(root, num);
        cout << "After inserting " << num << ": " << endl;
        breadthPrint(root, cout);
        cout << endl;
    }
    breadthPrint(root, out);
    return 0;
}



TreeNode* newTreeNode(int data){
    TreeNode* ret = new TreeNode;
    ret->leftChild = 0;
    ret->rightChild = 0;
    ret->data = data;
    ret->height = 0;
    return ret;
}

int getBalance(TreeNode* root){
    int left = 0;
    int right = 0;
    if(root){
        left = (root->leftChild) ? root->leftChild->height : -1;
        right = (root->rightChild) ? root->rightChild->height : -1;
    }
    return left - right;
}

TreeNode* rebalance(TreeNode* root){
    TreeNode* ret = root;
    if(root){
        setHeights(root);
        int balance = getBalance(root);
        //rotations
        //https://stackoverflow.com/questions/19278236/avl-tree-balance
        if(balance > 1){
            //left heavy
            if(getBalance(root->leftChild) < 0){
                //left heavy inner
                leftRotate(root->leftChild);
            }
            ret = rightRotate(root);
        } else if(balance < -1){
            //right heavy
            if(getBalance(root->rightChild) > 0){
                //right heavy inner
                rightRotate(root->rightChild);
            }
            ret = leftRotate(root);
        }
    }
    return ret;
}

void setHeights(TreeNode* root){
    if(root){
        setHeights(root->leftChild);
        setHeights(root->rightChild);
        int left = (root->leftChild) ? root->leftChild->height : -1;
        int right = (root->rightChild) ? root->rightChild->height : -1;
        root->height = max(left, right) + 1;
    }
}

TreeNode* insert(TreeNode* root, int data){
    if(!root){
        root = newTreeNode(data);
    } else if(data < root->data){
        root->leftChild = insert(root->leftChild, data);
    } else {
        root->rightChild = insert(root->rightChild, data);
    }
    root = rebalance(root);
    return root;
}

TreeNode* leftRotate(TreeNode* root){
    TreeNode* newRoot = root;
    if(root){
        newRoot = root->rightChild;
        if(root->rightChild){
            root->rightChild = newRoot->leftChild;
            newRoot->leftChild = root;
            setHeights(newRoot);
        }
    }
    return newRoot;
}

TreeNode* rightRotate(TreeNode* root){
    TreeNode* newRoot = root;
    if(root){
        newRoot = root->leftChild;
        if(root->leftChild){
            root->leftChild = newRoot->rightChild;
            newRoot->rightChild = root;
            setHeights(newRoot);
        }
    }

    return newRoot;
}

void breadthPrint(TreeNode* root, ostream &output){
    if(!root){
        return;
    }
    LinkedList* currLv = newLinkedList();
    TreeNode* curr = root;
    enq(currLv, curr);
    while(currLv->head){
        LinkedList* nextLv = newLinkedList();
        while(currLv->head){
            curr = deq(currLv);
            output << "Data: " << curr->data << " Height: " << curr->height << " Balance: " << getBalance(curr);

            if(curr->leftChild){
                enq(nextLv, curr->leftChild);
                output << " Left child is " << curr->leftChild->data << " ";
            }
            if(curr->rightChild){
                enq(nextLv, curr->rightChild);
                output << " Right child is " << curr->rightChild->data << " ";
            }
            output << " | ";
        }

        currLv = nextLv;
        output << endl;
    }
}

Node* newNode(TreeNode* data){
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

void enq(LinkedList* ll, TreeNode* data){
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
TreeNode* deq(LinkedList* ll){
    TreeNode* ret = 0;
    if(ll->head){
        ret = ll->head->data;
        ll->head = ll->head->next;
        if(ll->head){
            ll->head->prev = 0;
        }
    }
    return ret;
}
