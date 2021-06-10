#ifndef SORTING
#define SORTING

typedef void (*SortingAlgorithm)(int a[], int length);

/*
Pushes largest ints to the top first,
then makes its way down.
Thus, the largest "bubble" to the top.

O(n^2)
*/
void bubbleSort(int a[], int length);

//void selectSort(int a[], int length);
//void insertionSort(int a[], int length);
//void shellSort(int a[], int length);
//void quickSort(int a[], int length);
//void mergeSort(int a[], int length);
//void radixSort(int a[], int length);

//int binarySearch(int a[], int length);

int useSorting();

#endif
