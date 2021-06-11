#include "sorting.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>



#define ARRAY_SIZE 5000 // choose how many elements it should test with


/*
Private function prototypes
*/

void swap(int a[], int i, int j);

void testAlgorithm(SortingAlgorithm algorithm);

int* createRandomArray(int length);

/*
Sorts the range [min, max)
*/
void doQuickSort(int a[], int min, int max);

/*
Sorts the range [min, max)
*/
void doMergeSort(int a[], int min, int max);

/*
[min, max)
*/
int idxOfMedian(int a[], int min, int max);

/*
Returns true if a <= b <= c or c <= b <= a
*/
bool isBetween(int a, int b, int c);

bool betweenRecur(int a, int b, int c);

/*
Public functions
*/

void bubbleSort(int a[], int length){
    if(DEBUG){
        printArray(a, length);
    }
    for(int i = 0; i < length - 1; ++i){
        /*
        at the end of the i'th pass, the i+1 largest will be at the end,
        so no need to check them
        */
        for(int j = 0; j < length - i - 1; ++j){
            if(a[j] > a[j + 1]){
                swap(a, j, j + 1);
                if(DEBUG){
                    printArray(a, length);
                }
            }
        }
    }
}

void selectSort(int a[], int length){
    int smallest = -1;
    if(DEBUG){
        printArray(a, length);
    }
    for(int i = 0; i < length; ++i){
        smallest = i;
        for(int j = i + 1; j < length; ++j){
            if(a[smallest] > a[j]){
                smallest = j;
            }
        }
        swap(a, i, smallest);
        if(DEBUG){
            printArray(a, length);
        }
    }
}

void insertionSort(int a[], int length){
    if(DEBUG){
        printArray(a, length);
    }
    for(int i = 1; i < length; ++i){
        for(int j = i; j > 0 && a[j] < a[j - 1]; --j){
            swap(a, j, j - 1);
            if(DEBUG){
                printArray(a, length);
            }
        }
    }
}

void shellSort(int a[], int length){
    if(DEBUG){
        printArray(a, length);
    }
    for(int gap = length / 2; gap >= 1; gap >>= 1){ // cut gap in half each iteration
        for(int i = gap; i < length; ++i){
            for(int j = i; j >= gap && a[j - gap] > a[j]; j -= gap){
                swap(a, j, j - gap);
                if(DEBUG){
                    printArray(a, length);
                }
            }
        }
    }
}

void quickSort(int a[], int length){
    doQuickSort(a, 0, length);
}

void mergeSort(int a[], int length){
    doMergeSort(a, 0, length);
}

void radixSort(int a[], int length){
    // create queues
    unsigned int base = 10; // can use any number here except 0 or 1
    Queue* queues[base];
    int i;
    for(i = 0; i < base; ++i){
        queues[i] = newQueue();
    }

    int baseToSomePower = 1;
    bool biggerFish = true; // not all numbers have been sorted
    while(biggerFish){
        biggerFish = false;

        // check the next digit when the numbers are interpreted in the given base
        for(i = 0; i < length; ++i){
            if(abs(a[i]) > baseToSomePower * base){
                biggerFish = true;
                // will require at least one more iteration to sort
            }
            enqueue(
                queues[
                    (abs(a[i]) / baseToSomePower) % base
                ],
                a[i]
            );
        }

        // sort everything according to the current digit
        i = 0;
        for(int b = 0; b < base; ++b){
            while(!isQueueEmpty(queues[b])){
                a[i++] = dequeue(queues[b]);
            }
        }

        if(DEBUG){
            printArray(a, length);
        }

        baseToSomePower *= base;
    }

    // free queues
    for(i = 0; i < base; ++i){
        deleteQueue(&(queues[i]));
    }

    // by now, a[] is sorted by absolute value
    Stack* negatives = 0;
    Queue* positives = newQueue();
    for(i = 0; i < length; ++i){
        if(a[i] < 0){
            push(&negatives, a[i]);
        } else {
            enqueue(positives, a[i]);
        }
    }

    i = 0;
    while(negatives){
        a[i++] = pop(&negatives);
    }
    while(!isQueueEmpty(positives)){
        a[i++] = dequeue(positives);
    }

    // stack is empty, so no need to free it
    deleteQueue(&positives);
}

void unsignedRadixSort(unsigned int a[], int length){
    // create queues
    Queue* queues[2] = {
        newQueue(),
        newQueue()
    };

    int numBits = sizeof(int) * 8;

    int bit;
    int i;
    for(int bitNum = 0; bitNum < numBits; ++bitNum){
        for(i = 0; i < length; ++i){
            bit = (a[i] >> bitNum) & 1;
            enqueue(queues[bit], a[i]);
        }
        // by now, queues[0] contains all elements of a[] whose bitNum-th bit is 0,
        // and queues[1] has all elements whose bitNum-th bit is 1
        i = 0;
        while(!isQueueEmpty(queues[0])){
            a[i++] = dequeue(queues[0]);
        }
        while(!isQueueEmpty(queues[1])){
            a[i++] = dequeue(queues[1]);
        }

        if(DEBUG){
            printArray((int*)a, length);
        }
    }

    // todo sort by sign

    // free queues
    deleteQueue(&(queues[0]));
    deleteQueue(&(queues[1]));
}

int binarySearch(int a[], int length, int searchFor){
    int min = 0;
    int max = length - 1;
    int mid;
    int foundAt = -1;
    while(foundAt == -1 && min <= max){
        mid = (min + max) / 2;
        if(a[mid] > searchFor){
            max = mid - 1;
        } else if(a[mid] < searchFor){
            min = mid + 1;
        } else {
            foundAt = mid;
        }
    }
    return foundAt;
}

int useSorting(){
    SortingAlgorithm algorithms[] = {
        &bubbleSort,
        &selectSort,
        &insertionSort,
        &shellSort,
        &quickSort,
        &mergeSort,
        &radixSort
    };

    char* algorithmNames[] = {
        "Bubble sort",
        "Select sort",
        "Insertion sort",
        "Shell sort",
        "Quick sort",
        "Merge sort",
        "Radix sort"
    };
    int numOptions = sizeof(algorithms) / sizeof(algorithms[0]);

    printf("%s\n", "Sorting Algorithms");
    int ip = 0;

    do {
        for(int i = 0; i < numOptions; ++i){
            printf("%d: %s\n", i + 1, algorithmNames[i]);
        }
        printf("%s\n%s", "0: Quit", "Choose an option: ");
        scanf("%d", &ip);
        --ip;
        if(ip >= 0 && ip < numOptions){
            testAlgorithm(algorithms[ip]);
        }
    } while(ip != -1);

    return 0;
}



/*
Private function implementations
*/

void swap(int a[], int i, int j){
    int temp = a[i];
    a[i] = a[j];
    a[j] = temp;
}

void testAlgorithm(SortingAlgorithm algorithm){
    int length = ARRAY_SIZE;
    int* sortMe = createRandomArray(length);

    printf("%s", "Before: ");
    printArray(sortMe, length);

    clock_t end;
    clock_t start = clock();
    algorithm(sortMe, length);
    end = clock();

    printf("%s", "After: ");
    printArray(sortMe, length);

    printf("Took %6.6f seconds to run\n", ((double)(end - start)) / CLOCKS_PER_SEC);
    free(sortMe);
}

int* createRandomArray(int length){
    int* a = (int*)malloc(length * sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < length; ++i){
        a[i] = rand() % 256 - 128; // (-128, 127)
    }
    return a;
}

void doQuickSort(int a[], int min, int max){
    if(max - min <= 1){ // don't sort sub-arrays of 1 element
        return;
    }

    // find the ideal pivot value
    int pivotIdx = idxOfMedian(a, min, max);
    int pivot = a[pivotIdx];

    swap(a, pivotIdx, max - 1); // move pivot to the end
    int i = min;
    int j = max - 2; // left of pivot

    while(i <= j){
        while(i < max - 1 && a[i] < pivot){
            ++i;
        } // i now points to either the pivot or a problematic value

        while(j > min - 1 && a[j] > pivot){
            --j;
        } // j has either fallen off the end or points to a problematic value

        if(i <= j){
            // both point to a problematic value, so swap them
            swap(a, i++, j--); // post- inc and dec, not pre-
        } // else, we are done partitioning
    }
    // i now points to the pivot's proper place
    swap(a, i, max - 1);

    if(DEBUG){
        printArray(a, max);
    }

    doQuickSort(a, min, i);
    doQuickSort(a, i + 1, max);
}

int idxOfMedian(int a[], int min, int max){
    int mid = (min + max) / 2;
    --max;
    int best = mid;

    if(isBetween(a[mid], a[min], a[max])){
        best = min;
    } else if(isBetween(a[min], a[max], a[mid])){
        best = max;
    } // else best = mid

    return best;
}

bool isBetween(int a, int b, int c){
    return betweenRecur(a, b, c) || betweenRecur(c, b, a);
}

bool betweenRecur(int a, int b, int c){
    return a <= b && b <= c;
}

void doMergeSort(int a[], int min, int max){
    int size = max - min;
    if(size <= 1){ // don't bother sorting sub-arrays of 1 element
        return;
    }

    int mid = (min + max) / 2;
    doMergeSort(a, min, mid);
    doMergeSort(a, mid, max);
    // [min, mid) and [mid, max) are now both sorted

    // merge them together
    int graft[size];
    int i = 0;
    int queue1 = min;
    int queue2 = mid;
    // treat sub-arrays as queues
    while(queue1 < mid && queue2 < max){
        if(a[queue1] < a[queue2]){
            graft[i++] = a[queue1++];
        } else {
            graft[i++] = a[queue2++];
        }
        // keep dequeueing the smaller value int the graft
    }

    // by now, exactly one queue is empty. Empty the other one
    while(queue1 < mid){
        graft[i++] = a[queue1++];
    }
    while(queue2 < max){
        graft[i++] = a[queue2++];
    }

    // graft the graft array back into the original array
    // i already declared
    for(i = 0; i < size; ++i){
        a[min + i] = graft[i];
    }

    if(DEBUG){
        printArray(a, max);
    }
}
