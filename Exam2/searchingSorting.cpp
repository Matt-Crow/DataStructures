#include <iostream>
#include <cstdlib>
using namespace std;

void print(int a[], int length);
void reset(int a[], int length);

void bubbleSort(int a[], int length, bool ascending);
void selectSort(int a[], int length, bool ascending);

void gappedSort(int a[], int length, bool ascending, int gap);
void insertionSort(int a[], int length, bool ascending);
void shellSort(int a[], int length, bool ascending);

int binarySearch(int a[], int length, int searchFor);

int useSearchSort(){
    int a[5];
    reset(a, 5);
    cout << "Before: " << endl;
    print(a, 5);
    cout << "Bubble sort: " << endl;
    bubbleSort(a, 5, true);
    reset(a, 5);
    cout << "Select sort: " << endl;
    selectSort(a, 5, true);
    reset(a, 5);
    cout << "Insertion sort: " << endl;
    insertionSort(a, 5, true);
    reset(a, 5);
    cout << "Shell sort: " << endl;
    shellSort(a, 5, true);
    reset(a, 5);
    return 0;
}

void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i];
        if(i != length - 1){
            cout << ", ";
        } else {
            cout << endl;
        }
    }
}

void reset(int a[], int length){
    for(int i = 0; i < length; i++){
        a[i] = (rand() % 10000) - 5000;
    }
}
/*
Pushes largest ints to the top first,
then makes its way down.
Thus, the largest "bubble" to the top
*/
void bubbleSort(int a[], int length, bool ascending){
    int temp;
    for(int i = 0; i < length - 1; i++){
        //at the end of the i'th pass, the i+1
        //largest will be at the end,
        //so no need to check them
        for(int j = 0; j < length - i - 1; j++){
            if(
               (ascending && a[j] > a[j + 1]) ||
               (!ascending && a[j] < a[j + 1])
               ){
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
        cout << "Pass " << i << ": " << endl;
        print(a, length);
    }
}

/*
finds the smallest element in an array, then puts it
at the beginning.
*/
void selectSort(int a[], int length, bool ascending){
    int temp;
    int idxOfSmallest;
    for(int i = 0; i < length; i++){
        idxOfSmallest = i;
        for(int j = i + 1; j < length; j++){
            if(
               (ascending && a[idxOfSmallest] > a[j]) ||
                (!ascending && a[idxOfSmallest] < a[j])
            ){
                idxOfSmallest = j;
            }
        }
        temp = a[idxOfSmallest];
        a[idxOfSmallest] = a[i];
        a[i] = temp;
        cout << "Pass " << i << ": " << endl;
        print(a, length);
    }
}

void gappedSort(int a[], int length, bool ascending, int gap){
    int temp;
    for( ; gap >= 1; gap /= 2){
        for(int i = gap; i < length; i++){
            for(int j = i; j >= gap && a[(ascending) ? j - gap : j] > a[(ascending) ? j : j - gap]; j -= gap){
                temp = a[j];
                a[j] = a[j - gap];
                a[j - gap] = temp;
                print(a, length);
            }
        }
    }
}

/*
Goes through each element in the array, and shoves it back
until the item to its left is less than it
*/
void insertionSort(int a[], int length, bool ascending){
    gappedSort(a, length, ascending, 1);
}

/*
Same as insertion sort, except is compares elements
a set distance, or gap, apart.
This gap keeps shrinking with every pass.
*/
void shellSort(int a[], int length, bool ascending){
    gappedSort(a, length, length / 2, ascending);
}


//only works for ascending order
/*
Starts at the middle, keeps cutting in half and choosing
which partition to search next based on whether or not
the middle was less than or greater than searchFor
*/
int binarySearch(int a[], int length, int searchFor){
    int ret = -1;
    int minIdx = 0;
    int maxIdx = length - 1;
    int midIdx;

    while(minIdx <= maxIdx && ret == -1){
        midIdx = (maxIdx + minIdx) / 2;
        if(a[midIdx] == searchFor){
            ret = midIdx;
        } else if(a[midIdx] < searchFor){
            minIdx = midIdx + 1;
        } else {
            maxIdx = midIdx - 1;
        }
    }

    return ret;
}


