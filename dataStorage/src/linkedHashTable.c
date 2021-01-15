#include "linkedHashTable.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

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

LinkedHashTableNode* newLinkedHashTableNode(char* value){
    LinkedHashTableNode* ret = (LinkedHashTableNode*)malloc(sizeof(LinkedHashTableNode));
    ret->next = 0;
    ret->value = strdup(value);//(char*)malloc(sizeof(char) * (strlen(value) + 1));
    //strcpy(ret->value, value);
    return ret;
}

bool freeLinkedHashTableNode(LinkedHashTableNode** node){
    bool freed = node && *node;
    if(freed){
        if((*node)->next){
            freeLinkedHashTableNode(&((*node)->next));
        }
        printf("Freed table node with value \"%s\"\n", (*node)->value);
        free((*node)->value);
        free(*node);
        *node = 0;
    }
    return freed;
}

unsigned hash(char* str, int tableCapacity){
    unsigned theHash = 0;
    // needs to be unsigned to prevent rolling over to negative
    for(int i = 0; str[i] != '\0'; i++){
        theHash = str[i] + 31 * theHash;
    }
    return theHash % tableCapacity;
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

bool freeLinkedHashTable(LinkedHashTable** table){
    bool freed = table && *table; // neither null nor pointer to null
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

void putIntoHashTable(LinkedHashTable* table, char* value){
    unsigned hashCode = hash(value, table->capacity);
    printf("hash is %u\n", hashCode);
    LinkedHashTableNode* newNode = newLinkedHashTableNode(value);
    newNode->next = table->values[hashCode];
    table->values[hashCode] = newNode;
}

bool isInHashTable(LinkedHashTable* table, char* value){
    bool found = false;
    unsigned hashCode = hash(value, table->capacity);
    LinkedHashTableNode* curr = table->values[hashCode];
    while(curr && !found){
        if(strcmp(curr->value, value) == 0){
            found = true;
        } else {
            curr = curr->next;
        }
    }
    return found;
}

void getNextLine(char* intoHere, int maxChars){
    fgets(intoHere, maxChars, stdin);
    char* nlChar = strstr(intoHere, "\n");
    if(nlChar){
        nlChar[0] = '\0'; // replace newline character
    }
}

void printLinkedHashTable(LinkedHashTable* table){
    printf("%s", "Linked Hash Table:\n");
    for(int i = 0; i < table->capacity; i++){
        printf("* %d: ", i);
        for(LinkedHashTableNode* curr = table->values[i]; curr != 0; curr = curr->next){
            printf("\"%s\"", curr->value);
            if(curr->next){
                printf("%s", " => ");
            }
        }
        printf("%s", "\n");
    }
}

int testLinkedHashTable(){
    LinkedHashTable* table = newLinkedHashTable(4);
    int maxIpSize = 100;
    char ip[maxIpSize];
    int option = -1;
    do {
        printf("%s", "=== Linked Hash Table ===\n");
        printf("%s", "0: Print the linked hash table\n");
        printf("%s", "1: Put into the linked hash table\n");
        printf("%s", "2: Check if in the linked hash table\n");
        printf("%s", "-1: Quit\n");
        printf("%s", "Choose an option: ");
        scanf("%d", &option);
        switch (option) {
            case 0:
                printLinkedHashTable(table);
                break;
            case 1:
                fgets(ip, maxIpSize, stdin); // clear stdin first
                printf("%s", "Enter value to insert: ");
                getNextLine(ip, maxIpSize);
                putIntoHashTable(table, ip);
                break;
            case 2:
                fgets(ip, maxIpSize, stdin); // clear stdin first
                printf("%s", "Enter value to search for: ");
                getNextLine(ip, maxIpSize);
                bool found = isInHashTable(table, ip);
                if(found){
                    printf("\"%s\" is in the hash table\n", ip);
                } else {
                    printf("\"%s\" is not in the hash table\n", ip);
                }
                break;
        }
    } while(option != -1);

    freeLinkedHashTable(&table);
    return 0;
}
