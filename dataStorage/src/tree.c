#include "tree.h"
#include "core.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

BinaryTree* newBinaryTree(int val){
    BinaryTree* ret = (BinaryTree*)malloc(sizeof(BinaryTree));
    ret->value = val;
    ret->left = 0;
    ret->right = 0;
    return ret;
}
void deleteBinaryTree(BinaryTree** root){
    if(root && *root){
        BinaryTree* ptr = *root;
        deleteBinaryTree(&(ptr->left));
        deleteBinaryTree(&(ptr->right));
        printf("deleted %i\n", ptr->value);
        free(ptr);
        *root = 0;
    }
}

bool isInTree(BinaryTree* root, int val){
    bool found = false;
    BinaryTree* curr = root;
    while(curr && !found){
        if(curr->value > val){
            curr = curr->left;
        } else if(curr->value < val){
            curr = curr->right;
        } else {
            found = true;
        }
    }
    curr = 0;
    return found;
}

// untested
BinaryTree* locateInTree(BinaryTree* root, int val){
    BinaryTree* curr = root;
    while(curr && curr->value != val){
        if(curr->value > val){
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    } // breaks when curr is in the place val should exist or contains val
    return curr;
}

bool insertIntoTree(BinaryTree** root, int val){
    bool inserted = false;
    if(root){
        //if root is null pointer, there is nothing I can do with it.
        if(*root){
            //root has been allocated
            if((*root)->value > val){
                inserted = insertIntoTree(&((*root)->left), val);
            } else if((*root)->value < val){
                inserted = insertIntoTree(&((*root)->right), val);
            } else {
                //value already in tree, do not insert
            }
        } else {
            *root = newBinaryTree(val);
            inserted = true;
        }
    }
    return inserted;
}

// untested
bool insertIter(BinaryTree** root, int val){
    bool inserted = false;
    if(root){ // can't do anything with null pointer
        BinaryTree** insertHere = root;
        while(*insertHere && (*insertHere)->value != val){
            if((*insertHere)->value > val){
                insertHere = &((*insertHere)->left);
            } else if((*insertHere)->value < val){
                insertHere = &((*insertHere)->right);
            }
        } // breaks when *insertHere is null or holds val
        if(*insertHere){
            // already exists
        } else {
            inserted = true;
            *insertHere = newBinaryTree(val);
        }
    }
    return inserted;
}

bool deleteFromTree(BinaryTree** root, int val){
    bool deleted = false;
    if(root && *root){
        BinaryTree* curr = *root;
        if(curr->value > val){
            deleted = deleteFromTree(&(curr->left), val);
        } else if(curr->value < val){
            deleted = deleteFromTree(&(curr->right), val);
        } else {
            deleted = true;
            BinaryTree* deleteMe = curr;
            if(!(deleteMe->left || deleteMe->right)){
                //no children
                free(deleteMe);
                *root = 0;
            } else if(deleteMe->left && deleteMe->right){
                //2 children
                BinaryTree* swapMe = deleteMe->right;
                /*
                can either go right one, then keep going left,
                or left one, then keep going right
                */
                while(swapMe->left){
                    swapMe = swapMe->left;
                }

                int newVal = swapMe->value;

                deleteFromTree(root, swapMe->value);
                // delete the node I swapped with.
                swapMe = 0; //freed by deleteFromTree

                deleteMe->value = newVal;
                // old value has been "deleted"
            } else if(deleteMe->left){
                *root = deleteMe->left; //move root
                deleteMe->left = 0;
                free(deleteMe);
            } else if(deleteMe->right){
                *root = deleteMe->right;
                deleteMe->right = 0;
                free(deleteMe);
            } else {
                //will never go here
            }
        }
    }
    return deleted;
}

int getHeight(BinaryTree* root){
    int ret = -1; // height of null is -1
    if(root){
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        ret = (left > right) ? left : right; //larger height between those of root's left and right children
        ret++; //one more for root
    }
    return ret;
}

int getArraySize(BinaryTree* root){
    int ret = 1;
    int height = getHeight(root);
    // if root is null, height is -1
    // 2^(height + 1) - 1;
    for(int i = 0; i < height + 1; i++){
        ret *= 2;
    }
    ret--;
    return ret;
}

void populateArray(BinaryTree* root, int* a, int aLen, int idx){
    if(root && a){
        if(idx >= 0 && idx < aLen){
            a[idx] = root->value;
        }
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;
        if(left >= 0 && left < aLen){
            populateArray(root->left, a, aLen, left);
        }
        if(right >= 0 && right < aLen){
            populateArray(root->right, a, aLen, right);
        }
    }
}
int* toArray(BinaryTree* root){
    int* ret = 0;
    if(root){
        int len = getArraySize(root);
        ret = (int*)malloc(sizeof(int) * len);
        memset(ret, 0, len * sizeof(int));
        populateArray(root, ret, len, 0);
    }
    return ret;
}

BinaryTree* fromSortedArrayIdx(int* a, int start, int end){
    BinaryTree* ret = 0;
    if(start <= end && a){
        int mid = (start + end) / 2;
        ret = newBinaryTree(a[mid]);
        ret->left = fromSortedArrayIdx(a, start, mid - 1);
        ret->right = fromSortedArrayIdx(a, mid + 1, end);
    }
    return ret;
}

BinaryTree* fromSortedArray(int* a, int len){
    return fromSortedArrayIdx(a, 0, len - 1);
}

BinaryTree* fromUnsoredArrayIdx(int* a, int len, int idx){
    BinaryTree* ret = 0;
    if(a){
        if(idx >= 0 && idx < len){
            int left = 2 * idx + 1;
            int right = 2 * idx + 2;
            ret = newBinaryTree(a[idx]);
            ret->left = fromUnsoredArrayIdx(a, len, left);
            ret->right = fromUnsoredArrayIdx(a, len, right);
        }
    }
    return ret;
}

BinaryTree* fromUnsoredArray(int* a, int len){
    return fromUnsoredArrayIdx(a, len, 0);
}

void inOrder(BinaryTree* root){
    if(root){
        inOrder(root->left);
        printf("%i ", root->value);
        inOrder(root->right);
    }
}
void preOrder(BinaryTree* root){
    if(root){
        printf("%i ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}
void postOrder(BinaryTree* root){
    if(root){
        postOrder(root->left);
        postOrder(root->right);
        printf("%i ", root->value);
    }
}

BinaryTree* asTreePtr(void** dataStructure){
    BinaryTree** ptrPtr = (BinaryTree**)dataStructure;
    return *ptrPtr;
}

void doPrintInOrder(void** dataStructure){
    inOrder(asTreePtr(dataStructure));
    printf("%c", '\n');
}

void doPrintPreOrder(void** dataStructure){
    preOrder(asTreePtr(dataStructure));
    printf("%c", '\n');
}

void doPrintPostOrder(void** dataStructure){
    postOrder(asTreePtr(dataStructure));
    printf("%c", '\n');
}

void doInsertBinaryTree(void** dataStructure){
    printf("%s", "enter a value to insert: ");
    int ip;
    scanf("%d", &ip);
    bool success = insertIntoTree((BinaryTree**)dataStructure, ip);
    if(success){
        printf("%i %s", ip, "was inserted\n");
    } else {
        printf("%i %s", ip, "is already in the tree\n");
    }
}

void doSearchBinaryTree(void** dataStructure){
    printf("%s", "enter a value to search for: ");
    int ip;
    scanf("%d", &ip);
    bool success = isInTree(asTreePtr(dataStructure), ip);
    if(success){
        printf("%i is in the tree.\n", ip);
    } else {
        printf("%i is not in the tree.\n", ip);
    }
}

void doDeleteFromBinaryTree(void** dataStructure){
    printf("%s", "enter a value to delete: ");
    int ip;
    scanf("%d", &ip);
    bool success = deleteFromTree((BinaryTree**)dataStructure, ip);
    if(success){
        printf("%i was deleted from the tree.\n", ip);
    } else {
        printf("%i is not in the tree.\n", ip);
    }
}

void doDeleteBinaryTree(void** dataStructure){
    deleteBinaryTree((BinaryTree**)dataStructure);
}

void doConvertBinaryTreeToArray(void** dataStructure){
    BinaryTree* root = asTreePtr(dataStructure);
    int* a = toArray(root);
    int size = getArraySize(root);
    printf("%s", "[");
    for(int i = 0; i < size - 1; i++){
        printf("%d, ", a[i]);
    }
    if(size > 0){
        printf("%d", a[size - 1]);
    }
    printf("%s", "]\n");
    if(a){
        free(a);
    }
}

void doConvertSortedArrayToBinaryTree(void** dataStructure){
    int arr[] = {1, 2, 3, 4, 5, 6, 7};
    BinaryTree* temp = fromSortedArray(arr, 7);
    inOrder(temp);
    printf("%s", "\n");
    deleteBinaryTree(&temp);
}

void doConvertUnsortedArrayToBinaryTree(void** dataStructure){
    int arr[] = {5, 1, 3, 2, 4};
    BinaryTree* temp = fromUnsoredArray(arr, 5);
    inOrder(temp);
    printf("%s", "\n");
    deleteBinaryTree(&temp);
}



int testBinaryTree(){
    BinaryTree* root = 0;

    printf("%s\n", "Binary Search Tree");

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("Print the binary tree in order", &doPrintInOrder),
        newConsumerMenuOption("Print the binary tree pre-order", &doPrintPreOrder),
        newConsumerMenuOption("Print the binary tree post-order", &doPrintPostOrder),
        newConsumerMenuOption("Insert into the binary tree", &doInsertBinaryTree),
        newConsumerMenuOption("Search the binary tree", &doSearchBinaryTree),
        newConsumerMenuOption("Delete from the binary tree", &doDeleteFromBinaryTree),
        newConsumerMenuOption("Delete the binary tree", &doDeleteBinaryTree),
        newConsumerMenuOption("Convert the binary tree to an array", &doConvertBinaryTreeToArray),
        newConsumerMenuOption("Convert [1, 2, 3, 4, 5, 6, 7] to a binary tree", &doConvertSortedArrayToBinaryTree),
        newConsumerMenuOption("Convert [5, 1, 3, 2, 4] to a binary tree", &doConvertUnsortedArrayToBinaryTree)
    };
    int numOptions = sizeof(options) / sizeof(options[0]);

    doConsumerMenu(options, numOptions, (void**)&root);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteBinaryTree(&root);

    return 0;
}
