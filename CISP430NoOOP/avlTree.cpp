#include <iostream>
#include "misc.h"

using namespace std;

struct treeNode{
    int data;
    treeNode* left;
    treeNode* right;
    int height;
};

treeNode* newTreeNode(int data);

void insert(treeNode* &root, int data);

bool deleteNode(treeNode* &root, int withValue);

void rebalance(treeNode* &root);
void leftRotate(treeNode* &root);
void rightRotate(treeNode* &root);

void preOrder(treeNode* root, ostream &output);

void inOrder(treeNode* root, ostream &output);

void postOrder(treeNode* root, ostream &output);

void breadthPrint(treeNode* root, ostream &output);

void printTree(treeNode* root);

bool inTree(treeNode* root, int val);

void setHeights(treeNode* root);
int getBalance(treeNode* root);



int useAvlTree(){
    treeNode* root = 0;
    int ip = 0;
    bool b = false;

    cout << "===AVL TREE===" << endl;
    while(ip != -1){
        cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
        cout << "Choose an option: " << endl;
        cout << "0: print the tree pre-order" << endl;
        cout << "1: print the tree in-order" << endl;
        cout << "2: print the tree post-order" << endl;
        cout << "3: print the tree breadth-print" << endl;
        cout << "4: print the tree (address format)" << endl;
        cout << "5: insert into the tree" << endl;
        cout << "6: delete a node from the tree" << endl;
        cout << "7: check if a number exists in the tree" << endl;
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
            printTree(root);
            break;
        case 5:
            cout << "Enter value to insert: ";
            cin >> ip;
            insert(root, ip);
            ip = 5;
            break;
        case 6:
            cout << "Enter value to delete: ";
            cin >> ip;

            b = deleteNode(root, ip);
            if(b){
                cout << ip << " was deleted" << endl;
            } else {
                cout << ip << " was not deleted" << endl;
            }
            ip = 6;
            break;
        case 7:
            cout << "Enter value to search for: ";
            cin >> ip;
            b = inTree(root, ip);
            if(b){
                cout << ip << " is in the tree" << endl;
            } else {
                cout << ip << " is not in the tree" << endl;
            }
            ip = 7;
            break;
        }
    }
    if(root){
        delete root;
    }

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

    setHeights(root);
    rebalance(root);
}

bool deleteNode(treeNode* &root, int withValue){
    bool deleted = false;
    if(root){
        if(root->data == withValue){
            deleted = true;
            if(!(root->left || root->right)){
                //root is only node in the tree
                delete root;
                root = 0;
            } else if(root->left && root->right){
                //2 children
                treeNode* temp = root->right;
                //either go right by one, and keep going left,
                //or go left by one, and keep going right,
                //it doesn't matter which
                while(temp->left){
                    temp = temp->left;
                }
                int newVal = temp->data;

                //delete the node I will swap with
                deleteNode(root, temp->data);
                //take that node's data
                root->data = newVal;
                //have to do in this order, otherwise root will be deleted
                delete temp;
            } else if(root->left){
                root = root->left;
            } else if(root->right){
                root = root->right;
            }
        } else if(root->data > withValue && root->left){
            deleted = deleteNode(root->left, withValue);
        } else if(root->data < withValue && root->right){
            deleted = deleteNode(root->right, withValue);
        }
    }

    setHeights(root);
    rebalance(root);
    return deleted;
}

void rebalance(treeNode* &root){
    if(root){
        int balance = getBalance(root);
        if(balance > 1){
            //left heavy
            if(getBalance(root->left) < 0){
                //left heavy inner
                leftRotate(root->left);
            }
            rightRotate(root);
        } else if(balance < -1){
            //right heavy
            if(getBalance(root->right) > 0){
                //right heavy inner
                rightRotate(root->right);
            }
            leftRotate(root);
        }
    }
}

void leftRotate(treeNode* &root){
    if(root){
        if(root->right){
            treeNode* temp = root;
            root = root->right;
            temp->right = root->left;
            root->left = temp;
            setHeights(root);
        }
    }
}
void rightRotate(treeNode* &root){
    if(root){
        if(root->left){
            treeNode* temp = root;
            root = root->left;
            temp->left = root->right;
            root->right = temp;
            setHeights(root);
        }
    }
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
    //can't do T is pointer type?
    /*
    linkedList<treeNode>* currLv = newLinkedList<treeNode>();
    treeNode* curr = root;
    enqueue(currLv, *root);

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

    delete currLv;
    */
}

void printTree(treeNode* root){
    if(!root){
        return;
    }
    cout << "Node " << root << " (" << root->data << ")" << endl;
    cout << "Height is " << root->height << endl;
    cout << "Balance is " << getBalance(root) << endl;
    if(root->left){
        cout << "   Left child: " << root->left << " (" << root->left->data << ")" << endl;
    }
    if(root->right){
        cout << "   Right child: " << root->right << " (" << root->right->data << ")" << endl;
    }
    if(root->left){
        printTree(root->left);
    }
    if(root->right){
        printTree(root->right);
    }
}

bool inTree(treeNode* root, int val){
    if(!root){
        return false;
    } else if(root->data == val){
        cout << root->data << " ";
        return true;
    } else if(root->data > val && root->left){
        cout << root->data << " ";
        return inTree(root->left, val);
    } else if(root->data < val && root->right){
        cout << root->data << " ";
        return inTree(root->right, val);
    } else {
        cout << root->data << " ";
        return false;
    }
}

void setHeights(treeNode* root){
    if(root){
        setHeights(root->left);
        setHeights(root->right);
        int left = (root->left) ? root->left->height : -1;
        int right = (root->right) ? root->right->height : -1;
        root->height = max(left, right) + 1;
    }
}
int getBalance(treeNode* root){
    int left = 0;
    int right = 0;
    if(root){
        left = (root->left) ? root->left->height : -1;
        right = (root->right) ? root->right->height : -1;
    }
    return left - right;
}
