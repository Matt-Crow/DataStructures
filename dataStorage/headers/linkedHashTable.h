#ifndef LINKED_HASH_TABLE
#define LINKED_HASH_TABLE

#include<stdbool.h>

/*
LinkedHashTable is defined in linkedHashTable.c
Notice how this allows me to reference this data structure from any file that
includes this one, yet only linkedHashTable.c is allowed access to the
implementation details.
*/
typedef struct LinkedHashTable LinkedHashTable;

LinkedHashTable* newLinkedHashTable(int capacity);
bool freeLinkedHashTable(LinkedHashTable** table);
void putIntoHashTable(LinkedHashTable* table, char* value);
bool isInHashTable(LinkedHashTable* table, char* value);
void printLinkedHashTable(LinkedHashTable* table);

int testLinkedHashTable();

#endif
