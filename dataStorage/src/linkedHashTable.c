#include "linkedHashTable.h"
#include<stdlib.h>
#include<stdio.h>

/*
Private definitions
*/
typedef struct LinkedHashTableNode {
    struct LinkedHashTableNode* next;
    char* value;
} LinkedHashTableNode;

typedef struct LinkedHashTable {
    LinkedHashTableNode** values;
    int capacity;
} LinkedHashTable;

int freeLinkedHashTableNode(LinkedHashTableNode** node){
    int freed = node && *node;
    if(freed){
        if((*node)->next){
            freeLinkedHashTableNode(&((*node)->next));
        }
        printf("Freed table node with value \"%s\"\n", (*node)->value);
        free(*node);
        *node = 0;
    }
    return freed;
}


/*
Public definitions
*/
LinkedHashTable* newLinkedHashTable(int capacity){
    LinkedHashTable* ret = (LinkedHashTable*)malloc(sizeof(LinkedHashTable));
    ret->values = (LinkedHashTableNode**)malloc(sizeof(LinkedHashTableNode*) * capacity);
    for(int i = 0; i < capacity; i++){
        (ret->values)[i] = 0; // set to null pointers
    }
    ret->capacity = capacity;
    return ret;
}

int freeLinkedHashTable(LinkedHashTable** table){
    int freed = table && *table; // neither null nor pointer to null
    if(freed){
        LinkedHashTable* theTable = *table;
        for(int i = 0; i < theTable->capacity; i++){
            if(theTable->values[i]){
                freeLinkedHashTableNode(&(theTable->values[i]));
            }
        }
        free(theTable);
        *table = 0;
    }
    return freed;
}

int testLinkedHashTable(){
    LinkedHashTable* table = newLinkedHashTable(4);
    freeLinkedHashTable(&table);
    return 0;
}
