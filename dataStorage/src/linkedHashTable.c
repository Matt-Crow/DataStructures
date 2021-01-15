#include "linkedHashTable.h"
#include<stdlib.h>

typedef struct LinkedHashTableNode {
    struct LinkedHashTableNode* next;
    char* value;
} LinkedHashTableNode;

typedef struct LinkedHashTable {
    LinkedHashTableNode** values;
    int capacity;
} LinkedHashTable;

LinkedHashTable* newLinkedHashTable(int capacity){
    LinkedHashTable* ret = (LinkedHashTable*)malloc(sizeof(LinkedHashTable));
    ret->values = (LinkedHashTableNode**)malloc(sizeof(LinkedHashTableNode*) * capacity);
    for(int i = 0; i < capacity; i++){
        (ret->values)[i] = 0; // set to null pointers
    }
    ret->capacity = capacity;
    return ret;
}

int testLinkedHashTable(){
    return 1;
}
