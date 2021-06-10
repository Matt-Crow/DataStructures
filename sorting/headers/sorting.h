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

/*
finds the smallest element in an array, then puts it
at the beginning.

O(n^2)
*/
void selectSort(int a[], int length);

/*
Goes through each element in the array, and shoves it back
until the item to its left is less than it

O(n^2)
*/
void insertionSort(int a[], int length);

/*
Same as insertion sort, except is compares elements
a set distance, or gap, apart.
This gap keeps shrinking with every pass.

O(n^2)
*/
void shellSort(int a[], int length);

//void quickSort(int a[], int length);
//void mergeSort(int a[], int length);
//void radixSort(int a[], int length);

//int binarySearch(int a[], int length);

int useSorting();

#endif
