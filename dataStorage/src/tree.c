#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "tree.h"

struct BinaryTree* newBinaryTree(int val){
    struct BinaryTree* ret = (struct BinaryTree*)malloc(sizeof(struct BinaryTree));
    ret->value = val;
    ret->left = 0;
    ret->right = 0;
    return ret;
}

void deleteBinaryTree(struct BinaryTree* root){
    if(root){
        deleteBinaryTree(root->left);
        deleteBinaryTree(root->right);
        printf("deleted %i\n", root->value);
        delete root;
        root = 0;
    }
}

bool insertIntoTree(struct BinaryTree** root, int val){
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


int getHeight(struct BinaryTree* root){
    int ret = -1;
    if(root){
        int left = getHeight(root->left);
        int right = getHeight(root->right);
        ret = (left > right) ? left : right; //larger height between those of root's left and right children
        ret++; //one more for root
    }
    return ret;
}

int getArraySize(struct BinaryTree* root){
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

void populateArray(struct BinaryTree* root, int* a, int aLen, int idx){
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
int* toArray(struct BinaryTree* root){
    int* ret = 0;
    if(root){
        int len = getArraySize(root);
        ret = (int*)malloc(sizeof(int) * len);
        memset(ret, 0, len * sizeof(int));
        populateArray(root, ret, len, 0);
    }
    return ret;
}

struct BinaryTree* fromSortedArrayIdx(int* a, int start, int end){
    struct BinaryTree* ret = 0;
    if(start <= end && a){
        int mid = (start + end) / 2;
        ret = newBinaryTree(a[mid]);
        ret->left = fromSortedArrayIdx(a, start, mid - 1);
        ret->right = fromSortedArrayIdx(a, mid + 1, end);
    }
    return ret;
}

struct BinaryTree* fromSortedArray(int* a, int len){
    return fromSortedArrayIdx(a, 0, len - 1);
}

struct BinaryTree* fromUnsoredArrayIdx(int* a, int len, int idx){
    struct BinaryTree* ret = 0;
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

struct BinaryTree* fromUnsoredArray(int* a, int len){
    return fromUnsoredArrayIdx(a, len, 0);
}

void inOrder(struct BinaryTree* root){
    if(root){
        inOrder(root->left);
        printf("%i ", root->value);
        inOrder(root->right);
    }
}

int testBinaryTree(){
    struct BinaryTree* root = 0;
    struct BinaryTree* temp = 0;
    int ip = 0;
    bool success;
    int* a = 0;
    do {
        printf("%s", "Choose an option:\n");
        printf("%s", "0: Print the binary tree in order\n");
        printf("%s", "1: Insert into the binary tree\n");
        printf("%s", "2: Delete the binary tree\n");
        printf("%s", "3: Convert the binary tree to an array\n");
        printf("%s", "4: Convert [1, 2, 3, 4, 5, 6, 7] to a binary tree\n");
        printf("%s", "5: Convert [5, 1, 3, 2, 4] to a binary tree\n");
        printf("%s", "-1: Quit\n");
        scanf("%d", &ip);

        switch(ip){
            case 0:
                inOrder(root);
                printf("%s", "\n");
                break;
            case 1:
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
            case 2:
                deleteBinaryTree(root);
                root = 0;
                break;
            case 3:
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
            case 4:
                a = new int[7]{1, 2, 3, 4, 5, 6, 7};
                temp = fromSortedArray(a, 7);
                inOrder(temp);
                printf("%s", "\n");
                deleteBinaryTree(temp);
                temp = 0;
                delete a;
                break;
            case 5:
                a = new int[5]{5, 1, 3, 2, 4};
                temp = fromUnsoredArray(a, 5);
                inOrder(temp);
                printf("%s", "\n");
                deleteBinaryTree(temp);
                temp = 0;
                delete a;
                break;
        }
    } while(ip != -1);

    if(root){
        deleteBinaryTree(root);
        root = 0;
    }

    return 0;
}
