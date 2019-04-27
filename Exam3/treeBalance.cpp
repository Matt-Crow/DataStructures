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

TreeNode* insert(TreeNode* &root, int data);

TreeNode* leftRotate(TreeNode* root);

TreeNode* rightRotate(TreeNode root);

void breadthPrint(TreeNode* root, ostream &output);
Node* newNode(TreeNode* data);
LinkedList* newLinkedList();

void enq(LinkedList* ll, TreeNode* data);
TreeNode* deq(LinkedList* ll);

int main(){
    TreeNode* root = 0;
    for(int i = 1; i < 10; i++){
        insert(root, i);
        cout << "After inserting " << i << ": " << endl;
        breadthPrint(root, cout);
        cout << endl;
    }
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
    int left = (root->leftChild) ? root->leftChild->height : 0;
    int right = (root->rightChild) ? root->rightChild->height : 0;
    return left - right;
}

TreeNode* rebalance(TreeNode* root){
    TreeNode* ret = root;
    if(root){
        int left = (root->leftChild) ? root->leftChild->height : 0;
        int right = (root->rightChild) ? root->rightChild->height : 0;
        root->height = max(left, right) + 1;
        int balance = getBalance(root);
        //rotations
        //if left heavy outside, ret = rightRotate<T>(root);
        //else if right heavy outside, ret = leftRotate<T>(root);
        //else if left heavy inside, leftRotate<T>(root->leftChild), ret = rightRotate<T>(root)
        //else if right heavy inside, rightRotate<T>(root->rightChild), ret = leftRotate<T>(root)
    }
    return root;
}

TreeNode* insert(TreeNode* &root, int data){
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
    TreeNode* x = root->rightChild;
    //rotate to the left, update root and x's heights
    return x;
}

TreeNode* rightRotate(TreeNode* root){
    TreeNode* x = root->leftChild;
    //rotate to the right, update root and x's heights
    return x;
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
