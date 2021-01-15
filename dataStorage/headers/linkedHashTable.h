#ifndef LINKED_HASH_TABLE
#define LINKED_HASH_TABLE

/*
LinkedHashTable is defined in linkedHashTable.c
Notice how this allows me to reference this data structure from any file that
includes this one, yet only linkedHashTable.c is allowed access to the
implementation details.
*/
typedef struct LinkedHashTable LinkedHashTable;

LinkedHashTable* newLinkedHashTable(int capacity);

int testLinkedHashTable();

#endif
