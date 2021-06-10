#include "sorting.h"
#include "util.h"
#include<stdio.h>
#include<stdlib.h>



/*
Private function prototypes
*/



/*
Public functions
*/

void bubbleSort(int a[], int length){
    
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
            // do sorting
        }
    } while(ip != -1);

    return 0;
}


/*
Private function implementations
*/
