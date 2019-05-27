#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Queue.h"
#include "Stack.h"

using namespace std;

void print(int a[], int length);
void bubbleSort(int a[], int length);
void selectSort(int a[], int length);
void gappedSort(int a[], int length, int gapSize);
void insertionSort(int a[], int length);
void shellSort(int a[], int length);

void quickSort(int a[], int start, int end);
int partition(int a[], int start, int end);
void mergeSort(int a[], int start, int end);

void radixSort(int a[], int length);
void radixSort(int a[], int length, int tenToSomePow);
void posNegSort(int a[], int length);

int binarySearch(int a[], int length, int searchFor);



int useSearchSort(){
    int a[] = {354, -102, 72, 448, -11, 945, 43, 57, 0, 6};
    int backup[10];
    int ip;
    bool sorted = false;
    memcpy(backup, a, 10 * sizeof(int));

    do {
        cout << "Choose an option:" << endl;
        cout << "0: Print the original array" << endl;
        cout << "1: Reset the array" << endl;
        cout << "2: use bubble sort" << endl;
        cout << "3: use select sort" << endl;
        cout << "4: use insertion sort" << endl;
        cout << "5: use shell sort" << endl;
        cout << "6: use quick sort" << endl;
        cout << "7: use merge sort" << endl;
        cout << "8: use radix sort" << endl;
        cout << "9: use binary search" << endl;
        cout << "-1: quit" << endl;
        cin >> ip;

        switch(ip){
        case 0:
            print(a, 10);
            break;
        case 1:
            memcpy(a, backup, 10 * sizeof(int));
            sorted = false;
            break;
        case 2:
            bubbleSort(a, 10);
            sorted = true;
            cout << "After bubble sort: ";
            print(a, 10);
            break;
        case 3:
            selectSort(a, 10);
            sorted = true;
            cout << "After select sort: ";
            print(a, 10);
            break;
        case 4:
            insertionSort(a, 10);
            sorted = true;
            cout << "After insertion sort: ";
            print(a, 10);
            break;
        case 5:
            shellSort(a, 10);
            sorted = true;
            cout << "After shell sort: ";
            print(a, 10);
            break;
        case 6:
            quickSort(a, 0, 10 - 1);
            sorted = true;
            cout << "After quick sort: ";
            print(a, 10);
            break;
        case 7:
            mergeSort(a, 0, 10 - 1);
            sorted = true;
            cout << "After merge sort: ";
            print(a, 10);
            break;
        case 8:
            radixSort(a, 10);
            sorted = true;
            cout << "After radix sort: ";
            print(a, 10);
            break;
        case 9:
            if(!sorted){
                cout << "Array must be sorted to perform binary search" << endl;
                break;
            }
            cout << "Enter the value to search for: ";
            cin >> ip;
            int idx = binarySearch(a, 10, ip);
            if(idx != -1){
                cout << ip << " is located at index " << idx << endl;
            } else {
                cout << ip << " is not in the array" << endl;
            }
            ip = 8;
        }
    }while(ip >= 0);



    return 0;
}



void print(int a[], int length){
    for(int i = 0; i < length; i++){
        cout << a[i] << " ";
    }
    cout << endl;
}

/*
Pushes largest ints to the top first,
then makes its way down.
Thus, the largest "bubble" to the top
*/
void bubbleSort(int a[], int length){
    int temp;
    for(int i = 0; i < length - 1; i++){
        //at the end of the i'th pass, the i+1
        //largest will be at the end,
        //so no need to check them
        for(int j = 0; j < length - i - 1; j++){
            if(a[j] > a[j + 1]){
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
                print(a, length);
            }
        }
    }
}

/*
finds the smallest element in an array, then puts it
at the beginning.
*/
void selectSort(int a[], int length){
    int temp;
    int idxOfSmallest;
    for(int i = 0; i < length; i++){
        idxOfSmallest = i;
        for(int j = i + 1; j < length; j++){
            if(a[idxOfSmallest] > a[j]){
                idxOfSmallest = j;
            }
        }
        temp = a[idxOfSmallest];
        a[idxOfSmallest] = a[i];
        a[i] = temp;
        print(a, length);
    }
}

void gappedSort(int a[], int length, int gap){
    int temp;
    for( ; gap >= 1; gap /= 2){
        for(int i = gap; i < length; i++){
            for(int j = i; j >= gap && a[j - gap] > a[j]; j -= gap){
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
void insertionSort(int a[], int length){
    gappedSort(a, length, 1);
}

/*
Same as insertion sort, except is compares elements
a set distance, or gap, apart.
This gap keeps shrinking with every pass.
*/
void shellSort(int a[], int length){
    gappedSort(a, length, length / 2);
}


void quickSort(int a[], int start, int end){
    if(start < end){
        int mid = partition(a, start, end);
        quickSort(a, start, mid - 1);
        quickSort(a, mid + 1, end);
    }
}

/*
Moves a[end], the PIVOT, to its proper place
in the array, and sorts it so everything to
its left is smaller than it, and everything
to its right is larger.
*/
int partition(int a[], int start, int end){
    int pivotValue = a[end];
    int i = start;
    int temp;
    cout << "Pivot is " << pivotValue << endl;
    for(int j = start; j < end; j++){
        //cout << "Checking index " << j << endl;
        if(a[j] <= pivotValue){
            temp = a[j];
            a[j] = a[i];
            a[i] = temp;
            i++;
            print(a, 10);
        }
        //cout << "Pivot should be moved to " << i << endl;
        //print(a, 10);
    }
    temp = a[i];
    a[i] = a[end];
    a[end] = temp;
    print(a, 10);
    return i;
}


/*
Keep breaking the array in half until we only
have two items to compare, the sort those two,
sort that sorted set with the next sorted set of 2,
creating a set of 4, sort that with the next set of 4, etc.
*/
void mergeSort(int a[], int start, int end){
    if(start < end){
        int mid = (start + end) / 2;
        mergeSort(a, start, mid);
        mergeSort(a, mid + 1, end);

        //merge
        //each split is technically a sorted array
        int a1 = start;
        int a2 = mid + 1;
        int mergedArray[end - start] = {0};
        int mergedArrayIdx = 0;
        /*
        cout << start << " < " << mid << " < " << end<< endl;
        cout << "A1 is " << endl;
        for(int i = start; i <= mid; i++){
            cout << a[i] << " ";
        }
        cout << endl << "A2 is " << endl;
        for(int i = mid + 1; i <= end; i++){
            cout << a[i] << " ";
        }
        cout << endl;
        */
        while(a1 <= mid && a2 <= end){
            if(a[a1] <= a[a2]){
                mergedArray[mergedArrayIdx] = a[a1];
                a1++;
            } else {
                mergedArray[mergedArrayIdx] = a[a2];
                a2++;
            }
            mergedArrayIdx++;
        }

        //copy the rest in
        while(a1 <= mid){
            mergedArray[mergedArrayIdx] = a[a1];
            a1++;
            mergedArrayIdx++;
        }
        while(a2 <= end){
            mergedArray[mergedArrayIdx] = a[a2];
            a2++;
            mergedArrayIdx++;
        }

        //copy new array into original
        for(int i = start; i <= end; i++){
            a[i] = mergedArray[i - start];
        }

        print(mergedArray, end - start + 1);
    }
}

/*
Sorts based on first the digit in the ones place,
then the tens place, hundreds and so on,
then sort by positive or negative
*/
void radixSort(int a[], int length){
    radixSort(a, length, 1);
    posNegSort(a, length);
}
void radixSort(int a[], int length, int tenToSomePow){
    bool higherPow = false; //wow. C++ is an atheist
    Queue<int> sigFigs[10]; //ten numbers, 10 queues
    for(int i = 0; i < 10; i++){
        sigFigs[i] = Queue<int>();
    }

    for(int i = 0; i < length; i++){
        //check to see if there are any digits we haven't sorted by yet
        if(!higherPow && abs(a[i]) > tenToSomePow * 10){
            higherPow = true;
        }
        //       gets the digit we are currently checking
        sigFigs[(abs(a[i])/tenToSomePow)%10].enqueue(a[i]);
    }
    cout << "After enqueing..." << endl;
    for(int i = 0; i < 10; i++){
        cout << i << ":";
        sigFigs[i].print();
        cout << endl;
    }

    //empty the queues into the array
    int aIdx = 0;
    for(int i = 0; i < 10; i++){
        while(!sigFigs[i].isEmpty()){
            a[aIdx] = sigFigs[i].deque();
            aIdx++;
        }
    }

    if(higherPow){
        radixSort(a, length, tenToSomePow * 10);
    }
}
void posNegSort(int a[], int length){
    /*
    a is sorted by absolute value,
    so now I need to put all the negatives at the front,
    and positives at the back
    */
    Stack<int>* neg = new Stack<int>();
    Queue<int>* pos = new Queue<int>();

    for(int i = 0; i < length; i++){
        if(a[i] >= 0){
            pos->enqueue(a[i]);
        } else {
            neg->push(a[i]);
        }
    }
    int aIdx = 0;
    while(!neg->isEmpty()){
        a[aIdx] = neg->pop();
        aIdx++;
    }
    while(!pos->isEmpty()){
        a[aIdx] = pos->deque();
        aIdx++;
    }

    delete pos;
    delete neg;
}

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
