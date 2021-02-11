#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

BinaryTree* newBinaryTree(int val){
    BinaryTree* ret = (BinaryTree*)malloc(sizeof(BinaryTree));
    ret->value = val;
    ret->left = 0;
    ret->right = 0;
    return ret;
}
void deleteBinaryTree(BinaryTree** root){
    if(root){
        BinaryTree* ptr = *root;
        if(ptr->left){
            deleteBinaryTree(&(ptr->left));
        }
        if(ptr->right){
            deleteBinaryTree(&(ptr->right));
        }
        printf("deleted %i\n", ptr->value);
        free(*root);
        *root = 0;
    }
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
bool deleteFromTree(BinaryTree** root, int val){
    bool deleted = false;
    if(root && *root){
        BinaryTree* curr = *root;
        if(curr->value > val){
            if(curr->left){
                deleted = deleteFromTree(&(curr->left), val);
            }
        } else if(curr->value < val){
            if(curr->right){
                deleted = deleteFromTree(&(curr->right), val);
            }
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

int testBinaryTree(){
    BinaryTree* root = 0;
    BinaryTree* temp = 0;
    int ip = 0;
    bool success;
    int* a = 0;
    do {
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the binary tree in order\n");
        printf("%s", "1: Print the binary tree pre-order\n");
        printf("%s", "2: Print the binary tree post-order\n");
        printf("%s", "3: Insert into the binary tree\n");
        printf("%s", "4: Delete the binary tree\n");
        printf("%s", "5: Convert the binary tree to an array\n");
        printf("%s", "6: Convert [1, 2, 3, 4, 5, 6, 7] to a binary tree\n");
        printf("%s", "7: Convert [5, 1, 3, 2, 4] to a binary tree\n");
        printf("%s", "8: Delete from the binary tree\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);

        switch(ip){
            case 0:
                inOrder(root);
                printf("%s", "\n");
                break;
            case 1:
                preOrder(root);
                printf("%s", "\n");
                break;
            case 2:
                postOrder(root);
                printf("%s", "\n");
                break;
            case 3:
                printf("%s", "enter a value to insert: ");
                scanf("%d", &ip);
                success = insertIntoTree(&root, ip);
                if(success){
                    printf("%i %s", ip, "was inserted\n");
                } else {
                    printf("%i %s", ip, "is already in the tree\n");
                }
                ip = 1;
                break;
            case 4:
                deleteBinaryTree(&root);
                root = 0;
                break;
            case 5:
                a = toArray(root);
                ip = getArraySize(root);
                printf("%s", "[");
                for(int i = 0; i < ip - 1; i++){
                    printf("%i, ", a[i]);
                }
                if(ip >= 0){
                    printf("%i", a[ip - 1]);
                }
                printf("%s", "]\n");
                if(a){
                    free(a);
                    a = 0;
                }
                ip = 3;
                break;
            case 6: {
                int arr[] = {1, 2, 3, 4, 5, 6, 7};
                temp = fromSortedArray(arr, 7);
                inOrder(temp);
                printf("%s", "\n");
                deleteBinaryTree(&temp);
                temp = 0;
                break;
            }
            case 7: {
                int arr[] = {5, 1, 3, 2, 4};
                temp = fromUnsoredArray(arr, 5);
                inOrder(temp);
                printf("%s", "\n");
                deleteBinaryTree(&temp);
                temp = 0;
                break;
            }
            case 8:
                printf("%s", "enter a value to delete: ");
                scanf("%d", &ip);
                success = deleteFromTree(&root, ip);
                if(success){
                    printf("%i was deleted from the tree.\n", ip);
                } else {
                    printf("%i is not in the tree.\n", ip);
                }
                ip = 6;
                break;
        }
    } while(ip != -1);

    if(root){
        deleteBinaryTree(&root);
        root = 0;
    }

    return 0;
}
