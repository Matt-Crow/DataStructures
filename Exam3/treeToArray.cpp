#include <iostream>
#include <fstream>

using namespace std;

struct TreeNode{
    int data;
    TreeNode* leftChild;
    TreeNode* rightChild;
    int height;
};

TreeNode* newTreeNode(int data);
int getBalance(TreeNode* root);
void leftRotate(TreeNode* &root);
void rightRotate(TreeNode* &root);
void setHeights(TreeNode* root);
void rebalance(TreeNode* &root);
void insert(TreeNode* &root, int data);

//temp
void printTree(TreeNode* root);

int main(){
    TreeNode* root = 0;
    for(int i = 1; i < 7; i++){
        insert(root, i);
        cout << "After inserting " << i << ": " << endl;
        printTree(root);
    }
    return 0;
}

//temp
void printTree(TreeNode* root){
    cout << "Node " << root << endl;
    cout << "Left child: " << root->leftChild << endl;
    cout << "Right child: " << root->rightChild << endl;
    cout << "Data: " << root->data << endl;
    cout << "Height: " << root->height << endl;
    cout << "Balance: " << getBalance(root) << endl;
    cout << endl;
    if(root->leftChild){
        printTree(root->leftChild);
    }
    if(root->rightChild){
        printTree(root->rightChild);
    }
}



TreeNode* newTreeNode(int data){
    TreeNode* ret = new TreeNode;
    ret->data = data;
    ret->leftChild = 0;
    ret->rightChild = 0;
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

void setHeights(TreeNode* root){
    if(root){
        setHeights(root->leftChild);
        setHeights(root->rightChild);
        int left = (root->leftChild) ? root->leftChild->height : -1;
        int right = (root->rightChild) ? root->rightChild->height : -1;
        root->height = max(left, right) + 1;
    }
}

void leftRotate(TreeNode* &root){
    if(root){
        if(root->rightChild){
            TreeNode* temp = root;
            root = root->rightChild;
            temp->rightChild = root->leftChild;
            root->leftChild = temp;
            setHeights(root);
            temp = 0;
            delete temp;
        }
    }
}

void rightRotate(TreeNode* &root){
    if(root){
        if(root->leftChild){
            TreeNode* temp = root;
            root = root->leftChild;
            temp->leftChild = root->rightChild;
            root->rightChild = temp;
            setHeights(root);
            temp = 0;
            delete temp;
        }
    }
}

void rebalance(TreeNode* &root){
    if(root){
        int balance = getBalance(root);
        if(balance > 1){
            //left heavy
            if(getBalance(root->leftChild) < 0){
                //left heavy inner
                leftRotate(root->leftChild);
            }
            rightRotate(root);
        } else if(balance < -1){
            //right heavy
            if(getBalance(root->rightChild) > 0){
                //right heavy inner
                rightRotate(root->rightChild);
            }
            leftRotate(root);
        }
    }
}

void insert(TreeNode* &root, int data){
    if(!root){
        root = newTreeNode(data);
    } else if(data < root->data){
        insert(root->leftChild, data);
    } else {
        insert(root->rightChild, data);
    }
    setHeights(root);
    rebalance(root);
}
