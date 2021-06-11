#include "sorting.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#include<sys/times.h>
#include<unistd.h>



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

int useSorting(){
    SortingAlgorithm algorithms[] = {
        &bubbleSort,
        &selectSort,
        &insertionSort,
        &shellSort,
        &quickSort
    };

    char* algorithmNames[] = {
        "Bubble sort",
        "Select sort",
        "Insertion sort",
        "Shell sort",
        "Quick sort"
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
    int length = 16;
    int* sortMe = createRandomArray(length);

    printf("%s", "Before: ");
    printArray(sortMe, length);

    struct tms startStruct;
    struct tms endStruct;
    clock_t end;
    clock_t start = clock();//times(&startStruct);
    algorithm(sortMe, length);
    end = clock();//times(&endStruct);

    printf("%s", "After: ");
    printArray(sortMe, length);

    printf("Took %6.6f seconds to run\n", ((double)(end - start)) / CLOCKS_PER_SEC);//sysconf(_SC_CLK_TCK));
    free(sortMe);
}

int* createRandomArray(int length){
    int* a = (int*)malloc(length * sizeof(int));
    srand(time(NULL));
    for(int i = 0; i < length; ++i){
        a[i] = rand() % 256;
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
