#include "sorting.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>
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

int useSorting(){
    SortingAlgorithm algorithms[] = {
        &bubbleSort
    };

    char* algorithmNames[] = {
        "Bubble sort"
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
    clock_t start = times(&startStruct);
    algorithm(sortMe, length);
    end = times(&endStruct);

    printf("%s", "After: ");
    printArray(sortMe, length);

    printf("Took %6.3f seconds to run\n", ((double)(end - start)) / sysconf(_SC_CLK_TCK));
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
