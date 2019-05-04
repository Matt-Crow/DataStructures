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

TreeNode* sortedArrayToTree(int a[], int start, int end);
TreeNode* unsortedArrayToTree(int a[], int idx, int length);

int getArraySize(TreeNode* root);
void populateArray(TreeNode* root, int a[], int idx, int arrSize);

void inOrder(TreeNode* root, ostream &output);
void print(int a[], int len);

//temp
void printTree(TreeNode* root);

const int NULL_VALUE = 0;

int main(){
    int temp[] = {1, 2, 3, 4, 5, 6, 7}; //todo read from file
    TreeNode* root = 0;

    cout << "Original array: " << endl;
    print(temp, 7);

    cout << "Converted to binary tree: " << endl;
    root = sortedArrayToTree(temp, 0, 6);
    inOrder(root, cout);

    cout << "Unsorted: " << endl;
    int arraySize = getArraySize(root);
    int unsorted[arraySize];
    populateArray(root, unsorted, 0, arraySize);
    cout << "A" << arraySize << endl;
    print(unsorted, arraySize);

    cout << "Unsorted to tree: " << endl;
    root = unsortedArrayToTree(unsorted, 0, arraySize);
    inOrder(root, cout);
    return 0;

    for(int i = 1; i < 10; i++){
        insert(root, i);
        cout << "After inserting " << i << ": " << endl;
        printTree(root);
    }
    //convert tree to array
    setHeights(root);
    arraySize = getArraySize(root);
    int a[arraySize];
    populateArray(root, a, 0, arraySize);
    print(a, arraySize);
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



//done with balancing tree
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


TreeNode* sortedArrayToTree(int a[], int start, int end){
    TreeNode* ret = 0;
    if(start <= end){
        int mid = (start + end) / 2;
        ret = newTreeNode(a[mid]);
        ret->leftChild = sortedArrayToTree(a, start, mid - 1);
        ret->rightChild = sortedArrayToTree(a, mid + 1, end);
    }
    return ret;
}

TreeNode* unsortedArrayToTree(int a[], int idx, int length){
    TreeNode* ret = 0;
    if(a[idx] != NULL_VALUE){
        ret = newTreeNode(a[idx]);
        if(idx * 2 + 2 < length){
            ret->leftChild = unsortedArrayToTree(a, idx * 2 + 1, length);
            ret->rightChild = unsortedArrayToTree(a, idx * 2 + 2, length);
        }
    }
    return ret;
}


int getArraySize(TreeNode* root){
    int s = 1;
    setHeights(root);
    if(root){
        // 2^(root->height + 1) - 1
        for(int i = 0; i < root->height + 1; i++){
            s *= 2;
        }
        s--;
    }
    return s;
}

void populateArray(TreeNode* root, int a[], int idx, int arrSize){
    if(root){
        a[idx] = root->data;
        print(a, arrSize);
        if(2 * idx + 1 < arrSize){
            populateArray(root->leftChild, a, 2 * idx + 1, arrSize);
        }
        if(2 * idx + 2 < arrSize){
            populateArray(root->rightChild, a, 2 * idx + 2, arrSize);
        }
    }
}

void inOrder(TreeNode* root, ostream &output){
    if(root){
        inOrder(root->leftChild, output);
        output << root->data << " ";
        inOrder(root->rightChild, output);
    }
}
void print(int a[], int len){
    for(int i = 0; i < len; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}
