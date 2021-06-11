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

/*
Partitions a pivot to its proper place
in the array, and sorts it so everything to
its left is smaller than it, and everything
to its right is larger, then recurs.
Very good for large problem sizes, as it only compares a small portion of the
array in each call.

O(n^2), but is more often around O(nlogn)
*/
void quickSort(int a[], int length);

/*
Keep breaking the array in half until we only
have two items to compare, the sort those two,
merge that sorted set with the next sorted set of 2,
creating a set of 4, merge that with the next set of 4, etc.

O(nlogn)
*/
void mergeSort(int a[], int length);

void radixSort(int a[], int length);

//int binarySearch(int a[], int length);

int useSorting();

#endif
