#ifndef RADIX_PRIOR
#define RADIX_PRIOR

typedef struct Record {
    char* fName;
    char* lName;
    int age;
} Record;

typedef struct RecordQueue {
    struct RecordQueue* next;
    struct RecordQueue* prev;
    Record* value;
} RecordQueue;


Record* newRecord(char fName[], char lName[], int age);
void deleteRecord(Record* record);
void printRecord(Record* record);

RecordQueue* newRecordQueue(Record* value);
void deleteRecordQueue(RecordQueue** head, RecordQueue** tail);
void enqueueRecordQueue(RecordQueue** head, RecordQueue** tail, Record* value);
Record* dequeueRecordQueue(RecordQueue** head, RecordQueue** tail);
void printRecordQueue(RecordQueue* head);


int testRadixPrioritySort();

#endif
