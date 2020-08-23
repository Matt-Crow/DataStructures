#ifndef RADIX_PRIOR
#define RADIX_PRIOR

enum SortType {F_NAME, L_NAME, AGE};

typedef struct Record {
    char* fName;
    char* lName;
    int age;
} Record;

Record* newRecord(char fName[], char lName[], int age);
void deleteRecord(Record* record);
void printRecord(Record* record);
void printRecords(Record* records[], int recordCount);

void radixPrioritySort(Record* records[], int numRecords, enum SortType priorities[], int numPriorities);

int testRadixPrioritySort();

#endif
