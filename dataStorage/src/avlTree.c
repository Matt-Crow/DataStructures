#include "avlTree.h"
#include "core.h"
#include<stdio.h>
#include<stdlib.h>

/*
Private functions
*/

/*
A positive number denotes left -heaviness
A negative number denotes right-heaviness
*/
int getBalance(AvlTreeNode* root){
    int balance = 0;
    if(root){
        balance = getAvlHeight(root->left) - getAvlHeight(root->right);
    }
    return balance;
}

/*
This assumes the heights of root's childen have already been updated.
Pro-tip: call this after recursive calls
*/
void setHeight(AvlTreeNode* root){
    if(root){
        int h1 = getAvlHeight(root->left);
        int h2 = getAvlHeight(root->right);
        root->height = ((h1 > h2) ? h1 : h2) + 1;
    }
}
/*
 *      (4)
 *     /   \
 *   (2)    (6)
 *  /  \    /  \
 * (1) (3) (5) (7)
 *
 * leftRotate((4)):
 *         (6)
 *        /   \
 *      (4)   (7)
 *     /   \
 *   (2)   (5)
 *  /   \
 * (1)  (3)
 */
void leftRotate(AvlTreeNode** root){
    if(root && *root){
        AvlTreeNode* oldRoot = *root;
        AvlTreeNode* newRoot = oldRoot->right;
        *root = newRoot;
        oldRoot->right = newRoot->left;
        newRoot->left = oldRoot;
        // need to update in this order
        setHeight(oldRoot);
        setHeight(newRoot);
    }
}

/*
 *      (4)
 *    /     \
 *  (2)     (6)
 * /  \     / \
 *(1) (3) (5) (7)
 *
 * to
 *
 *      (2)
 *    /     \
 *  (1)     (4)
 *          / \
 *        (3) (6)
 *            / \
 *          (5) (7)
 */
void rightRotate(AvlTreeNode** root){
    if(root && *root){
        AvlTreeNode* oldRoot = *root;
        AvlTreeNode* newRoot = oldRoot->left;
        *root = newRoot;
        oldRoot->left = newRoot->right;
        newRoot->right = oldRoot;
        // need to update in this order
        setHeight(oldRoot);
        setHeight(newRoot);
    }
}
void rebalance(AvlTreeNode** root){
    if(root && *root){
        AvlTreeNode* node = *root;

        setHeight(node);

        int balance = getBalance(node);
        if(balance > 1){ // left heavy
            if(getBalance(node->left) < 0){ // left heavy inner
                leftRotate(&(node->left));
            }
            rightRotate(root);
        } else if(balance < -1){ // right heavy
            if(getBalance(node->right) > 0){ // right heavy inner
                rightRotate(&(node->right));
            }
            leftRotate(root);
        } // else, is OK
    }
}

/*
These are needed for breadth printing
*/
typedef struct AvlTreeQueueNode {
    AvlTreeNode* value;
    struct AvlTreeQueueNode* next;
} AvlTreeQueueNode;

typedef struct AvlTreeQueue {
    AvlTreeQueueNode* head;
    AvlTreeQueueNode* tail;
} AvlTreeQueue;

AvlTreeQueueNode* newAvlTreeQueueNode(AvlTreeNode* value){
    AvlTreeQueueNode* q = (AvlTreeQueueNode*)malloc(sizeof(AvlTreeQueueNode));
    q->value = value;
    q->next = 0;
    return q;
}
AvlTreeQueue* newAvlTreeQueue(){
    AvlTreeQueue* q = (AvlTreeQueue*)malloc(sizeof(AvlTreeQueue));
    q->head = 0;
    q->tail = 0;
    return q;
}
void deleteAvlTreeQueueNode(AvlTreeQueueNode** queue){
    if(queue && *queue){
        free(*queue);
        *queue = 0;
    }
}
void deleteAvlTreeQueue(AvlTreeQueue** queue){
    if(queue && *queue){
        free(*queue);
        *queue = 0;
    }
}
void enqueueAvlTreeQueue(AvlTreeQueue* queue, AvlTreeNode* value){
    if(queue){ // not passed null-pointer
        AvlTreeQueueNode* nn = newAvlTreeQueueNode(value);
        if(queue->head){
            queue->tail->next = nn;
        } else {
            queue->head = nn;
        }
        queue->tail = nn;
    }
}
AvlTreeNode* dequeueAvlTreeQueue(AvlTreeQueue* queue){
    AvlTreeNode* dequeued = 0;
    if(queue && queue->head){
        AvlTreeQueueNode* oldHead = queue->head;
        dequeued = oldHead->value;
        queue->head = oldHead->next;
        deleteAvlTreeQueueNode(&oldHead);
        if(!(queue->head)){ // no more nodes
            queue->tail = 0;
        }
    }
    return dequeued;
}

/*
Public functions
*/

AvlTreeNode* newAvlTree(int value){
    AvlTreeNode* avl = (AvlTreeNode*)malloc(sizeof(AvlTreeNode));
    avl->value = value;
    avl->left = 0;
    avl->right = 0;
    avl->height = 0;
    return avl;
}
void deleteAvlTree(AvlTreeNode** root){
    if(root && *root){
        AvlTreeNode* node = *root;
        // delete this node post-order so children don't become inaccessable
        deleteAvlTree(&(node->left));
        deleteAvlTree(&(node->right));
        free(node);
        *root = 0;
    }
}

bool isInAvlTree(AvlTreeNode* root, int val);

bool insertIntoAvlTree(AvlTreeNode** root, int val){
    bool notDuplicate = false;
    if(root){ // not passed a null pointer
        AvlTreeNode* node = *root;
        if(!node){ // no root yet
            *root = newAvlTree(val);
            notDuplicate = true;
        } else if(node->value > val){
            notDuplicate = insertIntoAvlTree(&(node->left), val);
            rebalance(root);
        } else if(node->value < val){
            notDuplicate = insertIntoAvlTree(&(node->right), val);
            rebalance(root);
        } else { // node->value == val
            notDuplicate = false;
        }
    }
    return notDuplicate;
}

bool removeFromAvlTree(AvlTreeNode** root, int val){
    bool deleted = false;
    if(root){ // not passed a null pointer
        AvlTreeNode* node = *root;
        if(!node){
            // no node, do nothing
        } else if(node->value > val){
            deleted = removeFromAvlTree(&(node->left), val);
            rebalance(root);
        } else if(node->value < val){
            deleted = removeFromAvlTree(&(node->right), val);
            rebalance(root);
        }
        // by now, the value has been found
        else if(!(node->left || node->right)){ // no children
            free(node);
            *root = 0;
            deleted = true;
        } else if(node->left && node->right){ // two children
            // swap with either smallest right child or largest left child
            AvlTreeNode* swapMe = node->left;
            while(swapMe->right){
                swapMe = swapMe->right;
            }
            int newVal = swapMe->value;

            /*
            Need to remove from the root to update all the heights along the
            path to swapMe
            */
            deleted = removeFromAvlTree(root, swapMe->value);
            node->value = newVal;
            rebalance(root);
        } else if(node->left){
            AvlTreeNode* temp = node;
            *root = node->left;
            temp->left = 0;
            free(temp);
            deleted = true;
        } else if(node->right){
            AvlTreeNode* temp = node;
            *root = node->right;
            temp->right = 0;
            free(temp);
            deleted = true;
        }
    }
    return deleted;
}

int getAvlHeight(AvlTreeNode* root){
    int height = -1;
    if(root){
        height = root->height;
    }
    return height;
}

void preOrderAvl(AvlTreeNode* root){
    if(root){
        printf("%d ", root->value);
        preOrderAvl(root->left);
        preOrderAvl(root->right);
    }
}
void inOrderAvl(AvlTreeNode* root){
    if(root){
        inOrderAvl(root->left);
        printf("%d ", root->value);
        inOrderAvl(root->right);
    }
}
void postOrderAvl(AvlTreeNode* root){
    if(root){
        postOrderAvl(root->left);
        postOrderAvl(root->right);
        printf("%d ", root->value);
    }
}
void breadthPrintAvl(AvlTreeNode* root){
    AvlTreeQueue* currentLevel = newAvlTreeQueue();
    AvlTreeQueue* nextLevel = 0;
    if(root){
        enqueueAvlTreeQueue(currentLevel, root);
    }
    AvlTreeNode* currNode = 0;
    while(currentLevel->head){
        nextLevel = newAvlTreeQueue();
        while(currentLevel->head){
            currNode = dequeueAvlTreeQueue(currentLevel);
            if(currNode->left){
                enqueueAvlTreeQueue(nextLevel, currNode->left);
            }
            if(currNode->right){
                enqueueAvlTreeQueue(nextLevel, currNode->right);
            }
            printf("%d (%d) ", currNode->value, currNode->height);
        }
        // done with current level
        printf("%c", '\n');
        deleteAvlTreeQueue(&currentLevel);
        currentLevel = nextLevel;
    }

    deleteAvlTreeQueue(&currentLevel);
}

// Conforms to the Consumer standard defined in core.h
void askInsertAvl(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    printf("%s", "Enter value to insert: ");
    int i;
    scanf("%d", &i);
    insertIntoAvlTree(root, i);
}
void askDeleteAvl(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    printf("%s", "Enter value to delete: ");
    int i;
    scanf("%d", &i);
    bool deleted = removeFromAvlTree(root, i);
    printf("%d %s deleted\n", i, (deleted) ? "was" : "was not");
}
void doPreOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    preOrderAvl(*root);
    printf("%c", '\n');
}
void doInOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    inOrderAvl(*root);
    printf("%c", '\n');
}
void doPostOrder(void** avlTree){
    AvlTreeNode** root = (AvlTreeNode**)avlTree;
    postOrderAvl(*root);
    printf("%c", '\n');
}
void doBreadthPrint(void** avlTree){
    if(avlTree){
        AvlTreeNode** node = (AvlTreeNode**)avlTree;
        breadthPrintAvl(*node);
    }
}

int testAvlTree(){
    AvlTreeNode* alvin = 0;

    printf("%s\n", "AVL Tree");

    ConsumerMenuOption* options[] = {
        newConsumerMenuOption("Insert into the AVL Tree", &askInsertAvl),
        newConsumerMenuOption("Remove from the AVL Tree", &askDeleteAvl),
        newConsumerMenuOption("Print pre-order", &doPreOrder),
        newConsumerMenuOption("Print in-order", &doInOrder),
        newConsumerMenuOption("Print post-order", &doPostOrder),
        newConsumerMenuOption("Print breadth", &doBreadthPrint)
    };
    int numOptions = 6;

    doConsumerMenu(options, numOptions, (void**)&alvin);

    for(int i = 0; i < numOptions; ++i){
        freeConsumerMenuOption(&options[i]);
    }

    deleteAvlTree(&alvin);

    return 0;
}
